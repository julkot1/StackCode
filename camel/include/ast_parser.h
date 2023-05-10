#pragma once
#include "mpc.h"
#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

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

void parser_init();
mpc_val_t *parse_ast(FILE *fd, char *file_name);
