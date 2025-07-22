#include "RuntimeLibs.h"

#include "Program.h"


namespace fs = std::filesystem;

RuntimeLibs::RuntimeLibs(const std::string& directoryPath)
    : dirPath(directoryPath) {}

bool RuntimeLibs::isBitcodeFile(const fs::path& path) {
    return path.extension() == ".bc" && fs::is_regular_file(path);
}

bool RuntimeLib::linkModule(const std::string& filePath, llvm::Module& targetModule, llvm::LLVMContext& context) {
    if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
        std::cerr << "Error: Invalid file path: " << filePath << "\n";
        return false;
    }

    auto bufferOrErr = llvm::MemoryBuffer::getFile(filePath);
    if (!bufferOrErr) {
        std::cerr << "  Failed to read file: " << bufferOrErr.getError().message() << "\n";
        return false;
    }

    auto moduleOrErr = llvm::parseBitcodeFile(bufferOrErr.get()->getMemBufferRef(), context);
    if (!moduleOrErr) {
        llvm::handleAllErrors(moduleOrErr.takeError(), [](llvm::ErrorInfoBase& e) {
            llvm::errs() << "  Failed to parse bitcode: " << e.message() << "\n";
        });
        return false;
    }

    std::unique_ptr<llvm::Module> loadedModule = std::move(moduleOrErr.get());

    for (auto& F : loadedModule->functions()) {
        if (!F.isDeclaration() && F.hasExternalLinkage()) {
            if (!targetModule.getFunction(F.getName())) {
                llvm::FunctionType* funcType = F.getFunctionType();
                llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, F.getName(), &targetModule);
                std::cout << "  Declared: " << F.getName().str() << "\n";
            }
        }
    }

    llvm::Linker linker(targetModule);
    if (linker.linkInModule(std::move(loadedModule))) {
        std::cerr << "  Linking failed for: " << filePath << "\n";
        return false;
    }

    std::cout << "  Successfully linked: " << filePath << "\n";
    return true;
}



stc::FunctionMetadataType RuntimeLib::getFunctionMetadata(std::string &arg)
{
    if (arg == Runtime::HELPER_STRING)
    {
        return stc::FUNCTION_HELPER;
    }
    if (arg == Runtime::INIT_LIB_STRING)
    {
        return stc::FUNCTION_LIB_INIT;
    }
    if (arg.length() > Runtime::TOKEN_STRING.length())
    {
        if (arg.starts_with(Runtime::TOKEN_STRING))
        {
            return stc::FUNCTION_TOKEN;
        }
    }
    return stc::FUNCTION_GENERATED;
    //ERR
}


std::vector<std::unique_ptr<stc::Function>> RuntimeLib::addFunctions()
{
    std::map<std::string, std::unique_ptr<stc::Function>>  functions;
    using namespace llvm;
    for (GlobalVariable &GV : module->globals())
    {
        if (GV.getName() == "llvm.global.annotations")
            {
            if (const auto *CA = dyn_cast<ConstantArray>(GV.getInitializer()))
                {
                for (unsigned i = 0; i < CA->getNumOperands(); ++i)
                    {
                    if (const auto *Annotation = dyn_cast<ConstantStruct>(CA->getOperand(i)))
                    {
                        Value *FuncVal = Annotation->getOperand(0)->stripPointerCasts();
                        auto *F = dyn_cast<Function>(FuncVal);

                        std::vector<std::string> args;
                        for (unsigned i1 = 1; i1 < Annotation->getNumOperands()-1; ++i1)
                        {
                            auto *StrGV = dyn_cast<GlobalVariable>(
                           Annotation->getOperand(i1)->stripPointerCasts());
                            std::string AnnotationStr;
                            if (StrGV && StrGV->hasInitializer()) {
                                if (const auto *CDA = dyn_cast<ConstantDataArray>(StrGV->getInitializer())) {
                                    if (CDA->isString()) {
                                        AnnotationStr = CDA->getAsCString().str();
                                    }
                                }
                                args.push_back(AnnotationStr);
                            }

                        }

                        if (F)
                        {
                            if (functions.find(F->getName().str()) == functions.end())
                            {
                                auto func = std::make_unique<stc::Function>();
                                func->name=".stc."+F->getName().str();
                                func->funcLLVM = F;
                                for (auto &arg : args)
                                {
                                    auto type = getFunctionMetadata(arg);
                                    if (type == stc::FUNCTION_TOKEN)
                                    {
                                        const auto idx = arg.find_first_of(':');
                                        const auto name = arg.substr(idx + 1);
                                        func->metadata[type] = name;
                                    }
                                    else
                                    {
                                        func->metadata[type] = arg;
                                    }
                                }
                                functions[F->getName().str()] = std::move(func);
                            }
                            else
                            {
                                for (auto &arg : args)
                                {
                                    auto type = getFunctionMetadata(arg);
                                    std::cout << arg << "\n";
                                    if (type == stc::FUNCTION_TOKEN)
                                    {
                                        const auto idx = arg.find_first_of(':');
                                        const auto name = arg.substr(idx + 1);
                                        functions[F->getName().str()]->metadata[type] = name;
                                    }
                                    else
                                    {
                                        functions[F->getName().str()]->metadata[type] = arg;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::vector<std::unique_ptr<stc::Function>>  functionsVec;
    for (auto &[k,v] : functions)
    {
        functionsVec.push_back(std::move(v));
    }
    return functionsVec;
}
bool RuntimeLibs::linkDirectory(const std::string& dirPath, llvm::Module& targetModule, llvm::LLVMContext& context) {
    if (!fs::is_directory(dirPath)) {
        std::cerr << "Error: Not a directory: " << dirPath << "\n";
        return false;
    }

    bool success = true;

    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (!entry.is_regular_file())
            continue;

        std::string filePath = entry.path().string();

        // Check for .bc file extension (bitcode)
        if (entry.path().extension() != ".bc")
            continue;

        std::cout << "Processing: " << filePath << "\n";
        auto lib = std::make_unique<RuntimeLib>();
        if (!lib->linkModule(filePath, targetModule, context)) {
            std::cerr << "  Failed to link module: " << filePath << "\n";
            success = false;
        }
        this->libraries.push_back(std::move(lib));
    }

    return success;
}
