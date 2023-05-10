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
              "       | (<scope> \"while\" <scope>)|(\"rt\" <scope>);"
              " fun: (<interface> <identifier> \"fn\" <scope>) | (<interface> \"fn\" <scope>); "
              " struct: <identifier> \"struct\" <interface>; "
              " interface: '('<identifier>*')'; "
              " logic: \"==\"| \">=\"| \"<=\" | \"!=\" | \"not\" | \"or\" | \"and\" | \"<\" | \">\" ;"
              " math: \"ls\"| \"rs\"| \"&\" | \"|\" | \"+\" | \"-\" | \"/\" | \"%\" | \"*\" | \"xor\" | \"!\";"
              " buildin: \"sizeof\"|\"typeof\"|\":=\" | \"dup\" | \"swap\" | \"pop\" | \"rot\" | \"input\" | \"print\";"
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
