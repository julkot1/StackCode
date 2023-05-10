#include "include/ast_analyzer.h"
#include <stdio.h>
#include <string.h>

void parse_token(token_type t, mpc_ast_t *ast, struct scope_stack *current)
{
    if (t == PARSER_NUMBER_TOKEN_TYPE)
    {
        parse_value_number(ast, current);
    }
    else if (t == PARSER_STRING_TOKEN_TYPE)
    {
        parse_value_string(ast, current);
    }
    else if (is_buildin_operation(t))
    {
        parse_operation(ast, current);
    }
}
compiler_program_t ast_analyze(mpc_val_t *result)
{
    mpc_ast_trav_t *trav = mpc_ast_traverse_start(result, mpc_ast_trav_order_pre);
    mpc_ast_t *ast;
    compiler_program_t c_program;
    struct scope_stack *current = malloc(sizeof(struct scope_stack));
    current->scope = &c_program.scope;
    current->element_ptr = 0;
    mpc_ast_print(result);
    ast = mpc_ast_traverse_next(&trav);
    ast = mpc_ast_traverse_next(&trav);
    char *namespace = ast->contents;
    printf("namespace: %s\n", namespace);
    ast = mpc_ast_traverse_next(&trav);
    current->scope->size = ast->children_num;
    current->scope->elements = malloc(current->scope->size * sizeof(compiler_Element_t));
    do
    {
        token_type t = match_token_type(ast->tag);
        parse_token(t, ast, current);
    } while ((ast = mpc_ast_traverse_next(&trav)) != NULL);
    return c_program;
}
void parse_value_number(mpc_ast_t *ast, struct scope_stack *current)
{
    current->scope->elements[current->element_ptr].type = CAMEL_VALUE;
    current->scope->elements[current->element_ptr].state = (compiler_state_t){.col = ast->state.col, .row = ast->state.row};
    compiler_Value_t *val = malloc(sizeof(compiler_Value_t));
    val->state = (compiler_state_t){.col = ast->state.col, .row = ast->state.row};
    val->t = NUMBER;
    val->value.number = atoi(ast->contents);
    current->scope->elements[current->element_ptr].ptr = val;
    current->element_ptr++;
}
void parse_value_string(mpc_ast_t *ast, struct scope_stack *current)
{
    current->scope->elements[current->element_ptr].type = CAMEL_VALUE;
    current->scope->elements[current->element_ptr].state = (compiler_state_t){.col = ast->state.col, .row = ast->state.row};
    compiler_Value_t *val = malloc(sizeof(compiler_Value_t));
    val->state = (compiler_state_t){.col = ast->state.col, .row = ast->state.row};
    val->t = STRING;
    size_t size = strlen(ast->contents);
    val->value.str = malloc(size - 2);
    strncpy(val->value.str, ast->contents + 1, size - 2);
    val->value.str[size - 2] = '\0';
    current->scope->elements[current->element_ptr]
        .ptr = val;
    current->element_ptr++;
}
void parse_value_literal(mpc_ast_t *ast, struct scope_stack *current)
{
}
void parse_operation(mpc_ast_t *ast, struct scope_stack *current)
{
    compiler_operation_type *op_type = malloc(sizeof(compiler_operation_type));
    *op_type = match_operation(ast->contents);
    compiler_Element_t *el = &current->scope->elements[current->element_ptr];
    el->type = CAMEL_BUILDIN;
    el->state = (compiler_state_t){.col = ast->state.col, .row = ast->state.row};
    el->ptr = op_type;
    current->element_ptr++;
}