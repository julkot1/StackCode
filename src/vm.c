#include "include/vm.h"
#include <stdlib.h>
#include "include/functions.h"
context *current_context;

inline void init()
{
    __p->stack = malloc(sizeof(struct stack_element) * __p->meta.stack_size);
    __p->labels = malloc(sizeof(int) * __p->meta.labels_size);
    __p->ptr = 0;
}
inline void labels_init()
{
}
void print_stack(int tick, operation op)
{
    printf("tick: %d operation: %d ptr: %ld\n", tick, op.code, __p->ptr);
    for (size_t i = 0; i < __p->ptr; i++)
    {
        printf("| %ld (%d) ", __p->stack[i].val.number, __p->stack[i].t);
    }
    printf("\n");
}
void parse_function()
{
    for (; current_context->state < current_context->fn->code_size; current_context->state++)
    {
        parse(current_context->fn->code[current_context->state]);
    }
    op_fun_end();
}
void parse_program()
{
    current_context = malloc(sizeof(context));
    current_context->fn = &__p->functions[GLOBAL_FUNCTION_ID];
    current_context->state = 0;
    current_context->parent = NULL;
    parse_function();
}

inline void op_dup()
{
    __p->stack[__p->ptr] = __p->stack[__p->ptr - 1];
    __p->ptr++;
}
inline void op_swap()
{
    struct stack_element a = op_pop();
    struct stack_element b = op_pop();
    __p->stack[__p->ptr++] = a;
    __p->stack[__p->ptr++] = b;
}
inline void op_push(operation op)
{
    __p->stack[__p->ptr++] = (struct stack_element){.t = op.payload_type, .val = op.payload};
}
inline void op_label(operation op)
{
    __p->labels[op.payload.number] = current_context->state;
}
inline void op_jmp(operation op)
{
    current_context->state = __p->labels[op.payload.number];
}
inline void op_jmp_if(operation op)
{
    struct stack_element a = op_pop();
    if (a.val.number)
        current_context->state = __p->labels[op.payload.number];
}
inline void op_jmp_if_not(operation op)
{
    struct stack_element a = op_pop();
    if (!a.val.number)
        current_context->state = __p->labels[op.payload.number];
}

inline void op_fun_call(operation op)
{
    context *tmp = current_context;
    current_context = malloc(sizeof(context));
    current_context->fn = &__p->functions[op.payload.number];
    current_context->parent = tmp;
    current_context->state = 0;
    parse_function();
}
inline void op_fun_end()
{
    if (current_context->parent == NULL)
        return;
    context *tmp = current_context;
    current_context = current_context->parent;
    free(tmp);
}
inline struct stack_element op_pop()
{
    return __p->stack[--__p->ptr];
}

void parse(operation op)
{

    char c;
    short s;
    int i;
    long l;

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
        op_label(op);
        break;
    case BIN_JMP:
        op_jmp(op);
        break;
    case BIN_JMP_IF:
        op_jmp_if(op);
        break;
    case BIN_JMP_IF_NOT:
        op_jmp_if_not(op);
        break;
    case BIN_VLOAD:
        __p->stack[__p->ptr++] = op_vload(op.payload.number);
        break;
    case BIN_VSTORE:
        op_vstore(op_pop(), op.payload.number);
        break;
    case BIN_CALL:
        op_fun_call(op);
        break;
    case BIN_DUMP:
        op_std_out(op_pop());
        break;
    case BIN_ADD:
        __p->stack[__p->ptr++] = op_add(op_pop(), op_pop());
        break;
    case BIN_SUB:
        __p->stack[__p->ptr++] = op_sub(op_pop(), op_pop());
        break;
    case BIN_DIV:
        __p->stack[__p->ptr++] = op_div(op_pop(), op_pop());
        break;
    case BIN_MUL:
        __p->stack[__p->ptr++] = op_mul(op_pop(), op_pop());
        break;
    case BIN_MOD:
        __p->stack[__p->ptr++] = op_mod(op_pop(), op_pop());
        break;
    case BIN_EQUAL:
        __p->stack[__p->ptr++] = op_equal(op_pop(), op_pop());
        break;
    case BIN_OR:
        __p->stack[__p->ptr++] = op_or(op_pop(), op_pop());
        break;
    case BIN_AND:
        __p->stack[__p->ptr++] = op_and(op_pop(), op_pop());
        break;
    case BIN_NOT_EQUAL:
        __p->stack[__p->ptr++] = op_not_equal(op_pop(), op_pop());
        break;
    case BIN_GREATER:
        __p->stack[__p->ptr++] = op_greater(op_pop(), op_pop());
        break;
    case BIN_LOWER:
        __p->stack[__p->ptr++] = op_lower(op_pop(), op_pop());
        break;
    case BIN_GREATER_OR_EQUAL:
        __p->stack[__p->ptr++] = op_greater_or_equal(op_pop(), op_pop());
        break;
    case BIN_LOWER_OR_EQUAL:
        __p->stack[__p->ptr++] = op_lower_or_equal(op_pop(), op_pop());
        break;
    case BIN_BITWISE_OR:
        __p->stack[__p->ptr++] = op_bitwise_or(op_pop(), op_pop());
        break;
    case BIN_BITWISE_AND:
        __p->stack[__p->ptr++] = op_bitwise_and(op_pop(), op_pop());
        break;
    case BIN_BITWISE_XOR:
        __p->stack[__p->ptr++] = op_bitwise_xor(op_pop(), op_pop());
        break;
    case BIN_LEFT_SHIFT:
        __p->stack[__p->ptr++] = op_left_shift(op_pop(), op_pop());
        break;
    case BIN_RIGHT_SHIFT:
        __p->stack[__p->ptr++] = op_right_shift(op_pop(), op_pop());
        break;
    case BIN_NOT:
        __p->stack[__p->ptr++] = op_not(op_pop());
        break;
    case BIN_BITWISE_NOT:
        __p->stack[__p->ptr++] = op_bitwise_not(op_pop());
        break;
    case BIN_SIZEOF:
        __p->stack[__p->ptr++] = op_sizeof(op_pop());
        break;
    case BIN_TYPEOF:
        __p->stack[__p->ptr++] = op_typeof(op_pop());
        break;
    default:

        break;
    }
}
