#pragma once
#include <jit/jit.h>
#include "main.h"

extern program *pr;
struct stack_element
{
    type t;
    payload_value val;
};
typedef struct stack_element (*function_ptr)(struct stack_element, struct stack_element);
typedef struct stack_element (*function_ptr_1)(struct stack_element);
typedef struct
{
    int args;
    opcode name;
    jit_type_t signature;
    function_ptr function;
} native_function;
void init_native(program *__pr);
void types_init();

extern struct stack_element
native_add(struct stack_element a, struct stack_element b);
extern struct stack_element native_sub(struct stack_element a, struct stack_element b);
extern struct stack_element native_div(struct stack_element a, struct stack_element b);
extern struct stack_element native_mul(struct stack_element a, struct stack_element b);
extern struct stack_element native_mod(struct stack_element a, struct stack_element b);

extern struct stack_element native_equal(struct stack_element a, struct stack_element b);
extern struct stack_element native_or(struct stack_element a, struct stack_element b);
extern struct stack_element native_and(struct stack_element a, struct stack_element b);
extern struct stack_element native_not_equal(struct stack_element a, struct stack_element b);
extern struct stack_element native_greater(struct stack_element a, struct stack_element b);
extern struct stack_element native_lower(struct stack_element a, struct stack_element b);
extern struct stack_element native_greater_or_equal(struct stack_element a, struct stack_element b);
extern struct stack_element native_lower_or_equal(struct stack_element a, struct stack_element b);
extern struct stack_element native_bitwise_or(struct stack_element a, struct stack_element b);
extern struct stack_element native_bitwise_and(struct stack_element a, struct stack_element b);
extern struct stack_element native_bitwise_xor(struct stack_element a, struct stack_element b);
extern struct stack_element native_left_shift(struct stack_element a, struct stack_element b);
extern struct stack_element native_right_shift(struct stack_element a, struct stack_element b);

extern struct stack_element native_not(struct stack_element a);
extern struct stack_element native_bitwise_not(struct stack_element a);
extern struct stack_element native_sizeof(struct stack_element a);
extern struct stack_element native_typeof(struct stack_element a);

extern void native_vstore(struct stack_element a, int index);
extern struct stack_element native_vload(int index);

#ifndef FUNC_PTR
#define FUNC_PTR
extern native_function native_functions[];
extern jit_type_t stack_element;
extern jit_uint stack_element_size;
extern jit_type_t stack_element_value;
extern jit_uint stack_element_value_size;
extern char *native_names[1024];
extern jit_type_t native_vstore_signature;
extern jit_type_t native_vload_signature;
#endif