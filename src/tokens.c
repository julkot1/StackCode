#include <string.h>
#include "./include/tokens.h"
#include "./include/structs.h"

int str_to_token(const char *str)
{
    if (str == NULL)
        return -2;
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
    else if (strcmp(str, TOKEN_ITER) == 0)
        return OP_ITER;
    else if (strcmp(str, TOKEN_LT) == 0)
        return OP_LT;
    else if (strcmp(str, TOKEN_GT) == 0)
        return OP_GT;
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
    else if (strcmp(str, TOKEN_ARRAY_OPEN) == 0)
        return OP_ARRAY_BEGIN;
    else if (strcmp(str, TOKEN_ARRAY_CLOSE) == 0)
        return OP_ARRAY_END;
    else if (strcmp(str, TOKEN_EQ) == 0)
        return OP_EQ;
    else if (strcmp(str, TOKEN_LET) == 0)
        return OP_LET;
    else if (strcmp(str, TOKEN_PUT) == 0)
        return OP_PUT;
    return -1;
}

char *token_to_string(opcode op)
{
    if (op == OP_ADD)
        return TOKEN_ADD;
    else if (OP_SUB == op)
        return TOKEN_SUB;
    else if (OP_DIV == op)
        return TOKEN_DIV;
    else if (OP_MOD == op)
        return TOKEN_MOD;
    else if (OP_MUL == op)
        return TOKEN_MUL;
    else if (OP_BEGIN == op)
        return TOKEN_BEGIN;
    else if (OP_IF == op)
        return TOKEN_IF;
    else if (OP_ITER == op)
        return TOKEN_ITER;
    else if (OP_LT == op)
        return TOKEN_LT;
    else if (OP_GT == op)
        return TOKEN_GT;
    else if (OP_END == op)
        return TOKEN_END;
    else if (OP_WHILE == op)
        return TOKEN_WHILE;
    else if (OP_DUP == op)
        return TOKEN_DUP;
    else if (OP_SWAP == op)
        return TOKEN_SWAP;
    else if (OP_POP == op)
        return TOKEN_POP;
    else if (OP_OVER == op)
        return TOKEN_OVER;
    else if (OP_ELSE == op)
        return TOKEN_ELSE;
    else if (OP_PRINT == op)
        return TOKEN_PRINT;
    else if (OP_ARRAY_BEGIN == op)
        return TOKEN_ARRAY_CLOSE;
    else if (OP_ARRAY_END == op)
        return TOKEN_ARRAY_CLOSE;
    else if (OP_EQ == op)
        return TOKEN_EQ;
    else if (OP_LET == op)
        return TOKEN_LET;
    else if (OP_PUT == op)
        return TOKEN_PUT;
    return "null";
}