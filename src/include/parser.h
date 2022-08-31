#pragma once
#include "./structs.h"
typedef struct op_node op_node;
struct op_node
{
    operation val;
    op_node *next;
};

typedef struct
{
    op_node *begin;
    op_node *tail;
    int size;
    op_node **op_ptr;
} program;

operation parse_token(const char *token);
program parse(char *buffer);