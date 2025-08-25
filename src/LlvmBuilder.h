//
// Created by julian on 7/10/25.
//

#ifndef LLVMBUILDER_H
#define LLVMBUILDER_H

#include "Program.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include "RuntimeLibs.h"
#include "IdentifierManager.h"

class LLVMBuilder {
public:
    const stc::Program *program;

    RuntimeLibs runtimeLib;

    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;


    llvm::StructType* valueType = nullptr;
    llvm::GlobalVariable* stackStorage = nullptr;
    llvm::GlobalVariable* stackPtr = nullptr;

    llvm::Type* i8Type = nullptr;
    llvm::Type* i64Type = nullptr;
    llvm::Type* i32Type = nullptr;

    std::map<stc::OperatorType, stc::Function*> operatorMap;
    IdentifierManager identifierManager;
    void createOperatorMap();
    void createValueStruct();
    void createStackStorage();
    void createStackPtr();
    void loadRuntimeLib();
    void initLibs() const;

    void linkLibs();

    llvm::Value* push(llvm::Value* val) const;
    llvm::Value* pop() const;

    llvm::Value* createStackValue(llvm::Value* value, llvm::Value* type) const;

    llvm::FunctionCallee getPrintfFunction();
    llvm::GlobalVariable* getOrCreatePrintfFormatStr(const std::string& fmtStr);
    void printInt(llvm::Value* intValue);


    explicit LLVMBuilder(const stc::Program *program)
        : program(program),
          module(std::make_unique<llvm::Module>("stc_module", context)),
          builder(std::make_unique<llvm::IRBuilder<>>(context)),
          runtimeLib(RuntimeLibs(LIB_PATH))
    {
         identifierManager = IdentifierManager();
         i8Type = llvm::Type::getInt8Ty(context);
         i64Type = llvm::Type::getInt64Ty(context);
         i32Type = llvm::Type::getInt32Ty(context);
    }

    void buildPush(stc::PushOperation  *pushOperation);

    void buildOperation(const stc::Operator * operation);

    void buildIf(stc::IfStatement * ifStm);

    void buildRepeat(stc::RepeatStatement * repeatStm);


    void buildBlock(const std::unique_ptr<stc::Block> & block);

    void buildFunction(const std::unique_ptr<stc::Function> & func);

    void buildIdentifier(const stc::Identifier * identifier);

    llvm::Module* build();


    llvm::GlobalVariable* getStackStorage() const { return stackStorage; }
    llvm::GlobalVariable* getStackPtr() const { return stackPtr; }
    llvm::StructType* getValueType() const { return valueType; }

};



#endif //LLVMBUILDER_H
