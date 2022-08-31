#include "./include/structs.h"
#include "./include/parser.h"

#include <string.h>
#include <stdlib.h>

program parse(char *buffer)
{
    program pr;
    int size = 0;
    char *pch;
    pch = strtok(buffer, " ");
    op_node *node = malloc(sizeof(op_node));
    node->val = parse_token(pch);
    pr.begin = node;
    pr.tail = node;
    while (pch != NULL)
    {
        pch = strtok(NULL, " ");
        node = malloc(sizeof(op_node));
        node->val = parse_token(pch);
        pr.tail->next = node;
        pr.tail = node;
        size++;
    }
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
    return pr;
}
operation parse_token(const char *token)
{
    operation op;
    op.code = OP_ADD;
    return op;
}