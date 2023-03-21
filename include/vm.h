#include "main.h"
#include "functions.h"

#ifndef VM
#define VM
#define GLOBAL_FUNCTION_ID 0

typedef struct context context;

struct context
{
    function *fn;
    int state;
    context *parent;
};

void init();
void labels_init();

void parse_program();

void parse(operation op);

extern void op_dup();
extern void op_swap();
extern void op_push(operation op);
extern void op_label(operation op);
extern void op_jmp(operation op);
extern void op_jmp_if(operation op);
extern void op_jmp_if_not(operation op);
extern void op_push(operation op);
extern void op_fun_call(operation op);
extern void op_fun_end();
extern struct stack_element op_pop();

extern function CURRENT_FUNCTION;
#endif