#include <stdio.h>
#include "../include/bc_parser.h"
#include "../include/loader.h"
#include "../include/cli.h"
#include "../include/vm.h"

void compile(cli_response res);

void run(cli_response res);

int main(int argc, char **argv)
{
    cli_response res = cli_parse_args(argc, argv);
    if(res.command == cli_COMPILE)
        compile(res);
    if(res.command == cli_RUN)
        run(res);
    exit(EXIT_SUCCESS);
}

void run(cli_response res) {
    FILE *in = fopen(res.file_in, "rb");
    program p = load(in);
    fclose(in);
    execute(p);

}

void compile(cli_response res)
{
    FILE  *in = fopen(res.file_in, "r");
    FILE  *out= fopen(res.specified_out?res.file_out:"app.bin", "wb");
    parse_bin(in,out);
    fclose(in);
    fclose(out);
}
