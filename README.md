# StackCode

C++ rewrite of [StackCode compiler in Go](https://github.com/julkot1/rpn-lang) with LLVM 20 and Antlr4

## Overview

StackCode is a stack-based programming language and compiler, inspired by Reverse Polish Notation (RPN) languages. This project reimplements the original Go-based StackCode compiler in C++, leveraging LLVM 20 for code generation and Antlr4 for parsing.

## Features

- Stack-based execution model
- LLVM IR code generation
- Support for arithmetic, logic, and custom operations
- Extensible operator and function system

## Language Documentation

For detailed information about the StackCode language syntax, semantics, and standard library, see the [official StackCode documentation](https://stackcodedoc.netlify.app/docs/category/language).

## Dependencies

- LLVM 20
- Antlr4 (C++ runtime)
- CMake (build system)
- A C++20 compatible compiler


## Usage

Compile a StackCode source file:

```sh
./stackcode compile <source-file.rpn>
```

## License

MIT License. See [LICENSE](./LICENSE) for details.
