#include "include/main.h"
#include "include/bc_parser.h"
#include "include/vm.h"
#include <time.h>

program *__p;
int main()
{

    __p = parse_program_bc("program.bc");
    init();
    mode = DEBUG;
    parse_program();
    exit(EXIT_SUCCESS);
}