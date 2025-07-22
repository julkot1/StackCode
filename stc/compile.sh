#!/bin/bash

mkdir -p bin


find lib -maxdepth 1 -type f -name "*.c" | while read -r c_file; do
  base_name=$(basename "$c_file" .c)
  output_file="bin/${base_name}.bc"

  clang -emit-llvm -c "$c_file" -o "$output_file" -O2
  echo $c_file

  if [ $? -eq 0 ]; then
    echo "Compiled $c_file -> $output_file"
  else
    echo "Failed to compile $c_file"
  fi
done
