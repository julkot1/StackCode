#include "Cli.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <cxxopts.hpp>

std::optional<CompilationConfig> RunCLI(int argc, char** argv) {
    if (argc < 2) {
        std::cout << R"(
Usage: stc <command> [options]

Commands:
  compile     Compile program files
  libs        Compile stc default libs

Run 'stc <command> --help' for detailed options of a command.
)";
        return std::nullopt;
    }

    std::string command = argv[1];

    // Check for global help flags before commands
    if (command == "-h" || command == "--help") {
        std::cout << R"(
Usage: stc <command> [options]

Commands:
  compile     Compile program files
  libs        Compile stc default libs

Run 'stc <command> --help' for detailed options of a command.
)";
        return std::nullopt;
    }

    CompilationConfig cfg;

    if (command == "compile") {
        cfg.mode = "compile";
        cxxopts::Options options("stc compile", "Compile program to executable");
        options.add_options()
            ("o,output", "Output file", cxxopts::value<std::string>()->default_value("out"))
            ("O,opt", "Optimization level (0–3)", cxxopts::value<int>()->default_value("0"))
            ("l,emit-llvm", "Emit LLVM IR", cxxopts::value<bool>()->default_value("false"))
            ("files", "Input files", cxxopts::value<std::vector<std::string>>())
            ("h,help", "Show help");

        options.parse_positional({"files"});
        auto result = options.parse(argc - 1, argv + 1);

        if (result.count("help") || !result.count("files")) {
            std::cout << options.help() << std::endl;
            return std::nullopt;
        }

        cfg.outFile = result["output"].as<std::string>();
        cfg.optimization = result["opt"].as<int>();
        cfg.emitLLVM = result["emit-llvm"].as<bool>();
        cfg.inputFiles = result["files"].as<std::vector<std::string>>();

        if (cfg.optimization < 0 || cfg.optimization > 3) {
            std::cerr << "Error: -O level must be between 0 and 3\n";
            return std::nullopt;
        }

    } else if (command == "libs") {
        cfg.mode = "libs";

        // Optional: allow --help on libs to print info (if you want)
        if (argc > 2) {
            std::string arg2 = argv[2];
            if (arg2 == "-h" || arg2 == "--help") {
                std::cout << "Usage: stc libs\n"
                             "Compile stc default libraries.\n";
                return std::nullopt;
            }
        }

    } else {
        std::cerr << "Unknown command: " << command << "\n";
        std::cerr << "Run 'stc --help' for usage.\n";
        return std::nullopt;
    }

    return cfg;
}
