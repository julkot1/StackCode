#include "./include/vm.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#ifndef STACK_PTR
#define STACK
unsigned int ptr = -1;
#endif

#ifndef STACK_IDX
#define STACK
int idx = 0;
#endif

void add()
{
    stack_element a = pop();
    stack_element b = pop();
    stack_element res;
    if (a.type == NUMBER && b.type == NUMBER)
    {
        res.type = NUMBER;
        res.val.number = a.val.number + b.val.number;
    }
    else if (type_pair(a, b, NUMBER, BOOL))
    {
        res.type = NUMBER;
        res.val.number = a.val.number + b.val.number;
    }
    else
        perror("not implemented");
    push(res);
}
void sub()
{
    stack_element a = pop();
    stack_element b = pop();
    stack_element res;
    if (a.type == NUMBER && b.type == NUMBER)
    {
        res.type = NUMBER;
        res.val.number = a.val.number - b.val.number;
    }
    else
        perror("not implemented");
    push(res);
}
void mod()
{
    stack_element a = pop();
    stack_element b = pop();
    stack_element res;
    if (a.type == NUMBER && b.type == NUMBER)
    {
        res.type = NUMBER;
        res.val.number = a.val.number % b.val.number;
    }
    else
        perror("not implemented");
    push(res);
}
void exec_div()
{
    stack_element a = pop();
    stack_element b = pop();
    stack_element res;
    if (a.type == NUMBER && b.type == NUMBER)
    {
        if (b.val.number == 0)
        {
            perror("divide by 0");
            exit(EXIT_FAILURE);
        }
        res.type = NUMBER;
        res.val.number = a.val.number / b.val.number;
    }
    else
        perror("not implemented");
    push(res);
}
void mul()
{
    stack_element a = pop();
    stack_element b = pop();
    stack_element res;
    if (a.type == NUMBER && b.type == NUMBER)
    {
        res.type = NUMBER;
        res.val.number = a.val.number * b.val.number;
    }
    else
        perror("not implemented");
    push(res);
}
void eq()
{
    stack_element a = pop();
    stack_element b = pop();
    stack_element res;
    if (a.type == NUMBER && b.type == NUMBER)
    {
        res.type = BOOL;
        res.val.number = a.val.number == b.val.number;
    }
    else
        perror("not implemented");
    push(res);
}
void gt()
{
    stack_element a = pop();
    stack_element b = pop();
    stack_element res;
    if (a.type == NUMBER && b.type == NUMBER)
    {
        res.type = BOOL;
        res.val.number = a.val.number > b.val.number;
    }
    else
        perror("not implemented");
    push(res);
}
void print()
{

    stack_element a = pop();
    if (a.type == NUMBER)
    {
        printf("%d", a.val.number);
    }
    else if (a.type == BOOL)
        puts(a.val.ch == 0 ? "false" : "true");
    else if (a.type == CHAR)
        putchar(a.val.ch);
    else if (a.type == STRING)
        puts(a.val.str);
}
void exec_if(operation op)
{
    stack_element a = pop();
    if (a.type != BOOL)
    {
        perror("not a bool value");
        exit(EXIT_FAILURE);
    }
    if (a.val.number == 0)
        idx = op.arg.val.number;
}
void exec_end(operation op)
{
    if (op.arg.val.number != -1)
        idx = op.arg.val.number;
}
void exec_while(operation op)
{
    stack_element a = pop();
    if (a.type != BOOL)
    {
        perror("not a bool value");
        exit(EXIT_FAILURE);
    }
    if (a.val.number == 0)
        idx = op.arg.val.number + 1;
}
void exec_else(operation op)
{
    stack_element a = pop();
    if (a.type != BOOL)
    {
        perror("not a bool value");
        exit(EXIT_FAILURE);
    }
    if (a.val.number == 0)
        idx = op.arg.val.number;
}

void exec_operation(operation op)
{
    if (op.code == OP_PUSH)
    {
        push(op.arg);
    }
    else if (op.code == OP_POP)
    {
        pop();
    }
    else if (op.code == OP_ADD)
        add();
    else if (op.code == OP_SWAP)
    {
        swap();
    }
    else if (op.code == OP_DUP)
    {
        dup();
    }
    else if (op.code == OP_SUB)
        sub();
    else if (op.code == OP_DIV)
        exec_div();
    else if (op.code == OP_MUL)
        mul();
    else if (op.code == OP_MOD)
        mod();
    else if (op.code == OP_EQ)
        eq();
    else if (op.code == OP_GT)
        gt();
    else if (op.code == OP_PRINT)
        print();
    else if (op.code == OP_IF)
        exec_if(op);
    else if (op.code == OP_END)
        exec_end(op);
    else if (op.code == OP_WHILE)
        exec_while(op);
    else if (op.code == OP_BEGIN)
    {
    }
    else
        perror("not implemented");
}
void exec(program pr)
{
    while (idx < pr.size)
    {
        exec_operation((pr.op_ptr[idx])->val);
        idx++;
    }
}