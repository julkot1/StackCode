//
// Created by julian on 2/6/24.
//

#ifndef CAMEL_CLI_H
#define CAMEL_CLI_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define CLI_RUN_COMMAND "run"
#define CLI_COMPILE_COMMAND "compile"


typedef enum {
    cli_RUN, cli_COMPILE
} cli_command;
typedef enum {
    cli_BYTECODE, cli_CAMEL
} cli_file_type;
typedef struct {
    cli_command command;
    cli_file_type file_type;
    char *file_in, *file_out;
    bool specified_out;
} cli_response;

cli_response cli_parse_args(int argc, char **argv);

#endif //CAMEL_CLI_H
