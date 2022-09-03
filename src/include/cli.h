#pragma once
#define VERSION "0.0.1"
#include "utils.h"

struct cli_res
{
    char *file;
    char **args;
    int argc;
    int run;
};
typedef struct cli_res cli_res;

void print_help();
void print_version();
cli_res pass_args(int argc, char **args);
