#pragma once
#include <stdio.h>
#include <stdlib.h>

#define CONST_POOL_PTR -1

#ifndef MAIN
#define MAIN
#define TOKEN_SECTION_DATA "::DATA\n"
#define TOKEN_SECTION_CONST "::CONST_POOL\n"
#define TOKEN_SECTION_FUNCTIONS "::FUNCTION"

#define TOKEN_DATA_STACK_SIZE ".stack_size"
#define TOKEN_DATA_LABELS ".labels"
#define TOKEN_DATA_FUNCTIONS ".functions"
#define TOKEN_DATA_CONST_SIZE ".const_pool_size"
#define TOKEN_DATA_VAR_SIZE ".var_pool_size"

#define TOKEN_PUSH "push"
#define TOKEN_ADD "add"
#define TOKEN_SUB "sub"
#define TOKEN_DIV "div"
#define TOKEN_MUL "mul"
#define TOKEN_MOD "mod"
#define TOKEN_DUMP "dump"
#define TOKEN_POP "pop"
#define TOKEN_DUP "dup"
#define TOKEN_SWAP "swap"
#define TOKEN_JMP "jmp"
#define TOKEN_JMP_IF "jme"
#define TOKEN_JMP_IF_NOT "jmn"
#define TOKEN_LABEL "lb"
#define TOKEN_EQUAL "eq"
#define TOKEN_NOT "not"
#define TOKEN_NOT_EQUAL "neq"
#define TOKEN_OR "or"
#define TOKEN_AND "and"
#define TOKEN_GREATER "gr"
#define TOKEN_LOWER "lt"
#define TOKEN_GREATER_OR_EQUAL "ge"
#define TOKEN_LOWER_OR_EQUAL "le"
#define TOKEN_BITWISE_AND "band"
#define TOKEN_BITWISE_OR "bor"
#define TOKEN_BITWISE_XOR "xor"
#define TOKEN_BITWISE_NOT "bnot"
#define TOKEN_LEFT_SHIFT "shl"
#define TOKEN_RIGHT_SHIFT "shr"
#define TOKEN_TYPEOF "typeof"
#define TOKEN_SIZEOF "sizeof"
#define TOKEN_EOP "eop"
#define TOKEN_VLOAD "vld"
#define TOKEN_VSTORE "vst"
#define TOKEN_INPUT "in"
#define TOKEN_CALL "call"
#define TOKEN_ARR_STORE "@st"
#define TOKEN_ARR_APPEND "@app"
#define TOKEN_ARR_NEW_STACK "s@arr"
#define TOKEN_ARR_LOAD "@ld"

#define TOKEN_CONST_POOL_ELEMENT '$'
#define TOKEN_VAR_POOL_ELEMENT '*'

#define TOKEN_TYPE_NUMBER "Number"
#define TOKEN_TYPE_STRING "String"
#define TOKEN_TYPE_TYPE "Type"
#define TOKEN_TYPE_PTR "Ptr"
#define TOKEN_TYPE_BOOL "Bool"
#define TOKEN_TYPE_CHAR "Char"
#define TOKEN_TYPE_ARRAY "Arr"

typedef enum
{
    SECTION_DATA,
    SECTION_FUNCTION,
    SECTION_CONST

} file_section;
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
    BIN_ARR_NEW_STACK,
    BIN_ARR_STORE,
    BIN_ARR_APPEND,
    BIN_ARR_LOAD,
    BIN_EOP
} opcode;
typedef enum
{
    NUMBER,
    STRING,
    BOOL,
    CHAR,
    PTR,
    ARRAY,
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
    size_t length, capacity;
    struct stack_element *elements;
} array;
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
    size_t *labels;
    function *functions;

    struct stack_element *stack;
    size_t ptr;
} program;

typedef char word[32];

extern program *__p;
int main();
#endif