#include <stdlib.h>
#include "./include/structs.h"
#include "./include/vm.h"
#include "./include/parser.h"
#include "./include/utils.h"
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include "./include/env.h"
#include "./include/cli.h"

int main(int argc, char **args)
{

    cli_res res = pass_args(argc, args);
    if (res.file == NULL)
    {
        printc(ColRed, "File is not specified\n");
        printf("%d", res.run);
        exit(EXIT_FAILURE);
    }
    else if (res.run == 1)
    {
        FILE *fp = fopen(res.file, "r");
        if (fp == NULL)
        {
            printc(ColRed, "File does not exist\n");
            exit(EXIT_FAILURE);
        }

        program pr = parse(fp);
        fclose(fp);

        exec(pr);
    }

    exit(EXIT_SUCCESS);
}
