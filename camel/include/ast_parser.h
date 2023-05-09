#pragma once
#include "mpc.h"
#include <stdio.h>
#include <stdlib.h>

#define PARSER_NUMBER_TOKEN "number"
#define PARSER_LITERAL_TOKEN "lit"
#define PARSER_IDENTIFIER_TOKEN "identifier"
#define PARSER_STRING_TOKEN "string"
#define PARSER_CHAR_TOKEN "char"
#define PARSER_VALUE_TOKEN "value"
#define PARSER_BODY_TOKEN "body"
#define PARSER_STMT_TOKEN "stmt"
#define PARSER_TYPE_TOKEN "type"
#define PARSER_SCOPE_TOKEN "scope"
#define PARSER_FUN_TOKEN "fun"
#define PARSER_STRUCT_TOKEN "struct"
#define PARSER_INTERFACE_TOKEN "interface"
#define PARSER_LOGIC_TOKEN "logic"
#define PARSER_MATH_TOKEN "math"
#define PARSER_BUILD_IN_TOKEN "buildin"

extern mpc_parser_t *parser_Identifier;
extern mpc_parser_t *parser_String;
extern mpc_parser_t *parser_Char;
extern mpc_parser_t *parser_Value;
extern mpc_parser_t *parser_Body;
extern mpc_parser_t *parser_Stmt;
extern mpc_parser_t *parser_Type;
extern mpc_parser_t *parser_Scope;
extern mpc_parser_t *parser_Function;
extern mpc_parser_t *parser_Struct;
extern mpc_parser_t *parser_Interface;
extern mpc_parser_t *parser_Logic;
extern mpc_parser_t *parser_Number;
extern mpc_parser_t *parser_Lit;
extern mpc_parser_t *parser_Build_in;
extern mpc_parser_t *parser_Math;

typedef enum
{
    PARSER_NUMBER_TOKEN_TYPE,
    PARSER_LITERAL_TOKEN_TYPE,
    PARSER_IDENTIFIER_TOKEN_TYPE,
    PARSER_STRING_TOKEN_TYPE,
    PARSER_CHAR_TOKEN_TYPE,
    PARSER_VALUE_TOKEN_TYPE,
    PARSER_BODY_TOKEN_TYPE,
    PARSER_STMT_TOKEN_TYPE,
    PARSER_TYPE_TOKEN_TYPE,
    PARSER_SCOPE_TOKEN_TYPE,
    PARSER_FUN_TOKEN_TYPE,
    PARSER_STRUCT_TOKEN_TYPE,
    PARSER_INTERFACE_TOKEN_TYPE,
    PARSER_LOGIC_TOKEN_TYPE,
    PARSER_MATH_TOKEN_TYPE,
    PARSER_BUILD_IN_TOKEN_TYPE

} token_type;

void parser_init();
mpc_val_t *parse_ast(FILE *fd, char *file_name);
token_type match_token_type(char *str);
