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
#define LIB_PATH "stc/bin"
namespace Runtime
{
    const std::string HELPER_STRING = "helper";
    const std::string INIT_LIB_STRING = "helper";
    const std::string TOKEN_STRING = "token:";
}


class RuntimeLib
{
public:
    llvm::Module *module;

    stc::FunctionMetadataType getFunctionMetadata(std::string &arg);
    std::vector<std::unique_ptr<stc::Function>> addFunctions();
    bool linkModule(const std::string& filePath, llvm::Module& targetModule, llvm::LLVMContext& context);
};


class RuntimeLibs {
public:


    std::vector<std::unique_ptr<RuntimeLib>> libraries;
    RuntimeLibs(const std::string& directoryPath);
    bool linkDirectory(const std::string& dirPath, llvm::Module& targetModule, llvm::LLVMContext& context);



private:
    std::string dirPath;

    static bool isBitcodeFile(const std::filesystem::path& path);
};



#endif //RUNTIMELIB_H
