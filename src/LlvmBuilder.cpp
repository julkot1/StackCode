#include "LlvmBuilder.h"

void LLVMBuilder::createValueStruct() {

    valueType = llvm::StructType::create(context, {i8Type, i64Type}, "Value");
}

void LLVMBuilder::createStackStorage() {
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

llvm::Value* LLVMBuilder::push(llvm::Value* val) {
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
    using namespace llvm;

    for (auto &[_, func] : program.functions)
    {
        func->buildFunctionDefinition(*builder, *module);
    }

    for (auto &[_, func] : program.functions)
    {
        buildFunction(func);
    }
    // FunctionType *funcType = FunctionType::get(builder->getInt32Ty(), false);
    // Function *mainFunc = Function::Create(funcType, Function::ExternalLinkage, "main", module.get());
    //
    // BasicBlock *entry = BasicBlock::Create(context, "entry", mainFunc);
    // builder->SetInsertPoint(entry);
    //
    // push(createStackValue(builder->getInt64(10), builder->getInt8(1)));
    //
    //
    // Value* poppedStruct = pop();
    //
    // Value* popped_cValue= builder->CreateExtractValue(poppedStruct, 1);
    // printInt(popped_cValue);
    // builder->CreateRet(ConstantInt::get(i32Type, 0));
    return module.get();
}

void LLVMBuilder::buildFunction(const std::unique_ptr<stc::Function> & func)
{
    for (auto &block: func->blocks)
    {
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, block->name, func->funcLLVM);
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
                break;
            case stc::REPEAT_STATEMENT:
                break;
            case stc::VAR_ASSIGNMENT:
                break;
            case stc::FUNCTION_CALL:
                break;
            case stc::OPERATION:
                break;
        }
    }
}

void  LLVMBuilder::buildPush(stc::PushOperation  *pushOperation)
{
    auto [type, value] = pushOperation->getLLVMToken(context);
    push(createStackValue(value, type));
}

