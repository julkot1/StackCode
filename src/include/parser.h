#pragma once
#include "./structs.h"
#include <stdio.h>

operation parse_token(const char *token);
program parse(FILE *fp);