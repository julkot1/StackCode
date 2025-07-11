//
// Created by julian on 7/10/25.
//

#ifndef CLI_H
#define CLI_H
#pragma once
#include <string>
#include <vector>
#include <optional>

struct CompilationConfig {
    std::string outFile = "out";
    int optimization = 0;
    bool emitLLVM = false;
    std::vector<std::string> inputFiles;
    std::string mode = "compile"; // or "libs"
};

std::optional<CompilationConfig> RunCLI(int argc, char** argv);

#endif //CLI_H
