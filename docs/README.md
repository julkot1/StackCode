# StackCode Docs
## Memu

* [Main Page](README.md)
* [Language](language.md)
* [Runtime](runtime.md)

## Introduction

StackCode is a stack-based, statically-typed programming language designed for simplicity :-) and performance (in future). It compiles to LLVM IR and supports a variety of types and operations, including arithmetic, logic, control flow, and user-defined functions and structures.

## Types

Supported types:
- `I64`: 64-bit signed integer
- `I8`: 8-bit signed integer
- `F64`: 64-bit floating point
- `Str`: String
- `Bool`: Boolean
- `Arr`: Array
- `Struct`: User-defined structure

## Syntax Overview

Functions are defined using the `fun` keyword:

```plaintext
fun main {
  // statements
}
```

Blocks are enclosed in `{ ... }`. Statements include operations, assignments, control flow, and function calls.

### Literals

- Integer: `42`, `-7`
- Float: `3.14`, `-2.5`
- Binary: `0b1010`
- Hexadecimal: `0xFF`
- Char: `'a'`
- String: `"hello"`
- Boolean: `true`, `false`

### Operators

Arithmetic: `+`, `-`, `*`, `/`, `%`

Logic: `<`, `>`, `<=`, `>=`, `==`, `!=`, `and`, `or`, `not`

Assignment: `:=`

Built-in: `typeof`, `len`, `call`, `copy`

### Stack Operations

- `dup`: Duplicate top value
- `rot`: Rotate top three values
- `swap`: Swap top two values
- `over`: Copy second value to top
- `pop`: Remove top value

### Control Flow

- `if { ... } else { ... }`: Conditional execution
- `repeat (n) { ... }`: Loop n times (n must be integer)

## Example

```plaintext
fun main {
  10 20 +
  dup
  if {
    "Result is nonzero" print
  } else {
    "Result is zero" print
  }
  5 repeat {
    "Loop iteration" print
  }
}
```

## Structures

Define custom types with `struct`:

```plaintext
struct Point {
  x <I64>
  y <I64>
}
```

## Summary

StackCode is designed for concise, stack-based computation with strong typing and extensibility via user-defined functions and structures.
