# STC Runtime

This section describes the STC runtime system, including its core types, macros, helpers, and the mechanism for runtime libraries.

## Overview

The STC runtime provides essential types, macros, and helper functions for programs compiled with STC. It also supports extensibility via runtime libraries, which are loaded and linked at compile time to provide additional operators, helpers, and initialization routines.

## Runtime Libraries

Runtime libraries in STC are LLVM bitcode files (`.bc`) containing helper functions, operators, or initialization routines. These libraries are discovered, loaded, and linked by the compiler to extend the functionality of generated programs.

### How Runtime Libraries Work

- **Discovery**: The compiler scans a directory (default: `/tmp/stc/bin`) for `.bc` files.
- **Loading**: Each bitcode file is loaded as an LLVM module.
- **Function Extraction**: Functions with external linkage and special annotations (e.g., `helper`, `init`, `token:name`) are discovered and registered.
- **Declaration**: The functions are declared in the main module and linked for use during code generation.
- **Initialization**: Functions annotated with `init` are called at program startup (typically at the beginning of `main`).

### How to Create a Runtime Library

1. **Write C Code**: Implement your helper functions, operators, or initialization routines using the STC runtime header and macros. Functions should use the `stc_value` type for arguments and return values.
2. **Annotate Functions**: Use GCC's `__attribute__((annotate("...")))` to mark functions for the runtime system. Supported annotations:
   - `"helper"`: Marks a function as a general helper.
   - `"init"`: Marks a function to be called at program startup. (It is mandatory to have a `void` return type and no parameters. Each library can have one `init` function.)
   - `"token:NAME"`: Associates a function with an operator or token (e.g., `"token:+"` for addition).
   - Example:
     ```c
     
     stc_value helper my_helper(stc_value a, stc_value b) { /* ... */ }

     void init my_init() { /* ... */ }

     stc_value token("+") add_op(stc_value a, stc_value b) { /* ... */ }
     ```
3. **Compile to LLVM Bitcode**:
   - Use `clang` to compile your C source file to LLVM bitcode:
     ```
     clang -emit-llvm -c mylib.c -o mylib.bc -O2
     ```
   - Ensure your code includes the STC runtime header and uses the correct types/macros.
   - **Automatic Compilation:**  
     All C files in the `stc/lib` directory are automatically compiled to bitcode (`.bc`) by the build system (`stc/compile.sh`). You do not need to manually compile each library; just add your `.c` file to `stc/lib` and run the build.
4. **Install the Bitcode Library**:
   - The build system copies all compiled `.bc` files to the runtime library directory (default: `/tmp/stc/bin`):
     ```
     cp bin/*.bc /tmp/stc/bin/
     ```
   - The compiler will automatically discover and link all `.bc` files in this directory.

**Note:**  
- All functions must use external linkage and the correct annotations to be recognized.
- Initialization functions (`init`) are called at the start of `main`.
- Operator functions (`token:NAME`) are mapped to language operators and used during code generation.

For more advanced usage, see the provided macros for defining binary operations and vtables in the STC runtime header.

## Types

- **stc_i64**: 64-bit signed integer
- **stc_i32**: 32-bit signed integer
- **stc_i8**: 8-bit signed integer
- **stc_f64**: 64-bit floating point
- **stc_type**: 8-bit unsigned integer representing a type tag

### `stc_value`

```c
typedef struct {
    stc_type type;
    stc_i64 val;
} stc_value;
```
A tagged union for runtime values. `type` is one of the `STC_*_TYPE` constants.

## Type Tags

- `STC_I64_TYPE` (0)
- `STC_BOOL_TYPE` (1)
- `STC_I8_TYPE` (2)
- `STC_F64_TYPE` (3)
- `STC_STRING_TYPE` (4)
- `STC_ARRAY_TYPE` (5)
- `STC_REF_TYPE` (6)
- `STC_TYPE_TYPE` (7)
- `STC_STRUCT_TYPE` (8)

## Function Pointer Types

- `typedef stc_value (*stc_function_2_t)(stc_value, stc_value);`

## Macros

### Type Conversion

- `I64_TO_F64(i)`: Bit-cast int64 to double
- `F64_TO_I64(d)`: Bit-cast double to int64
- `I64_TO_STR(i)`: Cast int64 to string pointer

### Binary Operation Helpers

- `DEFINE_STC_I64_BINOP(name, op)`: Define a binary op for int64
- `DEFINE_STC_F64_BINOP(name, op)`: Define a binary op for float64
- `DEFINE_STC_F64_I64_BINOP(name, op)`: float64 op int64
- `DEFINE_STC_I64_F64_BINOP(name, op)`: int64 op float64
- `DEFINE_STC_BINOP(name, op)`: All of the above

### VTable Helpers

- `STC_CREATE_VTABLE(name, type)`: Create a vtable for binary ops
- `STC_ADD_TO_VTABLE_OPERATION(vtable, op_name)`: Add all overloads of an op to vtable

### Attributes

- `helper`, `init`, `token(name)`: GCC attributes for codegen/annotation

## Example: Defining an Addition Operation

```c
DEFINE_STC_BINOP(add, +)
```

This will generate all overloads for `add` on i64 and f64 types.

## Example: Creating and Using a VTable

```c
STC_CREATE_VTABLE(add_vtable, stc_function_2_t)
STC_ADD_TO_VTABLE_OPERATION(add_vtable, add)
```
