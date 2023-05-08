#pragma once
#include "../../include/main.h"
#include "vm.h"

#define DEBUG_NEXT_TOKEN "next"
#define DEBUG_LIST_STACK_TOKEN "stack"
#define DEBUG_LIST_TOKENS_TOKEN "tokens"
#define DEBUG_LIST_VAR_POOL_TOKEN "vars"
#define DEBUG_PRINT_VAR_TOKEN "var"
#define DEBUG_CTX_TOKEN "ctx"
#define DEBUG_QUIT_TOKEN "quit"
#define DEBUG_HELP_TOKEN "help"

void debug_token(operation op, context *ctx);

void get_debug_operation();
void debug_list_stack();
void debug_list_tokens(function *fn);
void debug_ctx(context *ctx);
void debug_print_var(int id);
void print_help();
