#include "./include/structs.h"
#include "./include/parser.h"
#include "./include/tokens.h"
#include "./include/utils.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void analyze_code(program *pr)
{
    operation *op;
    StackNode *root = malloc(sizeof(StackNode));
    for (int i = 0; i < pr->size; i++)
    {
        op = &(pr->op_ptr[i]->val);
        if (op->code == OP_IF || op->code == OP_BEGIN || op->code == OP_ITER)
            stack_push(&root, op);
        else if (op->code == OP_END)
        {
            operation *op_match = stack_pop(&root);
            if (op_match->code == OP_IF)
            {
                op_match->arg.val.number = op->id;
                op_match->arg.type = NUMBER;

                op->arg.type = NUMBER;
                op->arg.val.number = -1;
            }
            else if (op_match->code == OP_ITER)
            {
                op_match->arg.val.number = op->id;
                op_match->arg.type = NUMBER;

                op_match->arg2.type = OBJ;
                op_match->it = (iterator){
                    .begin = 0,
                    .end = 0,
                    .step = 0,
                    .current = 0,
                    .started = false};

                op->arg.val.number = op_match->id - 1;
                op->arg.type = NUMBER;
            }
            else if (op_match->code == OP_WHILE)
            {
                op->arg.val.number = op_match->arg.val.number;
                op->arg.type = NUMBER;
                (&pr->op_ptr[op_match->id]->val)->arg.val.number = op->id + 1;
            }
        }
        else if (op->code == OP_WHILE)
        {
            operation *op_begin = stack_pop(&root);
            op->arg.type = NUMBER;
            op->arg.val.number = op_begin->id;
            stack_push(&root, op);
        }
    }
}
void node_push(op_node *node, program *pr)
{
    op_node **parent;
    if (pr->size == 0)
        parent = &pr->begin;
    else
        parent = &pr->tail;
    node->val.id = pr->size + 1;
    (*parent)->next = node;
    *parent = node;
    pr->size++;
}
char getSpecialChar(char c)
{
    if (c == 'a')
        return '\a';
    if (c == 'b')
        return '\b';
    if (c == 'e')
        return '\e';
    if (c == 'f')
        return '\f';
    if (c == 'n')
        return '\n';
    if (c == 'r')
        return '\r';
    if (c == 'v')
        return '\v';
    return ' ';
}
program parse(FILE *fp)
{
    program pr;
    pr.size = 0;
    int size = 0, token_index = 0, str_parse = false, escape = false;
    char c;
    char token[256];
    bool special_char = false;
    op_node *node = malloc(sizeof(op_node));
    operation o = {0, OP_NONE};
    node->val = o;
    pr.begin = node;
    pr.tail = node;

    while ((c = getc(fp)) != EOF)
    {
        if (c == TOKEN_STRING[0])
        {
            if (str_parse == false)
            {
                str_parse = true;
                continue;
            }
            node = malloc(sizeof(op_node));
            token[token_index] = '\0';
            stack_element el;
            el.type = STRING;
            el.val.str = malloc(strlen(token) * sizeof(char));
            strcpy(el.val.str, token);
            node->val = (operation){.code = OP_PUSH, .arg = el};
            node->val.id = size + 1;
            pr.tail->next = node;
            pr.tail = node;
            size++;
            str_parse = false;
            token_index = 0;
            token[token_index] = '\0';
            continue;
        }
        if (str_parse == true)
        {
            if (c == '\\')
            {
                if (special_char)
                {
                    token[token_index] = c;
                    token_index++;
                    special_char = false;
                    continue;
                }
                else
                    special_char = true;
            }
            else if (special_char)
            {
                token[token_index] = getSpecialChar(c);
                token_index++;
                special_char = false;
                continue;
            }
            else
            {
                token[token_index] = c;
                token_index++;
            }
            continue;
        }
        if (isspace(c) && token_index != 0)
        {
            token[token_index] = '\0';
            node = malloc(sizeof(op_node));
            node->val = parse_token(token);
            node->val.id = size + 1;
            pr.tail->next = node;
            pr.tail = node;
            size++;
            token_index = 0;
            token[token_index] = '\0';
            continue;
        }
        if (!isspace(c))
        {
            token[token_index] = c;
            token_index++;
        }
    }
    if (token_index > 0)
    {
        token[token_index] = '\0';

        node = malloc(sizeof(op_node));
        node->val = parse_token(token);
        node->val.id = size + 1;
        pr.tail->next = node;
        pr.tail = node;
        size++;
    }
    size++;
    pr.size = size;

    pr.op_ptr = malloc(sizeof(op_node) * size);
    op_node *tmp = pr.begin;
    int index = 0;
    while (tmp != NULL)
    {
        pr.op_ptr[index] = tmp;
        tmp = tmp->next;
        index++;
    }

    analyze_code(&pr);

    return pr;
}

operation parse_not_operation(const char *token)
{

    operation op;

    stack_element el;
    op.code = OP_PUSH;
    int number;
    if (strcmp(token, TOKEN_TRUE) == 0)
    {
        el.type = BOOL;
        el.val.number = 1;
    }
    else if (strcmp(token, TOKEN_FALSE) == 0)
    {
        el.type = BOOL;
        el.val.number = 0;
    }
    else if ((number = atoi(token)) == 0 && token[0] != '0')
    {
        el.type = VAR;
        el.val.str = malloc(sizeof(char) * MAX_VAR_SIZE);
        strcpy(el.val.str, token);
    }
    else
    {
        el.type = NUMBER;
        el.val.number = atoi(token);
    }
    op.arg = el;

    return op;
}
operation parse_token(const char *token)
{
    operation op;
    int code = str_to_token(token);
    if (code == -1)
    {
        return parse_not_operation(token);
    }
    op.code = code;
    return op;
}