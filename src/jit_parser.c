#include "include/jit_parser.h"
#include "include/vm.h"
#include <stdlib.h>
#include "include/jit_native.h"
jit_context_t context;
jit_function_t GLOBAL_F;
function *CURRENT_F;

void init(program *__pr)
{
    __pr->functions = malloc(sizeof(jit_function_t) * 10);
    jit_init();
    context = jit_context_create();
    init_native(__pr);
    types_init();
    labels_init(__pr);
}
void parse_program(program *__pr)
{
    for (int i = 0; i < __pr->meta.functions_size; i++)
    {
        jit_context_build_start(context);
        init_function(&(__pr->functions[i]));
        jit_context_build_end(context);
    }
    for (int i = 0; i < __pr->meta.functions_size; i++)
    {
        jit_context_build_start(context);
        parse_function(__pr, &(__pr->functions[i]));
        jit_context_build_end(context);
    }
    for (int i = __pr->meta.functions_size - 1; i >= 0; i--)
    {
        jit_context_build_start(context);
        // jit_dump_function(stdout, __pr->functions[i].fn, __pr->meta.function_names[__pr->functions[i].id]);
        jit_function_compile(__pr->functions[i].fn);
        jit_context_build_end(context);
    }
    jit_function_apply(__pr->functions[0].fn, NULL, NULL);
    jit_context_destroy(context);
    free(__pr->labels);
}
void parse_function(program *__pr, function *fn)
{
    CURRENT_F = fn;
    GLOBAL_F = fn->fn;
    op_node *op_n = fn->code;

    CURRENT_F->stack_ptr = jit_value_create(GLOBAL_F, jit_type_void_ptr);
    jit_insn_store(GLOBAL_F, CURRENT_F->stack_ptr, jit_insn_alloca(GLOBAL_F, CONST_INT((__pr->meta.stack_size * stack_element_size))));

    for (size_t i = 0; i < fn->code_size; i++)
    {
        parse((fn->code)[i], __pr);
    }
}

void init_function(function *fn)
{

    fn->fn = jit_function_create(context, jit_type_create_signature(jit_abi_cdecl, jit_type_void, NULL, 0, 1));
}
void compile_function(program *__pr, function *fn)
{

    jit_dump_function(stdout, fn->fn, __pr->meta.function_names[fn->id]);
    jit_function_compile(fn->fn);
}
void labels_init(program *__pr)
{
    __pr->labels = malloc(__pr->meta.labels_size * sizeof(jit_label_t));
    for (size_t i = 0; i < __pr->meta.labels_size; i++)
    {
        __pr->labels[i] = jit_label_undefined;
    }
}

void op_push_jit(jit_value_t val)
{

    jit_insn_store_relative(GLOBAL_F, CURRENT_F->stack_ptr, 0, val);
    jit_value_t new_ptr = jit_insn_add(GLOBAL_F, CURRENT_F->stack_ptr, CONST_INT(stack_element_size));
    jit_insn_store(GLOBAL_F, CURRENT_F->stack_ptr, new_ptr);
}

void op_push(operation op)
{
    jit_insn_store_relative(GLOBAL_F, CURRENT_F->stack_ptr, 0, CONST_INT(op.payload_type));
    jit_insn_store_relative(GLOBAL_F, CURRENT_F->stack_ptr, stack_element_value_size, CONST_LONG(op.payload.all));
    jit_value_t new_ptr = jit_insn_add(GLOBAL_F, CURRENT_F->stack_ptr, CONST_UBYTE(stack_element_size));
    jit_insn_store(GLOBAL_F, CURRENT_F->stack_ptr, new_ptr);
}

jit_value_t op_pop()
{

    jit_value_t val = jit_insn_load_relative(GLOBAL_F, CURRENT_F->stack_ptr, -stack_element_size, stack_element);
    jit_value_t new_ptr = jit_insn_sub(GLOBAL_F, CURRENT_F->stack_ptr, CONST_INT(stack_element_size));
    jit_insn_store(GLOBAL_F, CURRENT_F->stack_ptr, new_ptr);
    return val;
}
void op_swap()
{
    jit_value_t a = op_pop();
    jit_value_t b = op_pop();
    op_push_jit(a);
    op_push_jit(b);
}
void op_dup()
{
    jit_value_t a = op_pop();
    op_push_jit(a);
    op_push_jit(a);
}

