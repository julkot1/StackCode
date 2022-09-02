#pragma once
#include "structs.h"

#define type_pair(a, b, t1, t2) ((a.type == t1 && b.type == t2) || (a.type == t2 && b.type == t1))

#define STACK_SIZE 4096

#ifndef STACK
#define STACK
stack_element stack[STACK_SIZE];
#endif

#ifndef STACK_PUSH
#define STACK_PUSH
#define push(el) stack[++ptr] = el;
#endif

#ifndef STACK_POP
#define STACK_POP
#define pop() stack[ptr--]
#endif

#ifndef STACK_SWAP
#define STACK_SWAP
#define swap()                   \
    {                            \
        stack_element a = pop(); \
        stack_element b = pop(); \
        push(a);                 \
        push(b);                 \
    }
#endif

#ifndef STACK_DUP
#define STACK_DUP
#define dup() push(stack[ptr])
#endif

#ifndef STACK_OVER
#define STACK_OVER
#define over() push(stack[ptr - 1])
#endif

void add();
void sub();
void mod();
void exec_div();
void mul();
void eq();
void gt();
void print();
void exec_if(operation op);
void exec_end(operation op);
void exec_while(operation op);
void exec_else(operation op);
void exec_operation(operation op);
void exec(program pr);