#pragma once

#include <stdlib.h>
#include "../../include/main.h"
typedef enum
{
    C_STMT_IF,
    C_STMT_IF_ELSE,
    C_STMT_ELSE,
    C_FOR
} compiler_stmt_type;
typedef enum
{
    C_SCOPE,
    C_STMT,
    C_OPERATION,
    C_VALUE,
    C_INTERFACE,
    C_IDENTIFIER,
    C_FUNCTION
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