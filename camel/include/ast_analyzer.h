#pragma once
#include "mpc.h"
#include "include/compiler.h"
struct scope_stack
{
    compiler_Scope_t *scope;
    int element_ptr;
    struct scope_stack *prev;
};

compiler_program_t ast_analyze(mpc_val_t *result);
void parse_value_number(mpc_ast_t *ast, struct scope_stack *current);
void parse_value_string(mpc_ast_t *ast, struct scope_stack *current);
void parse_value_literal(mpc_ast_t *ast, struct scope_stack *current);
void parse_operation(mpc_ast_t *ast, struct scope_stack *current);

void parse_token(token_type t, mpc_ast_t *ast, struct scope_stack *current);
int is_buildin_operation(token_type t);