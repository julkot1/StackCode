#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"

#include <cstdlib>  // for system()
#include <iostream>

#include "antlr4-runtime.h"
#include "antlr/StcLexer.h"
#include "antlr/StcParser.h"
#include "AstBuilder.h"

#include <fstream>
using namespace llvm;
using namespace antlr4;






int main() {
    std::ifstream stream;
    stream.open("app.rpn");
    ANTLRInputStream input(stream);
    StcLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    StcParser parser(&tokens);

    tree::ParseTree* tree = parser.prog();

    AstBuilder Abuilder;
    tree::ParseTreeWalker::DEFAULT.walk(&Abuilder, tree);


    LLVMContext context;
    IRBuilder<> builder(context);
    auto module = std::make_unique<Module>("my_module", context);

    // Create function: int main()
    FunctionType *funcType = FunctionType::get(builder.getInt32Ty(), false);
    Function *mainFunc = Function::Create(funcType, Function::ExternalLinkage, "main", module.get());

    // Create entry block
    BasicBlock *entry = BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);

    // Return 42
    Value *returnValue = builder.getInt32(42);
    builder.CreateRet(returnValue);

    // Write IR to file
    std::error_code EC;
    raw_fd_ostream out("main.ll", EC, sys::fs::OF_None);
    module->print(out, nullptr);
    out.close();

    std::cout << "✅ LLVM IR written to main.ll\n";

    // Compile to assembly using llc
    std::cout << "🔧 Running: llc main.ll -o main.s\n";
    if (std::system("llc main.ll -o main.s") != 0) {
        std::cerr << "❌ Error running j;l;lk.llc\n";
        return 1;
    }

    // Compile to executable using clang
    std::cout << "🔧 Running: clang main.s -o main_exe\n";
    if (std::system("clang main.s -o main_exe") != 0) {
        std::cerr << "❌ Error running clang\n";
        return 1;
    }

    std::cout << "✅ Compilation complete. Run with ./main_exe\n";

    return 0;
}
