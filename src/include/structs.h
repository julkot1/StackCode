#pragma once
typedef enum
{
    NUMBER,
    STRING,
    ARRAY,
    BOOL,
    CHAR
} types;
typedef union
{
    int number;
    char ch;
    char *str;
    void *arr;
} value;

typedef struct
{
    value val;
    types type;
} stack_element;
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
    OP_IF,
    OP_END,
    OP_OVER,
    OP_ELSE,
    OP_WHILE,
    OP_BEGIN,
    OP_ARRAY_BEGIN,
    OP_ARRAY_END
} opcode;
typedef struct
{
    opcode code;
    stack_element arg, arg2;
} operation;
typedef struct op_node op_node;
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