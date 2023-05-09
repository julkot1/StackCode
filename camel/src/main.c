#include "../../include/main.h"
#include "include/ast_parser.h"
#include "include/ast_analyzer.h"
#include <stdio.h>
#define PATH "examples/program.cml"

int main()
{
    parser_init();
    FILE *fd = fopen(PATH, "r");
    mpc_val_t *ast = parse_ast(fd, PATH);
    fclose(fd);
    ast_analyze(ast);

    exit(EXIT_SUCCESS);
}