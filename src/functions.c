//
// Created by julian on 2/6/24.
//
#include "../include/vm.h"
#include <string.h>
#include <stdio.h>
#include "../include/functions.h"
#include "stdlib.h"

element get_ptr(element a, program *p);

inline void op_push(element el, program *p)
{
    (p->stack)[p->stack_ptr++] = el;
}
inline element op_pop(program *p)
{
    element el = (p->stack)[--p->stack_ptr];
    if(el.t == PTR)el = get_ptr(el, p);
    return  el;
}
inline element op_add(element a, element b, program *p) {
    if(a.t == b.t)
    {
        if(a.t == NUMBER) return (element){.t = NUMBER, .val = (value){.number = a.val.number + b.val.number}};
    }
    return  (element){.t = a.t, .val = 0};
}
inline element op_sub(element a, element b, program *p)
{
    if(a.t == b.t)
    {
        if(a.t == NUMBER) return (element){.t = NUMBER, .val = (value){.number = a.val.number - b.val.number}};
    }
    return  (element){.t = a.t, .val = 0};
}
inline element op_div(element a, element b, program *p)
{
    if(a.t == b.t)
    {
        if(a.t == NUMBER) {
            if(b.val.number == 0)
            {
                fprintf(stderr, "Division by zero!\n");
                exit(EXIT_FAILURE);
            }
            return (element){.t = NUMBER, .val = (value){.number = a.val.number / b.val.number}};
        }
    }
    return  (element){.t = a.t, .val = 0};
}
inline element op_mul(element a, element b, program *p)
{
    if(a.t == b.t)
    {
        if(a.t == NUMBER) return (element){.t = NUMBER, .val = (value){.number = a.val.number * b.val.number}};
    }
    return  (element){.t = a.t, .val = 0};
}
inline element op_mod(element a, element b)
{
    if(a.t == NUMBER && b.t == NUMBER)
    {
        if(b.val.number == 0)
        {
            fprintf(stderr, "Division by zero!\n");
            exit(EXIT_FAILURE);
        }
        return (element){.t = NUMBER, .val = (value){.number = a.val.number % b.val.number}};
    }
    return  (element){.t = a.t, .val = 0};
}

inline void op_dup(program *p)
{
    op_push(p->stack[p->stack_ptr - 1], p);
}
inline void op_swap(program *p)
{
    element a = op_pop(p);
    element b = op_pop(p);
    op_push(a, p);
    op_push(b, p);

}
inline void op_label(operation op, program *p)
{

}
inline void op_jmp(operation op, program *p)
{

}
inline void op_jmp_if(operation op,program *p)
{

}
inline void op_jmp_if_not(operation op, program *p)
{

}
inline void op_dump(element a, program *p) {
    switch (a.t)
    {
        case NUMBER:
            printf("%d\n", a.val.number);
            break;
        case STRING:
            printf("%s\n", a.val.str);
            break;
        case BOOL:
            printf("%s\n", a.val.byte ? "true" : "false");
            break;
        case TYPE:
            printf("nil\n");
            break;
        case CHAR:
            printf("%c\n", a.val.byte);
            break;
        case PTR:
            printf("%lu\n", a.val.ptr);
            break;
        case ARRAY:
            break;
    }
}

element get_ptr(element a, program *p) {
    element result;
    if ((a.val.idx  >> (sizeof (size_t)*8-8)) == 0xA0)
    {
        size_t idx = a.val.idx - (CONST_POOL_ADDR_OFFSET << (sizeof (size_t)*8-8));
        pool_element  el = p->const_pool[idx];
        result = (element){.t = el.t, .val.ptr = (void *)el.addr};
    }
    return result;
}

inline element op_equal(element a, element b)
{
    if(a.t != b.t)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    switch (a.t)
    {
        case NUMBER:
            return (element){.t = BOOL, .val = (value){.byte = a.val.number == b.val.number}};
        case STRING:
            return (element){.t = BOOL, .val = (value){.byte = strcmp(a.val.str, b.val.str) == 0}};
        case BOOL:
            return (element){.t = BOOL, .val = (value){.byte = a.val.byte == b.val.byte}};
        case TYPE:
            return (element){.t = BOOL, .val = (value){.byte = 1}};
        case CHAR:
            return (element){.t = BOOL, .val = (value){.byte = a.val.byte == b.val.byte}};
        case PTR:
            return (element){.t = BOOL, .val = (value){.byte = a.val.ptr == b.val.ptr}};
        case ARRAY:
            return (element){.t = BOOL, .val = (value){.byte = a.val.all == b.val.all}};

    }
}
inline element op_or(element a, element b)
{
    if(a.t != BOOL || b.t != BOOL)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    return (element){.t = BOOL, .val = (value){.byte = a.val.byte || b.val.byte}};
}
inline element op_and(element a, element b)
{
    if(a.t != BOOL || b.t != BOOL)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    return (element){.t = BOOL, .val = (value){.byte = a.val.byte && b.val.byte}};
}

