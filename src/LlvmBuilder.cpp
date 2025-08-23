#include "LlvmBuilder.h"

void LLVMBuilder::createOperatorMap()
{
    for (auto &lib : runtimeLib.libraries)
    {
        for (auto &fun : lib->functions)
        {
            if (fun->metadata.contains(stc::FUNCTION_LIB_INIT))
            {
                std::cout << fun->name << "\n";
                lib->initFunction = &*fun;
            }
            else if (fun->metadata.contains(stc::FUNCTION_TOKEN))
            {
                auto tokenString = fun->metadata[stc::FUNCTION_TOKEN];
                auto token = stc::getOperatorType(tokenString);
                if (token != stc::OPERATOR_UNKOWN)
                {
                    operatorMap[token] = &*fun;
                }

            }
        }
    }
}

void LLVMBuilder::createValueStruct()
{

    valueType = llvm::StructType::create(context, {i8Type, i64Type}, "Value");
}

void LLVMBuilder::createStackStorage()
{
    assert(valueType && "Value struct must be created before stack storage");

    llvm::ArrayType* stackType = llvm::ArrayType::get(valueType, 1024);
    llvm::Constant* zeroInit = llvm::ConstantAggregateZero::get(stackType);

    stackStorage = new llvm::GlobalVariable(
        *module,
        stackType,
        false,  // isConstant
        llvm::GlobalValue::ExternalLinkage,
        zeroInit,
        "stack_storage");
    stackStorage->setSection(".stc_stack");
}

void LLVMBuilder::createStackPtr() {
    llvm::Constant* zeroInit = llvm::ConstantInt::get(i32Type, 0);
    stackPtr = new llvm::GlobalVariable(
        *module,
        i32Type,
        false,  // isConstant
        llvm::GlobalValue::PrivateLinkage,
        zeroInit,
        "stack_ptr");
}

void LLVMBuilder::loadRuntimeLib()
{
    if (!runtimeLib.loadDirectory("stc/bin", *module, context)) {
        std::cerr << "Failed to load runtime lib.\n";
        exit(1);
    }

}

void LLVMBuilder::initLibs() const
{
    for (auto &lib : runtimeLib.libraries)
    {
        auto fun = lib->initFunction->funcLLVM;
        builder->CreateCall(fun);
    }
}

void LLVMBuilder::linkLibs()
{
    for (auto &lib : runtimeLib.libraries)
    {
        if (!lib->linkModule( *module, context)) {
            std::cerr << "Failed to link runtime lib.\n";
            exit(1);
        }
    }
}

llvm::Value* LLVMBuilder::push(llvm::Value* val) const
{
    assert(stackPtr && stackStorage && valueType && "Stack vars must be initialized");

    llvm::Value* ptrVal = builder->CreateLoad(builder->getInt32Ty(), stackPtr);
    llvm::Value* gep = builder->CreateInBoundsGEP(stackStorage->getValueType(), stackStorage,{builder->getInt32(0), ptrVal});
    builder->CreateStore(val, gep);
    llvm::Value* incremented = builder->CreateAdd(ptrVal, builder->getInt32(1));
    builder->CreateStore(incremented, stackPtr);

    return incremented;
}

llvm::Value* LLVMBuilder::pop() const
{
    assert(stackPtr && stackStorage && valueType && "Stack vars must be initialized");

    llvm::Value* ptrVal = builder->CreateLoad(builder->getInt32Ty(), stackPtr);
    llvm::Value* decremented = builder->CreateSub(ptrVal, builder->getInt32(1));
    builder->CreateStore(decremented, stackPtr);
    llvm::Value* gep = builder->CreateInBoundsGEP(stackStorage->getValueType(), stackStorage,{builder->getInt32(0), decremented});
    llvm::Value* val = builder->CreateLoad(valueType, gep);

    return val;
}
llvm::FunctionCallee LLVMBuilder::getPrintfFunction()
{

    llvm::FunctionType *printfType = llvm::FunctionType::get(
        llvm::IntegerType::getInt32Ty(context),
        llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0),
        true // printf is variadic
    );

    llvm::FunctionCallee printfFunc = module->getOrInsertFunction("printf", printfType);
    return printfFunc;

}

