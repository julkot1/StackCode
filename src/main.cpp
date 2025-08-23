#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "antlr/StcLexer.h"
#include "antlr/StcParser.h"

#include "AstBuilder.h"
#include "cli/Cli.h"
#include "LlvmBuilder.h"


using namespace llvm;
using namespace antlr4;

int main(int argc, char** argv)
{
    auto config = RunCLI(argc, argv);
    if (config.has_value())
    {
        const auto& cfg = config.value();

        auto file = cfg.inputFiles[0];

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

        auto builder = LLVMBuilder(program);
        auto module = builder.build();

        // Use output name from -o flag, default to "main"
        std::string outBase = "main";
        if (!cfg.outFile.empty())
            outBase = cfg.outFile;

        std::string llFile = outBase + ".ll";
        std::string sFile = outBase + ".s";
        std::string exeFile = outBase;

        std::error_code EC;
        raw_fd_ostream out(llFile, EC, sys::fs::OF_None);
        module->print(out, nullptr);
        out.close();

        std::cout << "✅ LLVM IR written to " << llFile << "\n";

        // Compile to assembly using llc
        std::cout << "🔧 Running: llc " << llFile << " -o " << sFile << " -relocation-model=pic\n";
        std::string llcCmd = "llc " + llFile + " -o " + sFile + " -relocation-model=pic";
        if (std::system(llcCmd.c_str()) != 0) {
            std::cerr << "❌ Error running llc\n";
            return 1;
        }

        // Compile to executable using clang
        std::cout << "🔧 Running: clang " << sFile << " -o " << exeFile << " -fPIE\n";
        std::string clangCmd = "clang " + sFile + " -o " + exeFile + " -fPIE";
        if (std::system(clangCmd.c_str()) != 0) {
            std::cerr << "❌ Error running clang\n";
            return 1;
        }

        std::cout << "✅ Compilation complete. Run with ./" << exeFile << "\n";
    }
    return 0;
}
