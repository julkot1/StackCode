//
// Created by julian on 2/6/24.
//
#include "../include/cli.h"
#define VRGCLI
#include "../include/vrg.h"
int check_c_or_b(char *arg)
{
    static int found = 0;
    if (found == 1) vrgerror("Invalid '%s' argument. Only one between '-c' and '-b' can be specified.\n", arg);

    found = 1;
    return 1;
}
int check_operation(char *arg)
{

    if(strcmp(arg, "compile") == 0)return 1;
    if(strcmp(arg, "run") == 0)return 1;
    vrgerror("Invalid '%s' operation!\n", arg);
    return 1;
}
cli_command cli_get_command(char *arg)
{
    if(strcmp(arg, "compile") == 0)return cli_COMPILE;
    if(strcmp(arg, "run") == 0)return cli_RUN;
    return cli_RUN;
}

cli_response cli_parse_args(int argc, char **argv)
{
    cli_response res = {.specified_out = false};
    vrgcli("Camel Language (STCVM)") {
        vrgarg("operation\tName of operation: compile, run", check_operation) {
            res.command = cli_get_command(vrgarg);
        }

        vrgarg("-h, --help\tPrint this help") {
            vrgusage();
        }

        vrgarg("-b, --bytecode filename\tCompile bytecode file (mutually exclusive with '-b')",check_c_or_b) {
            res.file_type = cli_BYTECODE;
            res.file_in = malloc(strlen(vrgarg) * sizeof(char));
            strcpy(res.file_in, vrgarg);
        }

        vrgarg("-c, --camel filename\tCompile Camel file (mutually exclusive with '-c')",check_c_or_b) {
            res.file_type = cli_CAMEL;
            res.file_in = malloc(strlen(vrgarg) * sizeof(char));
            strcpy(res.file_in, vrgarg);
        }
        vrgarg("-o, --out outfile\tOutput filename") {
            res.file_out = malloc(strlen(vrgarg) * sizeof(char));
            res.specified_out = true;
            strcpy(res.file_out, vrgarg);
        }
        vrgarg("[filename]\tName of program executable") {
            res.file_in = malloc(strlen(vrgarg) * sizeof(char));
            strcpy(res.file_in, vrgarg);
        }

        vrgarg() {
            if (vrgarg[0] == '-') vrgerror("Unknown option '%s'\n",vrgarg);
            else printf("Other argument %s\n",vrgarg);
        }

    }
    return res;
}