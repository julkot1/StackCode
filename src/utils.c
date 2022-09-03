#include "./include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}
int ends_with(const char *str, const char *suffix)
{
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    return (str_len >= suffix_len) &&
           (!memcmp(str + str_len - suffix_len, suffix, suffix_len));
}

void stack_push(StackNode **root, void *el)
{
    StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));

    new_node->data = el;
    new_node->next = (*root);
    (*root) = new_node;
}

void *stack_pop(StackNode **root)
{
    void *res;
    StackNode *top;
    top = *root;
    res = top->data;
    *root = top->next;
    free(top);
    return res;
}

void printc(const char *color, const char *text)
{
    printf("%s%s%s", color, text, ColReset);
}
void printbc(const char *color, const char *bg, const char *text)
{
    printf("%s%s%s%s", color, bg, text, ColReset);
}