llvm::Value* LLVMBuilder::createStackValue(llvm::Value* value, llvm::Value* type) const
{
    llvm::Value* structVal = llvm::UndefValue::get(valueType);
    structVal = builder->CreateInsertValue(structVal, type, 0);
    structVal = builder->CreateInsertValue(structVal, value, 1);
    return structVal;
}

llvm::GlobalVariable*  LLVMBuilder::getOrCreatePrintfFormatStr(const std::string& fmtStr)
{
    llvm::Constant *formatConst = llvm::ConstantDataArray::getString(context, fmtStr);
    llvm::GlobalVariable *formatStr = module->getGlobalVariable(".str");

    if (!formatStr)
    {
        formatStr = new llvm::GlobalVariable(
            *module,
            formatConst->getType(),
            true, // isConstant
            llvm::GlobalValue::PrivateLinkage,
            formatConst,
            ".str"
        );
        formatStr->setAlignment(llvm::MaybeAlign(1));
    }
    return formatStr;
}

void  LLVMBuilder::printInt(llvm::Value* intValue)
{
    llvm::FunctionCallee printfFunc = getPrintfFunction();

    llvm::GlobalVariable* formatStr = getOrCreatePrintfFormatStr("%d\n");

    llvm::Value *zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
    llvm::Value *indices[] = {zero, zero};
    llvm::Value *formatStrPtr = builder->CreateInBoundsGEP(
        formatStr->getValueType(), formatStr, indices, "formatStrPtr");

    builder->CreateCall(printfFunc, {formatStrPtr, intValue});
}

llvm::Module*  LLVMBuilder::build()
{
    createValueStruct();
    createStackStorage();
    createStackPtr();
    loadRuntimeLib();
    createOperatorMap();



    for (auto &[_, func] : program->functions)
    {
        func->buildFunctionDefinition(*builder, *module);
    }

    for (auto &[_, func] : program->functions)
    {
        buildFunction(func);
    }
    linkLibs();
    return module.get();
}

void LLVMBuilder::buildFunction(const std::unique_ptr<stc::Function> & func)
{
    bool isMain = false;
    if (func->name=="main")
    {
        isMain = true;
        llvm::BasicBlock *initBlock = llvm::BasicBlock::Create(context, "init", func->funcLLVM);
        builder->SetInsertPoint(initBlock);
        initLibs();

    }
    for (auto &block: func->blocks)
    {
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, block->name, func->funcLLVM);
        if (isMain)
        {
            builder->CreateBr(entry);
        }
        builder->SetInsertPoint(entry);
        block->blockLLVM = entry;
        buildBlock(block);
        builder->CreateRet(llvm::ConstantInt::get(i32Type, 0));

    }
}

void LLVMBuilder::buildBlock(const std::unique_ptr<stc::Block> & block)
{
    for (auto &operation : block->operations)
    {
        switch (operation->type)
        {
            case stc::STACK_OPERATION:
                break;
            case stc::PUSH_OPERATION:
                buildPush(dynamic_cast<stc::PushOperation *>(operation.get()));
                break;
            case stc::IF_STATEMENT:
                buildIf(dynamic_cast<stc::IfStatement *>(operation.get()));
                break;
            case stc::REPEAT_STATEMENT:
                buildRepeat(dynamic_cast<stc::RepeatStatement *>(operation.get()));
                break;
            case stc::VAR_ASSIGNMENT:
                break;
            case stc::FUNCTION_CALL:
                break;
            case stc::OPERATION:
                buildOperation(dynamic_cast<stc::Operator *>(operation.get()));
                break;
        }
    }
}

void  LLVMBuilder::buildPush(stc::PushOperation  *pushOperation)
{
    auto [type, value] = pushOperation->getLLVMToken(context);
    push(createStackValue(value, type));
}

void LLVMBuilder::buildOperation(stc::Operator *operation)
{
    auto fun = operatorMap[operation->operatorType];

    unsigned numArgs = fun->funcLLVM->arg_size() / 2;

    std::vector<llvm::Value*> args;

    args.reserve(numArgs);

    for (unsigned i = 0; i < numArgs; ++i) {
        args.push_back(pop());
    }
    std::ranges::reverse(args);

    llvm::Value* result = builder->CreateCall(fun->funcLLVM, args);
    printInt( builder->CreateExtractValue(result, 1));
    push(result);
}

