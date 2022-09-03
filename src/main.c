#include <stdlib.h>
#include "./include/structs.h"
#include "./include/vm.h"
#include "./include/parser.h"
#include "./include/utils.h"

int main(int argc, char **args)
{

    char code[] = "10 40 = if 34 echo end";
    printc(ColGreen, "StackCode parser is running\n");
    program pr = parse(code);
    printc(ColGreen, "StackCode vm is running");
    printf("\n");
    exec(pr);
    exit(EXIT_SUCCESS);
}
