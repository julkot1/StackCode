#pragma once
#define ColBlack "\033[30m"
#define ColRed "\033[31m"
#define ColGreen "\033[32m"
#define ColYellow "\033[33m"
#define ColBlue "\033[34m"
#define ColMagenta "\033[35m"
#define ColCyan "\033[36m"
#define ColWhite "\033[37m"
#define ColReset "\033[0m"
#define ColBgBlack "\033[40m"
#define ColBgRed "\033[41m"
#define ColBgGreen "\033[42m"
#define ColBgYellow "\033[43m"
#define ColBgBlue "\033[44m"
#define ColBgMagenta "\033[45m"
#define ColBgCyan "\033[46m"
#define ColBgWhite "\033[47m"

int prefix(const char *pre, const char *str);
int ends_with(const char *str, const char *suffix);
typedef struct StackNode StackNode;
struct StackNode
{
    void *data;
    StackNode *next;
};
void stack_push(StackNode **root, void *el);
void *stack_pop(StackNode **root);
void printc(const char *color, const char *text);
void printbc(const char *color, const char *bg, const char *text);