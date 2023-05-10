#pragma once

#include <stdlib.h>
#include <string.h>
#include "../../include/main.h"

#define PARSER_NUMBER_TOKEN "number"
#define PARSER_LITERAL_TOKEN "lit"
#define PARSER_IDENTIFIER_TOKEN "identifier"
#define PARSER_STRING_TOKEN "string"
#define PARSER_CHAR_TOKEN "char"
#define PARSER_VALUE_TOKEN "value"
#define PARSER_BODY_TOKEN "body"
#define PARSER_STMT_TOKEN "stmt"
#define PARSER_TYPE_TOKEN "type"
#define PARSER_SCOPE_TOKEN "scope"
#define PARSER_FUN_TOKEN "fun"
#define PARSER_STRUCT_TOKEN "struct"
#define PARSER_INTERFACE_TOKEN "interface"
#define PARSER_LOGIC_TOKEN "logic"
#define PARSER_MATH_TOKEN "math"
#define PARSER_BUILD_IN_TOKEN "buildin"

#define CAMEL_TOKEN_ADD "+"
#define CAMEL_TOKEN_SUB "-"
#define CAMEL_TOKEN_DIV "/"
#define CAMEL_TOKEN_MUL "*"
#define CAMEL_TOKEN_MOD "%"
#define CAMEL_TOKEN_PRINT "print"
#define CAMEL_TOKEN_POP "pop"
#define CAMEL_TOKEN_DUP "dup"
#define CAMEL_TOKEN_SWAP "swap"
#define CAMEL_TOKEN_EQUAL "=="
#define CAMEL_TOKEN_NOT "not"
#define CAMEL_TOKEN_NOT_EQUAL "!="
#define CAMEL_TOKEN_OR "or"
#define CAMEL_TOKEN_AND "and"
#define CAMEL_TOKEN_GREATER ">"
#define CAMEL_TOKEN_LOWER "<"
#define CAMEL_TOKEN_GREATER_OR_EQUAL ">="
#define CAMEL_TOKEN_LOWER_OR_EQUAL "<="
#define CAMEL_TOKEN_BITWISE_AND "&"
#define CAMEL_TOKEN_BITWISE_OR "|"
#define CAMEL_TOKEN_BITWISE_XOR "xor"
#define CAMEL_TOKEN_BITWISE_NOT "!"
#define CAMEL_TOKEN_LEFT_SHIFT "rs"
#define CAMEL_TOKEN_RIGHT_SHIFT "ls"
#define CAMEL_TOKEN_TYPEOF "typeof"
#define CAMEL_TOKEN_SIZEOF "sizeof"
#define CAMEL_TOKEN_ASSIGN ":="
#define CAMEL_TOKEN_INPUT "in"

