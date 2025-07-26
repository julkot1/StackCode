#pragma once

#include <stdint.h>
#include <string.h>


#define STC_I64_TYPE 0x0
#define STC_BOOL_TYPE 0x1
#define STC_I8_TYPE 0x2
#define STC_F64_TYPE 0x3
#define STC_STRING_TYPE 0x4
#define STC_ARRAY_TYPE 0x5
#define STC_REF_TYPE 0x6
#define STC_TYPE_TYPE 0x7
#define STC_STRUCT_TYPE 0x8


typedef int64_t stc_i64;
typedef int32_t stc_i32;
typedef int8_t stc_i8;

typedef double stc_f64;

typedef uint8_t stc_type;


typedef struct {
    stc_type type;
    stc_i64 val;
} stc_value;

#define helper __attribute__((annotate("helper")))
#define lib_init __attribute__((annotate("init")))
#define token(name) __attribute((annotate("token:" name)))

typedef stc_value (*stc_function_2_t)(stc_value, stc_value);

#define STC_TYPE_SIZE 9

#define STC_CREATE_VTABLE(name, type) type name[STC_TYPE_SIZE][STC_TYPE_SIZE];
#define STC_ADD_TO_VTABLE(vtable, type_a, type_b, function) vtable[type_a][type_b] = function;


#define I64_TO_F64(i) ({ \
    double _d; \
    int64_t _i = (i); \
    memcpy(&_d, &_i, sizeof(double)); \
    _d; \
})
#define F64_TO_I64(d) ({         \
    int64_t _i;                  \
    double _d = (d);             \
    memcpy(&_i, &_d, sizeof(double)); \
    _i;                         \
})

// Macros with explicit result_type argument
#define DEFINE_STC_I64_BINOP_TYPED(name, op, result_type) \
stc_value helper token(#name "I") name##_I64_I64(stc_value a, stc_value b) { \
    stc_value r = { .type = result_type, .val = a.val op b.val }; \
    return r; \
}

#define DEFINE_STC_F64_BINOP_TYPED(name, op, result_type) \
stc_value helper token(#name "F") name##_f64_f64(stc_value a, stc_value b) { \
    stc_f64 _a = I64_TO_F64(a.val); \
    stc_f64 _b = I64_TO_F64(b.val); \
    stc_value r = { .type = result_type, .val = F64_TO_I64(_a op _b) }; \
    return r; \
}

#define DEFINE_STC_F64_I64_BINOP_TYPED(name, op, result_type) \
stc_value helper token(#name "FI") name##_F64_I64(stc_value a, stc_value b) { \
    stc_i64 _a = a.val; \
    stc_f64 _b = I64_TO_F64(b.val); \
    stc_value r = { .type = result_type, .val = F64_TO_I64(_a op _b) }; \
    return r; \
}

#define DEFINE_STC_I64_F64_BINOP_TYPED(name, op, result_type) \
stc_value helper token(#name "IF") name##_I64_F64(stc_value a, stc_value b) { \
    stc_i64 _a = a.val; \
    stc_f64 _b = I64_TO_F64(b.val); \
    stc_value r = { .type = result_type, .val = F64_TO_I64(_a op _b) }; \
    return r; \
}

#define DEFINE_STC_BOOL_BINOP_TYPED(name, op) \
stc_value helper token(#name "B") name##_BOOL_BOOL(stc_value a, stc_value b) { \
    stc_value r = { .type = STC_BOOL_TYPE, .val = (a.val op b.val) }; \
    return r; \
}

// Macro for unary bool op
#define DEFINE_STC_BOOL_UNOP_TYPED(name, op) \
stc_value helper token(#name) name##_BOOL(stc_value a) { \
    stc_value r = { .type = STC_BOOL_TYPE, .val = (op a.val) }; \
    return r; \
}

#define DEFINE_STC_I64_BINOP(name, op) DEFINE_STC_I64_BINOP_TYPED(name, op, STC_I64_TYPE)
#define DEFINE_STC_F64_BINOP(name, op) DEFINE_STC_F64_BINOP_TYPED(name, op, STC_F64_TYPE)
#define DEFINE_STC_F64_I64_BINOP(name, op) DEFINE_STC_F64_I64_BINOP_TYPED(name, op, STC_F64_TYPE)
#define DEFINE_STC_I64_F64_BINOP(name, op) DEFINE_STC_I64_F64_BINOP_TYPED(name, op, STC_F64_TYPE)
#define DEFINE_STC_BOOL_BINOP(name, op) DEFINE_STC_BOOL_BINOP_TYPED(name, op)

// Default: result types match previous ones
#define DEFINE_STC_BINOP(name, op) \
    DEFINE_STC_I64_BINOP(name, op) \
    DEFINE_STC_F64_BINOP(name, op) \
    DEFINE_STC_F64_I64_BINOP(name, op) \
    DEFINE_STC_I64_F64_BINOP(name, op) \
    DEFINE_STC_BOOL_BINOP(name, op)

// Custom: user specifies result type for all combinations
#define DEFINE_STC_BINOP_TYPED(name, op, t) \
    DEFINE_STC_I64_BINOP_TYPED(name, op, t) \
    DEFINE_STC_F64_BINOP_TYPED(name, op, t) \
    DEFINE_STC_F64_I64_BINOP_TYPED(name, op, t) \
    DEFINE_STC_I64_F64_BINOP_TYPED(name, op, t) \
    DEFINE_STC_BOOL_BINOP_TYPED(name, op)


#define STC_ADD_TO_VTABLE_OPERATION(vtable, op_name) {\
    STC_ADD_TO_VTABLE(vtable, STC_I64_TYPE, STC_I64_TYPE, op_name##_I64_I64);\
    STC_ADD_TO_VTABLE(vtable, STC_F64_TYPE, STC_F64_TYPE, op_name##_f64_f64);\
    STC_ADD_TO_VTABLE(vtable, STC_I64_TYPE, STC_F64_TYPE, op_name##_I64_F64);\
    STC_ADD_TO_VTABLE(vtable, STC_F64_TYPE, STC_I64_TYPE, op_name##_F64_I64);\
    STC_ADD_TO_VTABLE(vtable, STC_BOOL_TYPE, STC_BOOL_TYPE, op_name##_BOOL_BOOL);\
}

#define I64_TO_STR(i) ((const char *)(uintptr_t)(i))
