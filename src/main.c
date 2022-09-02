#include <stdlib.h>
#include "./include/structs.h"
#include "./include/vm.h"
#include "./include/parser.h"

int main(int argc, char **args)
{
    char code[] = "10 10 + dup echo 5 * dup echo";
    program pr = parse(code);
    exec(pr);
    exit(EXIT_SUCCESS);
}
