#pragma once
#include <stdio.h>
#include <stdlib.h>

#define CONST_POOL_PTR -1

#ifndef MAIN
#define MAIN

typedef struct stack_element (*function2)(struct stack_element, struct stack_element);
typedef struct stack_element (*function1)(struct stack_element);
typedef enum
{
    BIN_PUSH,
    BIN_ADD,
    BIN_SUB,
    BIN_DIV,
    BIN_MUL,
    BIN_DUMP,
    BIN_POP,
    BIN_DUP,
    BIN_SWAP,
    BIN_JMP,
    BIN_JMP_IF,
    BIN_JMP_IF_NOT,
    BIN_LABEL,
    BIN_EQUAL,
    BIN_NOT,
    BIN_NOT_EQUAL,
    BIN_OR,
    BIN_AND,
    BIN_GREATER,
    BIN_LOWER,
    BIN_GREATER_OR_EQUAL,
    BIN_LOWER_OR_EQUAL,
    BIN_BITWISE_AND,
    BIN_BITWISE_OR,
    BIN_BITWISE_XOR,
    BIN_BITWISE_NOT,
    BIN_LEFT_SHIFT,
    BIN_RIGHT_SHIFT,
    BIN_TYPEOF,
    BIN_MOD,
    BIN_SIZEOF,
    BIN_VLOAD,
    BIN_VSTORE,
    BIN_INPUT,
    BIN_CALL,
    BIN_PTR_NEW,
    BIN_PTR_STORE,
    BIN_ARR_APPEND,
    BIN_EOP
} opcode;
typedef enum
{
    NUMBER,
    STRING,
    BOOL,
    CHAR,
    PTR,
    TYPE
} type;
typedef union
{
    int number;
    char byte;
    char *str;
    void *ptr;
    unsigned long all;
} payload_value;

typedef struct
{
    opcode code;
    type payload_type;
    payload_value payload;
} operation;
typedef struct op_node op_node;
struct op_node
{
    operation op;
    op_node *next;
};
typedef struct
{
    int operations_size;
    int labels_size;
    int stack_size;
    int const_pool_size;
    int var_pool_size;
    int functions_size;
    char **function_names;
} program_meta;
typedef struct
{
    type type;
    int static_element;
    size_t size;
    int ref_counter;
    void *val;
    payload_value static_val;
} pool_element;
struct stack_element
{
    type t;
    payload_value val;
};
typedef struct
{
    int ptr;
    pool_element *elements;
} pool;

typedef struct
{
    size_t length, head;
    struct stack_element *elements;
} array;
typedef struct
{
    int num_args;
    int is_returning;
    int id;
    int code_size;
    char name[32];
    operation *code;
} function;
typedef struct
{
    program_meta meta;
    pool const_pool;
    pool var_pool;
    int *labels;
    function *functions;

    struct stack_element *stack;
    size_t ptr;
} program;

typedef char word[32];

extern program *__p;
int main();
#endif