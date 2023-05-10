#include "include/compiler.h"

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
token_type match_token_type(char *str)
{
    if (string_ends_with(str, concat(PARSER_NUMBER_TOKEN, "|regex")))
        return PARSER_NUMBER_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_LITERAL_TOKEN, "|regex")))
        return PARSER_LITERAL_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_IDENTIFIER_TOKEN, "|regex")))
        return PARSER_IDENTIFIER_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_STRING_TOKEN, "|regex")))
        return PARSER_STRING_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_CHAR_TOKEN, "|regex")))
        return PARSER_CHAR_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_VALUE_TOKEN, "|regex")))
        return PARSER_VALUE_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_BODY_TOKEN, "|regex")))
        return PARSER_BODY_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_STMT_TOKEN, "|regex")))
        return PARSER_STMT_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_TYPE_TOKEN, "|regex")))
        return PARSER_TYPE_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_SCOPE_TOKEN, "|>")))
        return PARSER_SCOPE_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_FUN_TOKEN, "|regex")))
        return PARSER_FUN_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_STRUCT_TOKEN, "|regex")))
        return PARSER_STRUCT_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_INTERFACE_TOKEN, "|regex")))
        return PARSER_INTERFACE_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_LOGIC_TOKEN, "|string")))
        return PARSER_LOGIC_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_MATH_TOKEN, "|string")))
        return PARSER_MATH_TOKEN_TYPE;
    else if (string_ends_with(str, concat(PARSER_BUILD_IN_TOKEN, "|string")))
        return PARSER_BUILD_IN_TOKEN_TYPE;
    return PARSER_CHAR_TOKEN_TYPE;
}
int is_buildin_operation(token_type t)
{
    return t == PARSER_MATH_TOKEN_TYPE ||
           t == PARSER_LOGIC_TOKEN_TYPE ||
           t == PARSER_BUILD_IN_TOKEN_TYPE;
}
compiler_operation_type match_operation(char *str)
{
    if (strcmp(str, CAMEL_TOKEN_ADD) == 0)
        return CAMEL_OP_ADD;
    else if (strcmp(str, CAMEL_TOKEN_SUB) == 0)
        return CAMEL_OP_SUB;
    else if (strcmp(str, CAMEL_TOKEN_DIV) == 0)
        return CAMEL_OP_DIV;
    else if (strcmp(str, CAMEL_TOKEN_MUL) == 0)
        return CAMEL_OP_MUL;
    else if (strcmp(str, CAMEL_TOKEN_MOD) == 0)
        return CAMEL_OP_MOD;
    else if (strcmp(str, CAMEL_TOKEN_PRINT) == 0)
        return CAMEL_OP_PRINT;
    else if (strcmp(str, CAMEL_TOKEN_POP) == 0)
        return CAMEL_OP_POP;
    else if (strcmp(str, CAMEL_TOKEN_DUP) == 0)
        return CAMEL_OP_DUP;
    else if (strcmp(str, CAMEL_TOKEN_SWAP) == 0)
        return CAMEL_OP_SWAP;
    else if (strcmp(str, CAMEL_TOKEN_EQUAL) == 0)
        return CAMEL_OP_EQUAL;
    else if (strcmp(str, CAMEL_TOKEN_NOT) == 0)
        return CAMEL_OP_NOT;
    else if (strcmp(str, CAMEL_TOKEN_NOT_EQUAL) == 0)
        return CAMEL_OP_NOT_EQUAL;
    else if (strcmp(str, CAMEL_TOKEN_OR) == 0)
        return CAMEL_OP_OR;
    else if (strcmp(str, CAMEL_TOKEN_AND) == 0)
        return CAMEL_OP_AND;
    else if (strcmp(str, CAMEL_TOKEN_GREATER) == 0)
        return CAMEL_OP_GREATER;
    else if (strcmp(str, CAMEL_TOKEN_LOWER) == 0)
        return CAMEL_OP_LOWER;
    else if (strcmp(str, CAMEL_TOKEN_GREATER_OR_EQUAL) == 0)
        return CAMEL_OP_GREATER_OR_EQUAL;
    else if (strcmp(str, CAMEL_TOKEN_LOWER_OR_EQUAL) == 0)
        return CAMEL_OP_LOWER_OR_EQUAL;
    else if (strcmp(str, CAMEL_TOKEN_BITWISE_AND) == 0)
        return CAMEL_OP_BITWISE_AND;
    else if (strcmp(str, CAMEL_TOKEN_BITWISE_OR) == 0)
        return CAMEL_OP_BITWISE_OR;
    else if (strcmp(str, CAMEL_TOKEN_BITWISE_XOR) == 0)
        return CAMEL_OP_BITWISE_XOR;
    else if (strcmp(str, CAMEL_TOKEN_BITWISE_NOT) == 0)
        return CAMEL_OP_BITWISE_NOT;
    else if (strcmp(str, CAMEL_TOKEN_LEFT_SHIFT) == 0)
        return CAMEL_OP_LEFT_SHIFT;
    else if (strcmp(str, CAMEL_TOKEN_RIGHT_SHIFT) == 0)
        return CAMEL_OP_RIGHT_SHIFT;
    else if (strcmp(str, CAMEL_TOKEN_TYPEOF) == 0)
        return CAMEL_OP_TYPEOF;
    else if (strcmp(str, CAMEL_TOKEN_SIZEOF) == 0)
        return CAMEL_OP_SIZEOF;
    else if (strcmp(str, CAMEL_TOKEN_ASSIGN) == 0)
        return CAMEL_OP_ASSIGN;
    else if (strcmp(str, CAMEL_TOKEN_INPUT) == 0)
        return CAMEL_OP_INPUT;
    return -1;
}