void op_label(operation op, jit_label_t *labels)
{
    jit_insn_label(GLOBAL_F, &(labels[op.payload.number]));
}
void op_jmp(operation op, jit_label_t *labels)
{

    jit_insn_branch(GLOBAL_F, &(labels[op.payload.number]));
}
void op_jmp_if(operation op, jit_label_t *labels)
{
    jit_value_t a = jit_insn_address_of(GLOBAL_F, op_pop());
    jit_value_t a_union = jit_insn_load_relative(GLOBAL_F, jit_insn_address_of(GLOBAL_F, a), stack_element_size, jit_type_long);
    jit_value_t a_val = jit_insn_load_relative(GLOBAL_F, jit_insn_address_of(GLOBAL_F, a_union), 0, jit_type_int);
    jit_value_t eq = jit_insn_eq(GLOBAL_F, a_val, CONST_INT(0));
    jit_insn_branch_if(GLOBAL_F, eq, &(labels[op.payload.number]));
}
void op_jmp_if_not(operation op, jit_label_t *labels)
{
    jit_value_t a = jit_insn_address_of(GLOBAL_F, op_pop());
    jit_value_t a_union = jit_insn_load_relative(GLOBAL_F, jit_insn_address_of(GLOBAL_F, a), stack_element_size, jit_type_long);
    jit_value_t a_val = jit_insn_load_relative(GLOBAL_F, jit_insn_address_of(GLOBAL_F, a_union), 0, jit_type_int);
    jit_value_t eq = jit_insn_eq(GLOBAL_F, a_val, CONST_INT(0));
    jit_insn_branch_if_not(GLOBAL_F, eq, &(labels[op.payload.number]));
}

void op_native(native_function native_f)
{
    if (native_f.args == 1)
        op_native_1(native_f);
    else if (native_f.args == 2)
        op_native_2(native_f);
}
void op_native_1(native_function native_f)
{
    jit_value_t a = op_pop();
    jit_value_t res = jit_insn_call_native(
        GLOBAL_F, native_names[native_f.name], native_f.function, native_f.signature, &a, native_f.args, JIT_CALL_NOTHROW);

    op_push_jit(res);
}
void op_native_2(native_function native_f)
{
    jit_value_t a = op_pop();
    jit_value_t b = op_pop();
    jit_value_t args[] = {b, a};
    jit_value_t res = jit_insn_call_native(
        GLOBAL_F, native_names[native_f.name], native_f.function, native_f.signature, args, native_f.args, JIT_CALL_NOTHROW);
    op_push_jit(res);
}
void op_vload(operation op, program *__pr)
{
    jit_value_t index = CONST_INT(op.payload.number);
    jit_value_t args[] = {index};
    jit_value_t res = jit_insn_call_native(
        GLOBAL_F, "vload", native_vload, native_vload_signature, args, 1, JIT_CALL_NOTHROW);
    op_push_jit(res);
}
void op_vstore(operation op, program *__pr)
{
    jit_value_t element = op_pop();
    jit_value_t index = CONST_INT(op.payload.number);
    jit_value_t args[] = {element, index};
    jit_insn_call_native(
        GLOBAL_F, "vstore", native_vstore, native_vstore_signature, args, 2, JIT_CALL_NOTHROW);
}

void op_fun_call(operation op, program *__pr)
{

    int id = op.payload.number;
    jit_function_t fn = __pr->functions[id].fn;
    char *name = __pr->meta.function_names[id];
    jit_insn_call(GLOBAL_F, name, fn, jit_type_create_signature(jit_abi_cdecl, jit_type_void, NULL, 0, 1), NULL, 0, 0);
}

void parse(operation op, program *__pr)
{
    switch (op.code)
    {

    case BIN_PUSH:
        op_push(op);
        break;
    case BIN_POP:
        op_pop();
        break;
    case BIN_DUP:
        op_dup();
        break;
    case BIN_SWAP:
        op_swap();
        break;
    case BIN_LABEL:
        op_label(op, __pr->labels);
        break;
    case BIN_JMP:
        op_jmp(op, __pr->labels);
        break;
    case BIN_JMP_IF:
        op_jmp_if(op, __pr->labels);
        break;
    case BIN_JMP_IF_NOT:
        op_jmp_if_not(op, __pr->labels);
        break;
    case BIN_VLOAD:
        op_vload(op, __pr);
        break;
    case BIN_VSTORE:
        op_vstore(op, __pr);
        break;
    case BIN_CALL:
        op_fun_call(op, __pr);
        break;
    default:
        op_native(native_functions[op.code]);
        break;
    }
}
