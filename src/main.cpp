
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

#include "LlvmBuilder.h"
using namespace llvm;
using namespace antlr4;
#include "cli/Cli.h"





int main(int argc, char** argv) {
    auto config = RunCLI(argc, argv);
    if (config.has_value())
    {
        const auto& cfg = config.value();

        auto file =cfg.inputFiles[0];

        std::ifstream stream;
        stream.open(file);
        ANTLRInputStream input(stream);
        StcLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        StcParser parser(&tokens);

        tree::ParseTree* tree = parser.prog();

        AstBuilder Abuilder;
        tree::ParseTreeWalker::DEFAULT.walk(&Abuilder, tree);

        auto program = &Abuilder.program;

        auto builder = LLVMBuilder(*program);
        auto module = builder.build();

        std::error_code EC;
        raw_fd_ostream out("main.ll", EC, sys::fs::OF_None);
        module->print(out, nullptr);
        out.close();

        std::cout << "✅ LLVM IR written to main.ll\n";

        // Compile to assembly using llc
        std::cout << "🔧 Running: llc main.ll -o main.s -relocation-model=pic\n";
        if (std::system("llc main.ll -o main.s -relocation-model=pic") != 0) {
            std::cerr << "❌ Error running app.llc\n";
            return 1;
        }

        // Compile to executable using clang
        std::cout << "🔧 Running: clang main.s -o main_exe -fPIE\n";
        if (std::system("clang main.s -o main_exe -fPIE" ) != 0) {
            std::cerr << "❌ Error running clang\n";
            return 1;
        }

        std::cout << "✅ Compilation complete. Run with ./main_exe\n";

    }
    return 0;
}