void LLVMBuilder::buildIf(stc::IfStatement *ifStmt)
{
    // Pop condition value from stack
    llvm::Value* condStruct = pop();
    llvm::Value* condValue = builder->CreateExtractValue(condStruct, 1);

    // Compare condition value to zero (not zero means true)
    llvm::Value* cond = builder->CreateICmpNE(condValue, builder->getInt64(0));

    llvm::Function* currentFunc = builder->GetInsertBlock()->getParent();

    // Create blocks for true and false branches and continuation
    llvm::BasicBlock* trueBlock = llvm::BasicBlock::Create(context, "if_true", currentFunc);
    llvm::BasicBlock* falseBlock = llvm::BasicBlock::Create(context, "if_false", currentFunc);
    llvm::BasicBlock* contBlock = llvm::BasicBlock::Create(context, "if_cont", currentFunc);

    // Branch based on condition
    builder->CreateCondBr(cond, trueBlock, falseBlock);

    // True branch
    builder->SetInsertPoint(trueBlock);
    if (ifStmt->trueBlock)
        buildBlock(ifStmt->trueBlock);
    builder->CreateBr(contBlock);

    // False branch
    builder->SetInsertPoint(falseBlock);
    if (ifStmt->falseBlock)
        buildBlock(ifStmt->falseBlock);
    builder->CreateBr(contBlock);

    // Continue after if
    builder->SetInsertPoint(contBlock);
}

void LLVMBuilder::buildRepeat(stc::RepeatStatement *repeatStm)
{
    // Pop loop count from stack
    llvm::Value* countStruct = pop();
    llvm::Value* countType = builder->CreateExtractValue(countStruct, 0);
    llvm::Value* countValue = builder->CreateExtractValue(countStruct, 1);

    // Check type is int (STC_I64_TYPE)
    llvm::Value* isIntType = builder->CreateICmpEQ(countType, builder->getInt8(STC_I64_TYPE));

    llvm::Function* currentFunc = builder->GetInsertBlock()->getParent();
    llvm::BasicBlock* loopCheckBlock = llvm::BasicBlock::Create(context, "repeat_check", currentFunc);
    llvm::BasicBlock* loopBodyBlock = llvm::BasicBlock::Create(context, "repeat_body", currentFunc);
    llvm::BasicBlock* loopEndBlock = llvm::BasicBlock::Create(context, "repeat_end", currentFunc);
    llvm::BasicBlock* errorBlock = llvm::BasicBlock::Create(context, "repeat_type_error", currentFunc);

    // Only enter loop if type is int, else throw
    builder->CreateCondBr(isIntType, loopCheckBlock, errorBlock);

    // Error block: throw exception
    //TO-DO: Replace with proper error handling
    builder->SetInsertPoint(errorBlock);
    llvm::FunctionCallee printfFunc = getPrintfFunction();
    llvm::GlobalVariable* formatStr = getOrCreatePrintfFormatStr("Repeat expects int type!\n");
    llvm::Value *zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
    llvm::Value *indices[] = {zero, zero};
    llvm::Value *formatStrPtr = builder->CreateInBoundsGEP(
        formatStr->getValueType(), formatStr, indices, "formatStrPtr");
    builder->CreateCall(printfFunc, {formatStrPtr});
    builder->CreateUnreachable();

    // Loop variables (no PHI)
    builder->SetInsertPoint(loopCheckBlock);
    llvm::AllocaInst* iVar = builder->CreateAlloca(builder->getInt64Ty(), nullptr, "i");
    builder->CreateStore(builder->getInt64(0), iVar);

    llvm::BasicBlock* loopCondBlock = llvm::BasicBlock::Create(context, "repeat_cond", currentFunc);
    builder->CreateBr(loopCondBlock);

    // Loop condition
    builder->SetInsertPoint(loopCondBlock);
    llvm::Value* iVal = builder->CreateLoad(builder->getInt64Ty(), iVar);
    llvm::Value* cond = builder->CreateICmpSLT(iVal, countValue);
    builder->CreateCondBr(cond, loopBodyBlock, loopEndBlock);

    // Loop body
    builder->SetInsertPoint(loopBodyBlock);
    if (repeatStm->LoopBlock)
        buildBlock(repeatStm->LoopBlock);
    llvm::Value* nextI = builder->CreateAdd(iVal, builder->getInt64(1));
    builder->CreateStore(nextI, iVar);
    builder->CreateBr(loopCondBlock);

    // Continue after loop
    builder->SetInsertPoint(loopEndBlock);
}
