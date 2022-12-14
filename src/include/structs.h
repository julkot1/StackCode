#pragma once
#include <stdbool.h>

typedef enum
{
    NUMBER,
    STRING,
    ARRAY,
    BOOL,
    VAR,
    VAR_EMPTY,
    OBJ,
    CHAR
} types;

typedef struct
{
    int begin, end, step, current;
    bool started;
} iterator;

// max size 8 bytes
typedef union
{
    long number;
    char ch;
    char *str;
    void *ptr;

} value;

typedef struct
{
    value val;
    types type;
} stack_element;

typedef struct
{
    char *name;
    value val;
    types type;

} variable;

typedef enum
{
    OP_PUSH,
    OP_POP,
    OP_SWAP,
    OP_DUP,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_EQ,
    OP_GT,
    OP_PRINT,
    OP_PUT,
    OP_IF,
    OP_LET,
    OP_END,
    OP_OVER,
    OP_ELSE,
    OP_WHILE,
    OP_BEGIN,
    OP_ITER,
    OP_ARRAY_BEGIN,
    OP_ARRAY_END,
    OP_LT,
    OP_NONE
} opcode;
typedef struct op_node op_node;
typedef struct
{
    int id;
    opcode code;
    stack_element arg, arg2;
    iterator it;
    op_node *node;
} operation;

struct op_node
{
    operation val;
    op_node *next;
};

typedef struct
{
    op_node *begin;
    op_node *tail;
    int size;
    op_node **op_ptr;
} program;