inline element op_greater(element a, element b)
{
    if(a.t != b.t)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    switch (a.t)
    {
        case NUMBER:
            return (element){.t = BOOL, .val = (value){.byte = a.val.number > b.val.number}};
        case CHAR:
            return (element){.t = BOOL, .val = (value){.byte = a.val.byte > b.val.byte}};
    }
    return (element){.t = BOOL, .val = (value){.byte = 0}};

}
inline element op_lower(element a, element b)
{
    if(a.t != b.t)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    switch (a.t)
    {
        case NUMBER:
            return (element){.t = BOOL, .val = (value){.byte = a.val.number < b.val.number}};
        case CHAR:
            return (element){.t = BOOL, .val = (value){.byte = a.val.byte < b.val.byte}};
    }
    return (element){.t = BOOL, .val = (value){.byte = 0}};
}
inline element op_greater_or_equal(element a, element b)
{
    if(a.t != b.t)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    switch (a.t)
    {
        case NUMBER:
            return (element){.t = BOOL, .val = (value){.byte = a.val.number >= b.val.number}};
        case CHAR:
            return (element){.t = BOOL, .val = (value){.byte = a.val.byte >= b.val.byte}};
    }
    return (element){.t = BOOL, .val = (value){.byte = 0}};
}
inline element op_lower_or_equal(element a, element b)
{
    if(a.t != b.t)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    switch (a.t)
    {
        case NUMBER:
            return (element){.t = BOOL, .val = (value){.byte = a.val.number <= b.val.number}};
        case CHAR:
            return (element){.t = BOOL, .val = (value){.byte = a.val.byte <= b.val.byte}};
    }
    return (element){.t = BOOL, .val = (value){.byte = 0}};
}
inline element op_bitwise_or(element a, element b)
{
    if(a.t != NUMBER && b.t != NUMBER)
    {
        return (element){.t = NUMBER, .val = (value){.number = 0}};
    }
    return (element){.t = NUMBER, .val = (value){.number = a.val.number | b.val.number}};
}
inline element op_bitwise_and(element a, element b)
{
    if(a.t != NUMBER && b.t != NUMBER)
    {
        return (element){.t = NUMBER, .val = (value){.number = 0}};
    }
    return (element){.t = NUMBER, .val = (value){.number = a.val.number & b.val.number}};
}
inline element op_bitwise_xor(element a, element b)
{
    if(a.t != NUMBER && b.t != NUMBER)
    {
        return (element){.t = NUMBER, .val = (value){.number = 0}};
    }
    return (element){.t = NUMBER, .val = (value){.number = a.val.number ^ b.val.number}};
}
inline element op_left_shift(element a, element b)
{
    if(a.t != NUMBER && b.t != NUMBER)
    {
        return (element){.t = NUMBER, .val = (value){.number = 0}};
    }
    return (element){.t = NUMBER, .val = (value){.number = a.val.number << b.val.number}};

}
inline element op_right_shift(element a, element b)
{
    if(a.t != NUMBER && b.t != NUMBER)
    {
        return (element){.t = NUMBER, .val = (value){.number = 0}};
    }
    return (element){.t = NUMBER, .val = (value){.number = a.val.number >> b.val.number}};
}
inline element op_not(element a)
{
    if(a.t != BOOL)
    {
        return (element){.t = BOOL, .val = (value){.byte = 0}};
    }
    return (element){.t = BOOL, .val = (value){.byte = !a.val.byte}};
}
inline element op_bitwise_not(element a)
{
    if(a.t != NUMBER)
    {
        return (element){.t = NUMBER, .val = (value){.number = 0}};
    }
    return (element){.t = NUMBER, .val = (value){.number = ~a.val.number}};
}
inline void op_vstore(element pop, operation op, program *p)
{
    element *el = &p->var_pool[op.payload.number];
    el->val = pop.val;
    el->t = pop.t;
}
inline element op_vload(operation op, program *p)
{
    element el = p->var_pool[op.payload.number];
    return el;
}
inline element op_sizeof(element a, program *p)
{
    if(a.t == STRING)
    {
        return (element){.t = NUMBER, .val = (value){.number = strlen(a.val.str)}};
    }

    return (element){.t = NUMBER, .val = (value){.number = 1}};
}
