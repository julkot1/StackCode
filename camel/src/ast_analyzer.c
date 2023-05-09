#include "include/ast_analyzer.h"
#include <stdio.h>
#include <string.h>

char *concat(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = malloc(len1 + len2 + 1);
    if (result == NULL)
    {
        return NULL;
    }
    memcpy(result, str1, len1);
    memcpy(result + len1, str2, len2 + 1);
    return result;
}
int string_ends_with(const char *str, const char *suffix)
{
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (str_len < suffix_len)
    {
        return 0;
    }

    const char *end_of_str = str + (str_len - suffix_len);
    return strcmp(end_of_str, suffix) == 0;
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

        if (string_ends_with(ast->tag, "number|regex"))
        {
            parse_value(ast, current);
        }
    } while ((ast = mpc_ast_traverse_next(&trav)) != NULL);
    return c_program;
}
void parse_value(mpc_ast_t *ast, struct scope_stack *current)
{
    current->scope->elements[current->element_ptr].type = C_VALUE;
    current->scope->elements[current->element_ptr].state = (compiler_state_t){.col = ast->state.col, .row = ast->state.row};
    compiler_Value_t *val = malloc(sizeof(compiler_Value_t));
    val->state = (compiler_state_t){.col = ast->state.col, .row = ast->state.row};
    val->t = NUMBER;
    val->value.number = atoi(ast->contents);
    current->scope->elements[current->element_ptr].ptr = val;
    current->element_ptr++;
}