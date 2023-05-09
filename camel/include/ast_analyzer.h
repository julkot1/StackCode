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
void parse_value(mpc_ast_t *ast, struct scope_stack *current);