typedef enum
{
    PARSER_NUMBER_TOKEN_TYPE,
    PARSER_LITERAL_TOKEN_TYPE,
    PARSER_IDENTIFIER_TOKEN_TYPE,
    PARSER_STRING_TOKEN_TYPE,
    PARSER_CHAR_TOKEN_TYPE,
    PARSER_VALUE_TOKEN_TYPE,
    PARSER_BODY_TOKEN_TYPE,
    PARSER_STMT_TOKEN_TYPE,
    PARSER_TYPE_TOKEN_TYPE,
    PARSER_SCOPE_TOKEN_TYPE,
    PARSER_FUN_TOKEN_TYPE,
    PARSER_STRUCT_TOKEN_TYPE,
    PARSER_INTERFACE_TOKEN_TYPE,
    PARSER_LOGIC_TOKEN_TYPE,
    PARSER_MATH_TOKEN_TYPE,
    PARSER_BUILD_IN_TOKEN_TYPE

} token_type;
typedef enum
{
    CAMEL_OP_ADD,
    CAMEL_OP_SUB,
    CAMEL_OP_DIV,
    CAMEL_OP_MUL,
    CAMEL_OP_MOD,
    CAMEL_OP_PRINT,
    CAMEL_OP_POP,
    CAMEL_OP_DUP,
    CAMEL_OP_SWAP,
    CAMEL_OP_EQUAL,
    CAMEL_OP_NOT,
    CAMEL_OP_NOT_EQUAL,
    CAMEL_OP_OR,
    CAMEL_OP_AND,
    CAMEL_OP_GREATER,
    CAMEL_OP_LOWER,
    CAMEL_OP_GREATER_OR_EQUAL,
    CAMEL_OP_LOWER_OR_EQUAL,
    CAMEL_OP_BITWISE_AND,
    CAMEL_OP_BITWISE_OR,
    CAMEL_OP_BITWISE_XOR,
    CAMEL_OP_BITWISE_NOT,
    CAMEL_OP_LEFT_SHIFT,
    CAMEL_OP_RIGHT_SHIFT,
    CAMEL_OP_TYPEOF,
    CAMEL_OP_SIZEOF,
    CAMEL_OP_ASSIGN,
    CAMEL_OP_INPUT
} compiler_operation_type;
typedef enum
{
    CAMEL_STMT_IF,
    CAMEL_STMT_IF_ELSE,
    CAMEL_STMT_ELSE,
    CAMEL_FOR
} compiler_stmt_type;
typedef enum
{
    CAMEL_SCOPE,
    CAMEL_STMT,
    CAMEL_BUILDIN,
    CAMEL_VALUE,
    CAMEL_INTERFACE,
    CAMEL_IDENTIFIER,
    CAMEL_FUNCTION
} compiler_element_type;
typedef struct compiler_state_t compiler_state_t;
typedef struct compiler_Stmt_if_t compiler_Stmt_if_t;
typedef struct compiler_Stmt_for_t compiler_Stmt_for_t;
typedef struct compiler_Element_t compiler_Element_t;
typedef struct compiler_Stmt_if_t compiler_Stmt_if_t;
typedef struct compiler_Stmt_for_t compiler_Stmt_for_t;
typedef struct compiler_Value_t compiler_Value_t;
typedef struct compiler_Interface_t compiler_Interface_t;
typedef struct compiler_Function_t compiler_Function_t;
typedef struct compiler_program_t compiler_program_t;
typedef struct compiler_Scope_t compiler_Scope_t;
typedef struct compiler_Identifier_t compiler_Identifier_t;
struct compiler_state_t
{
    long row, col;
    char *file;
};
struct compiler_Identifier_t
{
    compiler_state_t state;
    char **names;
    size_t size;
};
struct compiler_Scope_t
{
    compiler_state_t state;
    size_t size;
    compiler_Element_t *elements;
};

struct compiler_Element_t
{
    compiler_state_t state;
    compiler_element_type type;
    void *ptr;
};

struct compiler_Stmt_t
{
    compiler_state_t state;
    compiler_stmt_type type;
    void *ptr;
};

struct compiler_Stmt_if_t
{
    compiler_state_t state;
    compiler_stmt_type type;
    compiler_Scope_t scope;
    compiler_Stmt_if_t *next;
};

struct compiler_Stmt_for_t
{
    compiler_state_t state;
    compiler_Identifier_t var;
    compiler_Scope_t scope;
};

struct compiler_Value_t
{
    compiler_state_t state;
    type t;
    payload_value value;
};

struct compiler_Interface_t
{
    compiler_state_t state;
    compiler_Identifier_t *args;
    size_t size;
};

struct compiler_Function_t
{
    compiler_state_t state;
    compiler_Interface_t interface;
    compiler_Identifier_t name;
    compiler_Scope_t scope;
};

struct compiler_program_t
{
    compiler_state_t state;
    size_t function_size, const_pool_size;
    long labels_size;
    compiler_Function_t *functions;
    compiler_Value_t *const_pool;
    compiler_Scope_t scope;
};

token_type match_token_type(char *str);
compiler_operation_type match_operation(char *str);
char *concat(const char *str1, const char *str2);
int string_ends_with(const char *str, const char *suffix);