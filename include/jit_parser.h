#include <jit/jit.h>
#include "main.h"
#include "jit_native.h"
#ifndef PARSER
#define PARSER

#define CONST_UBYTE(v) (jit_value_create_nint_constant(GLOBAL_F, jit_type_nint, v))
#define CONST_BYTE(v) (jit_value_create_nint_constant(GLOBAL_F, jit_type_ubyte, v))
#define CONST_INT(v) (jit_value_create_nint_constant(GLOBAL_F, jit_type_sys_int, v))
#define CONST_LONG(v) (jit_value_create_long_constant(GLOBAL_F, jit_type_sys_long, v))
#define CONST_PTR(v) (jit_value_create_long_constant(GLOBAL_F, jit_type_void_ptr, v))

void init();
void labels_init();

void parse_program();
void parse_function(function *fn);
void init_function(function *fn);
void compile_function(function *fn);

void parse(operation op);
void op_native(native_function native_f);
void op_native_1(native_function native_f);
void op_native_2(native_function native_f);
void op_dup();
void op_swap();
void op_push(operation op);
void op_label(operation op, jit_label_t *labels);
void op_jmp(operation op, jit_label_t *labels);
void op_jmp_if(operation op, jit_label_t *labels);
void op_jmp_if_not(operation op, jit_label_t *labels);
void op_push_jit(jit_value_t val);
void op_push(operation op);
void op_vload(operation op);
void op_vstore(operation op);
void op_fun_call(operation op);
void op_fun_end();
jit_value_t op_pop();
#endif