# STC C Runtime Header

This header defines the core types, macros, and helpers for the STC runtime.

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
- `STC_ADD_TO_VTABLE(vtable, type_a, type_b, function)`: Add function to vtable
- `STC_ADD_TO_VTABLE_OPERATION(vtable, op_name)`: Add all overloads of an op to vtable

### Attributes

- `helper`, `lib_init`, `token(name)`: GCC attributes for codegen/annotation

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
