#include "./include/structs.h"
#include "./include/parser.h"
#include "./include/tokens.h"
#include "./include/utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char str_buffer[MAX_CONST_STRING_SIZE];
unsigned short str_size = 0;
int insert_str_buffer = -1;

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
        if (insert_str_buffer == -1)
        {
            pr.tail->next = node;
            pr.tail = node;
            size++;
        }
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

operation parse_not_operation(const char *token)
{

    operation op;
    /*
    if (insert_str_buffer == -1)
    {
        if (token[0] == TOKEN_STRING[0])
        {
            str_buffer[0] = '\0';
            strcat(str_buffer, (token + 1));
            str_size = strlen(token) - 1;
            insert_str_buffer = 1;
        }
        return op;
    }
    else if (insert_str_buffer == 0)
    {
        if (ends_with(token, TOKEN_STRING) == 1 && ends_with(token, TOKEN_ESCAPE_STRING) != 1)
        {
            insert_str_buffer = -1;
            strcat(str_buffer, token);
            str_size += strlen(token) - 1;
            str_buffer[str_size] = '\0';
            printf("%s\n", str_buffer);
        }
        else
        {
            strcat(str_buffer, token);
            str_size += strlen(token);
        }
    }
    else
    */
    {
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
    }
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