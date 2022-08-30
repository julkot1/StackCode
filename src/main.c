#include <stdlib.h>
#include "./include/structs.h"
#include "./include/vm.h"

int main(int argc, char **args)
{
    operation program[] =
        {
            {OP_PUSH, {1, NUMBER}},
            {OP_BEGIN},
            {OP_DUP},
            {OP_PUSH, {10, NUMBER}},
            {OP_GT},
            {OP_WHILE, {10, NUMBER}},
            {OP_DUP},
            {OP_PRINT},
            {OP_PUSH, {1, NUMBER}},
            {OP_ADD},
            {OP_END, {1, NUMBER}}};
    exec(program, 11);
    exit(EXIT_SUCCESS);
}
