//
// Created by julian on 2/2/24.
//
#pragma once
#include <stdio.h>
#include <stdlib.h>


#ifndef CAMEL_TOKENS_H
#define CAMEL_TOKENS_H
#define TOKEN_SECTION_HEADERS "::HEADERS\n"
#define TOKEN_SECTION_DATA "::DATA\n"
#define TOKEN_SECTION_FUNCTION "::FUN"

#define TOKEN_HEADER_STACK_SIZE "    stack_size"
#define TOKEN_HEADER_LABELS "    labels"
#define TOKEN_HEADER_FUNCTIONS "    functions"
#define TOKEN_HEADER_CONST_SIZE "    const_pool"
#define TOKEN_HEADER_VAR_SIZE "    var_pool"

#define TOKEN_PUSH "push"
#define TOKEN_ADD "add"
#define TOKEN_SUB "sub"
#define TOKEN_DIV "div"
#define TOKEN_MUL "mul"
#define TOKEN_MOD "mod"
#define TOKEN_DUMP "dump"
#define TOKEN_POP "pop"
#define TOKEN_DUP "dup"
#define TOKEN_SWAP "swap"
#define TOKEN_JMP "jmp"
#define TOKEN_JMP_IF "jme"
#define TOKEN_JMP_IF_NOT "jmn"
#define TOKEN_LABEL "lb"
#define TOKEN_EQUAL "eq"
#define TOKEN_NOT "not"
#define TOKEN_NOT_EQUAL "neq"
#define TOKEN_OR "or"
#define TOKEN_AND "and"
#define TOKEN_GREATER "gr"
#define TOKEN_LOWER "lt"
#define TOKEN_GREATER_OR_EQUAL "ge"
#define TOKEN_LOWER_OR_EQUAL "le"
#define TOKEN_BITWISE_AND "band"
#define TOKEN_BITWISE_OR "bor"
#define TOKEN_BITWISE_XOR "xor"
#define TOKEN_BITWISE_NOT "bnot"
#define TOKEN_LEFT_SHIFT "shl"
#define TOKEN_RIGHT_SHIFT "shr"
#define TOKEN_TYPEOF "typeof"
#define TOKEN_SIZEOF "sizeof"
#define TOKEN_EOP "eop"
#define TOKEN_VLOAD "vld"
#define TOKEN_VSTORE "vst"
#define TOKEN_INPUT "in"
#define TOKEN_CALL "call"
#define TOKEN_ARR_STORE "@st"
#define TOKEN_ARR_APPEND "@app"
#define TOKEN_ARR_NEW_STACK "s@arr"
#define TOKEN_ARR_LOAD "@ld"

#define TOKEN_SPECIAL_VAL '.'
#define TOKEN_VAR_POOL_ELEMENT '#'

#define TOKEN_TYPE_NUMBER "number"
#define TOKEN_TYPE_STRING "string"
#define TOKEN_TYPE_TYPE "type"
#define TOKEN_TYPE_PTR "ptr"
#define TOKEN_TYPE_BOOL "bool"
#define TOKEN_TYPE_CHAR "char"
#define TOKEN_TYPE_ARRAY "arr"

#define TOKEN_BOOL_TRUE "true"
#define TOKEN_BOOL_FALSE "false"



#endif //CAMEL_TOKENS_H
