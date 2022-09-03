#include <stdlib.h>
#include "./include/structs.h"
#include "./include/vm.h"
#include "./include/parser.h"
#include "./include/utils.h"
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include "./include/cli.h"

int main(int argc, char **args)
{

    cli_res res = pass_args(argc, args);
    if (res.file == NULL)
    {
        printc(ColRed, "File not specified\n");
        exit(EXIT_FAILURE);
    }
    else if (res.run == 1)
    {
        FILE *fp = fopen(res.file, "r");
        if (fp == NULL)
        {
            printc(ColRed, "File don't exist\n");
            exit(EXIT_FAILURE);
        }

        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char *code = malloc(size);
        fread(code, 1, size, fp);
        program pr = parse(code);
        fclose(fp);
        free(code);
        exec(pr);
    }

    exit(EXIT_SUCCESS);
}
