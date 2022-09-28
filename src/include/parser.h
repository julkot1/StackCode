#pragma once
#include "./structs.h"
#include <stdio.h>
#define MAX_VAR_SIZE 32

operation parse_token(const char *token);
program parse(FILE *fp);