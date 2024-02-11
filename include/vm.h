//
// Created by julian on 2/2/24.
//

#ifndef CAMEL_VM_H
#define CAMEL_VM_H

#define CONST_POOL_ADDR_OFFSET (size_t)0xA0
#define VAR_POOL_ADDR_OFFSET (size_t)0xC0

#include "stdlib.h"
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


typedef enum
{
    SECTION_HEADER,
    SECTION_FUNCTION,
    SECTION_DATA,
    NOT_DEFINED

} file_section;
typedef union
{
    int number;
    size_t idx;
    char byte;
    char *str;
    void *ptr;
    unsigned long all;
} value;
typedef struct
{
    size_t length, capacity;
    struct stack_element *elements;
} array;
typedef struct
{
    opcode code;
    type payload_type;
    value payload;
} operation;
typedef struct op_node op_node;
struct op_node
{
    operation op;
    op_node *next;
};
typedef struct
{
    size_t const_pool_size;
    size_t functions_size;
    size_t labels_size;
    size_t stack_size;
    size_t var_pool_size;
    size_t const_stack_size;
} program_meta;

typedef struct
{
    type t;
    value val;
} element;
typedef struct
{
    type t;
    size_t size;
    size_t addr;
} pool_element;
typedef struct
{
    size_t num_args;
    size_t id;
    size_t code_size;
    char name[32];
    size_t code_addr;
} function;

typedef struct
{
    program_meta *meta;
    pool_element *const_pool;
    element *var_pool;
    function *functions;
    void *const_pool_stack;
    element *stack;
    size_t stack_ptr;
} program;

typedef char word[32];

void execute(program p);

typedef struct context context;

struct context
{
    function *fn;
    size_t state;
    context *parent;
};

void execute_function(context *current_context, program *p);
void execute_operation(operation op, program *p);
void op_fun_end();

#endif //CAMEL_VM_H
