Sure! Here's a **detailed documentation in Markdown** format for your runtime header file. You can save it as `RUNTIME.md` or include it in your project's main documentation folder (`docs/`).

---

# `Header.h` – Runtime Header for Stack-Based Language (LLVM-Compatible)

## Overview

This header defines the **core types**, **macros**, and **helper utilities** used in the runtime of a custom stack-based language targeting LLVM IR. It provides a foundation for working with *dynamically typed values*, including type-safe binary operations and runtime dispatch through vtables.

---

## ✨ Features

### Tagged union type: `stc_value`

All values in the language are wrapped in a struct containing:

* a type tag (`stc_type`)
* a raw 64-bit value (`int64_t`), usable as integer, float, pointer, etc.

```c
typedef struct {
    stc_type type;
    stc_i64 val;
} stc_value;
```

---

### Built-in Type Tags

Each language-level type is assigned a unique `uint8_t` identifier.

```c
#define STC_I64_TYPE     0x0  // 64-bit signed integer
#define STC_BOOL_TYPE    0x1  // Boolean (as int64)
#define STC_I8_TYPE      0x2  // 8-bit signed integer
#define STC_F64_TYPE     0x3  // 64-bit float (double)
#define STC_STRING_TYPE  0x4  // Pointer to string (char*)
#define STC_ARRAY_TYPE   0x5  // Pointer to array (T[])
#define STC_REF_TYPE     0x6  // Boxed reference
#define STC_TYPE_TYPE    0x7  // Type descriptor
#define STC_STRUCT_TYPE  0x8  // User-defined struct
```

---

## Types

Short aliases for platform-specific fixed-width integers:

```c
typedef int64_t stc_i64;
typedef int32_t stc_i32;
typedef int8_t  stc_i8;
typedef double  stc_f64;
typedef uint8_t stc_type;
```

---

## Macros & Utilities

### Bitcast Between `int64_t` and `double`

Instead of using C-style casting (which changes value), this performs **raw memory reinterpretation** (bitcast), safe for IEEE 754 and portable:

```c
#define I64_TO_F64(i) ({ \
    double _d; \
    int64_t _i = (i); \
    memcpy(&_d, &_i, sizeof(double)); \
    _d; \
})

#define F64_TO_I64(d) ({ \
    int64_t _i; \
    double _d = (d); \
    memcpy(&_i, &_d, sizeof(double)); \
    _i; \
})
```

---

### VTable Definitions

Allows construction of 2D dispatch tables for binary operations, indexed by operand types:

```c
#define STC_TYPE_SIZE 9
#define STC_CREATE_VTABLE(name, type) type name[STC_TYPE_SIZE][STC_TYPE_SIZE];
#define STC_ADD_TO_VTABLE(vtable, type_a, type_b, function) \
    vtable[type_a][type_b] = function;
```

---

###  Function Annotation Helpers

Used for tagging runtime functions with metadata for the compiler/frontend tooling:

```c
#define helper    __attribute__((annotate("helper")))
#define lib_init  __attribute__((annotate("init")))
#define token(name) __attribute__((annotate("token:" name)))
```

---

### Binary Operation Macros

Auto-generate implementations of binary operations for all valid type combinations:

#### Integer only

```c
#define DEFINE_STC_I64_BINOP(name, op)
```

#### Float only (stored as int64)

```c
#define DEFINE_STC_F64_BINOP(name, op)
```

#### Mixed-type ops:

```c
#define DEFINE_STC_F64_I64_BINOP(name, op)
#define DEFINE_STC_I64_F64_BINOP(name, op)
```

#### All together:

```c
#define DEFINE_STC_BINOP(name, op)
```

Example:

```c
DEFINE_STC_BINOP(add, +)
```

This generates 4 functions:

* `add_int_int`
* `add_f64_f64`
* `add_F64_I64`
* `add_I64_F64`

---

### VTable Operation Injection

Auto-populate a vtable with all variants of an operation:

```c
#define STC_ADD_TO_VTABLE_OPERATION(vtable, op_name) { \
    STC_ADD_TO_VTABLE(vtable, STC_I64_TYPE, STC_I64_TYPE, op_name##_int_int); \
    STC_ADD_TO_VTABLE(vtable, STC_F64_TYPE, STC_F64_TYPE, op_name##_f64_f64); \
    STC_ADD_TO_VTABLE(vtable, STC_I64_TYPE, STC_F64_TYPE, op_name##_I64_F64); \
    STC_ADD_TO_VTABLE(vtable, STC_F64_TYPE, STC_I64_TYPE, op_name##_F64_I64); \
}
```

---

### String Helper

```c
#define I64_TO_STR(i) ((const char *)(uintptr_t)(i))
```

Converts an `int64_t` interpreted as a pointer to a C-string (`const char*`).

Used when string values are passed/stored via `val` field.

---

## Example Usage

### Define and register `add` operation:

```c
DEFINE_STC_BINOP(add, +)

STC_CREATE_VTABLE(add_vtable, stc_function_2_t)

void lib_init init() {
    STC_ADD_TO_VTABLE_OPERATION(add_vtable, add);
}
```

---

## Integration

This header is intended to be part of the **standard runtime library** of the language. The corresponding `.c` or `.cpp` file should define runtime helpers (`add`, `sub`, `print`, `compare`, etc.), compiled separately and linked with the LLVM-generated output.


---

## Summary

This runtime header forms the **core foundation** of a minimal, strongly-typed dynamic language built on a stack model and compiled to LLVM IR. It abstracts over type-safe operations, provides support for type-based function dispatch, and ensures consistent memory layout for low-level bit manipulation.

It allows rapid prototyping of language semantics while remaining low-level enough for fine-grained IR generation and optimization.