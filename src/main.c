#include "include/main.h"
#include "include/bc_parser.h"
#include "include/jit_parser.h"
#include <jit/jit.h>
#include <stdio.h>
#include <stdlib.h>
program *__p;
int main()
{
    __p = parse_program_bc("program.bc");

    init();
    parse_program();

    exit(EXIT_SUCCESS);
}