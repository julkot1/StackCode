#pragma once
#ifndef MAIN
#define MAIN

#include <jit/jit.h>

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
    jit_function_t fn;
    jit_type_t signature;
    jit_value_t stack_ptr;

    int num_args;
    int is_returning;
    int id;
    int code_size;
    operation *code;
} function;
typedef struct
{
    program_meta meta;
    pool const_pool;
    pool var_pool;
    function *functions;
    jit_label_t *labels;
} program;
typedef char word[32];
extern program *__p;
int main();
#endif