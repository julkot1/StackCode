#include <string.h>
#include "./include/tokens.h"
#include "./include/structs.h"

int str_to_token(const char *str)
{
    if (strcmp(str, TOKEN_ADD) == 0)
        return OP_ADD;
    else if (strcmp(str, TOKEN_SUB) == 0)
        return OP_SUB;
    else if (strcmp(str, TOKEN_DIV) == 0)
        return OP_DIV;
    else if (strcmp(str, TOKEN_MOD) == 0)
        return OP_MOD;
    else if (strcmp(str, TOKEN_MUL) == 0)
        return OP_MUL;
    else if (strcmp(str, TOKEN_BEGIN) == 0)
        return OP_BEGIN;
    else if (strcmp(str, TOKEN_IF) == 0)
        return OP_IF;
    else if (strcmp(str, TOKEN_END) == 0)
        return OP_END;
    else if (strcmp(str, TOKEN_WHILE) == 0)
        return OP_WHILE;
    else if (strcmp(str, TOKEN_DUP) == 0)
        return OP_DUP;
    else if (strcmp(str, TOKEN_SWAP) == 0)
        return OP_SWAP;
    else if (strcmp(str, TOKEN_POP) == 0)
        return OP_POP;
    else if (strcmp(str, TOKEN_OVER) == 0)
        return OP_OVER;
    else if (strcmp(str, TOKEN_ELSE) == 0)
        return OP_ELSE;
    else if (strcmp(str, TOKEN_PRINT) == 0)
        return OP_PRINT;
    return -1;
}