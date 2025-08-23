#ifndef RUNTIMELIB_H
#define RUNTIMELIB_H

#pragma once

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/raw_ostream.h>

#include <filesystem>
#include <string>
#include <iostream>
#include <map>
#include "Program.h"
#define LIB_PATH "/tmp/stc/bin"
namespace Runtime
{
    const std::string HELPER_STRING = "helper";
    const std::string INIT_LIB_STRING = "init";
    const std::string TOKEN_STRING = "token:";
}


class RuntimeLib
{
public:
    std::unique_ptr<llvm::Module> module;
    std::vector<std::unique_ptr<stc::Function>> functions;
    stc::Function* initFunction;
    stc::FunctionMetadataType getFunctionMetadata(std::string &arg);
    std::vector<std::unique_ptr<stc::Function>> addFunctions(llvm::Module& targetModule);

    bool loadModule(const std::string& filePath, llvm::Module& targetModule, llvm::LLVMContext& context);
    bool linkModule( llvm::Module& targetModule, llvm::LLVMContext& context);
    ~RuntimeLib() = default;
};


class RuntimeLibs {
public:


    std::vector<std::unique_ptr<RuntimeLib>> libraries;
    RuntimeLibs(const std::string& directoryPath);
    bool loadDirectory(const std::string& dirPath, llvm::Module& targetModule, llvm::LLVMContext& context);


private:
    std::string dirPath;

    static bool isBitcodeFile(const std::filesystem::path& path);
};



#endif //RUNTIMELIB_H
