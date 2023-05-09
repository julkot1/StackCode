#include "include/ast_parser.h"
mpc_parser_t *parser_Identifier;
mpc_parser_t *parser_String;
mpc_parser_t *parser_Char;
mpc_parser_t *parser_Value;
mpc_parser_t *parser_Body;
mpc_parser_t *parser_Stmt;
mpc_parser_t *parser_Type;
mpc_parser_t *parser_Scope;
mpc_parser_t *parser_Function;
mpc_parser_t *parser_Struct;
mpc_parser_t *parser_Interface;
mpc_parser_t *parser_Logic;
mpc_parser_t *parser_Number;
mpc_parser_t *parser_Lit;
mpc_parser_t *parser_Build_in;
mpc_parser_t *parser_Math;
mpc_parser_t *parser_GLOBAL;
void parser_init()
{
    parser_Number = mpc_new(PARSER_NUMBER_TOKEN);
    parser_Lit = mpc_new(PARSER_LITERAL_TOKEN);
    parser_Identifier = mpc_new(PARSER_IDENTIFIER_TOKEN);
    parser_String = mpc_new(PARSER_STRING_TOKEN);
    parser_Char = mpc_new(PARSER_CHAR_TOKEN);
    parser_Value = mpc_new(PARSER_VALUE_TOKEN);
    parser_Body = mpc_new(PARSER_BODY_TOKEN);
    parser_Stmt = mpc_new(PARSER_STMT_TOKEN);
    parser_Type = mpc_new(PARSER_TYPE_TOKEN);
    parser_Scope = mpc_new(PARSER_SCOPE_TOKEN);
    parser_Function = mpc_new(PARSER_FUN_TOKEN);
    parser_Struct = mpc_new(PARSER_STRUCT_TOKEN);
    parser_Interface = mpc_new(PARSER_INTERFACE_TOKEN);
    parser_Logic = mpc_new(PARSER_LOGIC_TOKEN);
    parser_Math = mpc_new(PARSER_MATH_TOKEN);
    parser_Build_in = mpc_new(PARSER_BUILD_IN_TOKEN);
    parser_GLOBAL = mpc_new("global");
    mpca_lang(MPCA_LANG_DEFAULT,
              " number : /[0-9]+/ ;"
              " lit : /[a-zA-Z_][a-zA-Z0-9_]*/ ;"
              " identifier: <lit>(':'<lit>)*;"
              " string : /\"(\\\\.|[^\"])*\"/ ;"
              " char: /'.'/; "
              " type: \"Char\"|\"Number\"| \"Struct<\"<identifier>'>' | \"Str\"|\"Bool\"|\"Array\";"
              " value: <type> | <number> | <identifier> | <string> | <char> ;"
              " body: <buildin> | <logic> | <math> | <stmt> | <fun> | <struct> | <value> | <scope> ;"
              " stmt :  (\"if\" <scope> (<scope>\"elif\"<scope>)* (\"else\"<scope>)? )"
              "       | (\"for\" <identifier>? <scope>)"
              "       | (<scope> \"while\" <scope>);"
              " fun: (<interface> <identifier> \"fn\" <scope>) | (<interface> \"fn\" <scope>); "
              " struct: <identifier> \"struct\" <interface>; "
              " interface: '('<identifier>*')'; "
              " logic: \"==\"| \">=\"| \"<=\" | \"!=\" | \"not\" | \"or\" | \"and\" | \"in\" | '<' | '>' ;"
              " math: \"ls\"| \"rs\"| '&' | '|' | '+' | '-' | '/' | '%' | '*';"
              " buildin: \"sizeof\"|'@'| (\"rt\" <scope>)|\"typeof\"|\":=\" | \"dup\" | \"swap\" | \"pop\" | \"rot\";"
              " scope: '{' <body>* '}'; "
              " global: <lit> <scope>;",

              parser_Number,
              parser_Lit, parser_Identifier, parser_String, parser_Char, parser_Type, parser_Value, parser_Body, parser_Stmt, parser_Function, parser_Struct, parser_Interface, parser_Logic, parser_Math, parser_Build_in, parser_Scope, parser_GLOBAL, NULL);
}
mpc_val_t *parse_ast(FILE *fd, char *file_name)
{
    mpc_result_t result;
    int ok = mpc_parse_file(file_name, fd, parser_GLOBAL, &result);
    if (ok)
    {
        return result.output;
    }

    mpc_err_print(result.error);
    mpc_err_delete(result.error);
    return NULL;
}

int EndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}
token_type match_token_type(char *str)
{
    if (EndsWith(str, PARSER_NUMBER_TOKEN))
        return PARSER_NUMBER_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_LITERAL_TOKEN))
        return PARSER_LITERAL_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_IDENTIFIER_TOKEN))
        return PARSER_IDENTIFIER_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_STRING_TOKEN))
        return PARSER_STRING_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_CHAR_TOKEN))
        return PARSER_CHAR_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_VALUE_TOKEN))
        return PARSER_VALUE_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_BODY_TOKEN))
        return PARSER_BODY_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_STMT_TOKEN))
        return PARSER_STMT_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_TYPE_TOKEN))
        return PARSER_TYPE_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_SCOPE_TOKEN))
        return PARSER_SCOPE_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_FUN_TOKEN))
        return PARSER_FUN_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_STRUCT_TOKEN))
        return PARSER_STRUCT_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_INTERFACE_TOKEN))
        return PARSER_INTERFACE_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_LOGIC_TOKEN))
        return PARSER_LOGIC_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_MATH_TOKEN))
        return PARSER_MATH_TOKEN_TYPE;
    else if (EndsWith(str, PARSER_BUILD_IN_TOKEN))
        return PARSER_BUILD_IN_TOKEN_TYPE;
    return PARSER_CHAR_TOKEN_TYPE;
}