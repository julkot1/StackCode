#include "../../include/main.h"
#include "include/ast_parser.h"
#include "include/ast_analyzer.h"
#include <stdio.h>
#include <errno.h>
#define PATH "examples/program.cml"

int main()
{
    parser_init();
    FILE *fd = fopen(PATH, "r");
    mpc_val_t *ast = parse_ast(fd, PATH);
    fclose(fd);
    if (ast == NULL)
    {
        if (errno == ENOENT)
            printf("Error: invalid syntax\n");
        else
            printf("Error during ast building: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    compiler_program_t pr = ast_analyze(ast);

    exit(EXIT_SUCCESS);
}