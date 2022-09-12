#include "./include/cli.h"
#include <stdio.h>
#include <getopt.h>

struct option long_opt[] =
    {
        {NULL, 0, NULL, 0},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"run", required_argument, NULL, 'r'}};

void print_help()
{
    printf("\nUsage: \n \tsc [options] [arguments]\n");
    printf("\nOptions: \n");
    printf("\t-help              Display this information.\n");
    printf("\t-version           Display StackCode installed version.\n");
    printf("\t-run file [args]   Run specified file.\n");
}
void print_version()
{
    printc(ColGreen, "StackCode");
    printf(" (version %s)\n", VERSION);
}
cli_res pass_args(int argc, char **args)
{
    cli_res res;
    res.argc = 0;
    res.file = NULL;
    res.run = -1;
    const char *short_opt = ":hvr:";
    int c;
    while ((c = getopt_long(argc, args, short_opt, long_opt, NULL)) != -1)
    {
        switch (c)
        {
        case -1:
        case 0:
            break;

        case 'r':
            res.file = optarg;
            res.run = 1;
            break;

        case 'h':
            print_help();
            break;
        case 'v':
            print_version();
            break;
        };
    };
    return res;
}