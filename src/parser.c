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
        if (op->code == OP_IF || op->code == OP_BEGIN)
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
program parse(FILE *fp)
{
    program pr;
    pr.size = 0;
    int size = 0, token_index = 0, str_parse = false;
    char c;
    char token[256];
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
            node->val = parse_token(token);
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
            token[token_index] = c;
            token_index++;
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