//
// Created by julian on 2/6/24.
//
#include "../include/vm.h"
#include "../include/functions.h"
#include <string.h>
#include <stdio.h>

function *find_main(program p);



void execute(program p)
{
    context *current_context;
    function *f = find_main(p);
    if(f == NULL)
    {
        fprintf(stderr, "No main function found!\n");
        exit(EXIT_FAILURE);
    }
    p.stack_ptr = 0;
    current_context = malloc(sizeof(context));
    current_context->fn = f;
    current_context->state = 0;
    current_context->parent = NULL;
    execute_function(current_context, &p);
    free(current_context);
}

void execute_function(context *current_context, program *p)
{
    for (; current_context->state < current_context->fn->code_size; current_context->state++)
    {
        execute_operation(((operation*)current_context->fn->code_addr)[current_context->state], p);
    }
    op_fun_end();
}

void op_fun_end() {

}

void execute_operation(operation op, program *p) {
    element a, b, c;
    switch (op.code)
    {
        case BIN_PUSH:
            op_push((element){.t = op.payload_type, .val = op.payload}, p);
            break;
        case BIN_POP:
            op_pop(p);
            break;
        case BIN_ADD:
            a = op_pop(p);
            b = op_pop(p);
            op_push(op_add(a,b, p), p);
            break;
        case BIN_DUMP:
            a = op_pop(p);
            op_dump(a, p);
            break;
        case BIN_SUB:
            op_push(op_sub(op_pop(p), op_pop(p), p), p);
            break;
        case BIN_DIV:
            op_push(op_div(op_pop(p), op_pop(p), p), p);
            break;
        case BIN_MUL:
            op_push(op_mul(op_pop(p), op_pop(p), p), p);
            break;
        case BIN_DUP:
            op_dup(p);
            break;
        case BIN_SWAP:
            op_swap(p);
            break;
        case BIN_JMP:
            op_jmp(op, p);
            break;
        case BIN_JMP_IF:
            op_jmp_if(op, p);
            break;
        case BIN_JMP_IF_NOT:
            op_jmp_if_not(op, p);
            break;
        case BIN_LABEL:
            op_label(op, p);
            break;
        case BIN_EQUAL:
            op_push(op_equal(op_pop(p), op_pop(p)), p);
            break;
        case BIN_NOT:
            op_push(op_not(op_pop(p)), p);
            break;
        case BIN_NOT_EQUAL:
            a = op_equal(op_pop(p), op_pop(p));
            a.val.byte = !((char)a.val.byte);
            op_push(a, p);
            break;
        case BIN_OR:
            op_push(op_or(op_pop(p), op_pop(p)), p);
            break;
        case BIN_AND:
            op_push(op_and(op_pop(p), op_pop(p)), p);
            break;
        case BIN_GREATER:
            op_push(op_greater(op_pop(p), op_pop(p)), p);
            break;
        case BIN_LOWER:
            op_push(op_lower(op_pop(p), op_pop(p)), p);
            break;
        case BIN_GREATER_OR_EQUAL:
            op_push(op_greater_or_equal(op_pop(p), op_pop(p)), p);
            break;
        case BIN_LOWER_OR_EQUAL:
            op_push(op_lower_or_equal(op_pop(p), op_pop(p)), p);
            break;
        case BIN_BITWISE_AND:
            op_push(op_bitwise_and(op_pop(p), op_pop(p)), p);
            break;
        case BIN_BITWISE_OR:
            op_push(op_bitwise_or(op_pop(p), op_pop(p)), p);
            break;
        case BIN_BITWISE_XOR:
            op_push(op_bitwise_xor(op_pop(p), op_pop(p)), p);
            break;
        case BIN_BITWISE_NOT:
            op_push(op_bitwise_not(op_pop(p)), p);
            break;
        case BIN_LEFT_SHIFT:
            op_push(op_left_shift(op_pop(p), op_pop(p)), p);
            break;
        case BIN_RIGHT_SHIFT:
            op_push(op_right_shift(op_pop(p), op_pop(p)), p);
            break;
        case BIN_TYPEOF:
            op_push((element){.t = TYPE, .val = (value){.number = op_pop(p).t}}, p);
            break;
        case BIN_MOD:
            op_push(op_mod(op_pop(p), op_pop(p)), p);
            break;
        case BIN_SIZEOF:
            op_push(op_sizeof(op_pop(p), p), p);
            break;
        case BIN_VLOAD:
            op_push(op_vload(op, p), p);
            break;
        case BIN_VSTORE:
            op_vstore(op_pop(p), op, p);
            break;
        case BIN_INPUT:
            break;
        case BIN_CALL:
            break;
        case BIN_ARR_NEW_STACK:
            break;
        case BIN_ARR_STORE:
            break;
        case BIN_ARR_APPEND:
            break;
        case BIN_ARR_LOAD:
            break;
        case BIN_EOP:
            exit(EXIT_SUCCESS);
            break;
    }
}



function *find_main(program p) {
    for (int i = 0; i < p.meta->functions_size; ++i) {
        if (strcmp(p.functions[i].name, "GLOBAL") == 0) {
            return &p.functions[i];
        }
    }
    return NULL;
}
