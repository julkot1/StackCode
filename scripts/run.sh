#!/bin/bash
set -euo pipefail

# Build if build folder or executable doesn't exist
if [ ! -d build ] || [ ! -f build/llvm_ir_gen ]; then
  echo "Build folder or executable not found. Building project..."
  ./scripts/build.sh
fi

# Run the LLVM IR generator executable
echo "Running LLVM IR generator..."
./build/src/llvm_ir_gen

# Assuming your program generates main.ll, compile and run it:
if [ -f main_exe ]; then
  ./main_exe
else
  echo "No main_exe found. Skipping compilation steps."
fi

