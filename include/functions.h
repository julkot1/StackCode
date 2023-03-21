#pragma once
#include "main.h"

extern struct stack_element op_add(struct stack_element a, struct stack_element b);
extern struct stack_element op_sub(struct stack_element a, struct stack_element b);
extern struct stack_element op_div(struct stack_element a, struct stack_element b);
extern struct stack_element op_mul(struct stack_element a, struct stack_element b);
extern struct stack_element op_mod(struct stack_element a, struct stack_element b);

extern struct stack_element op_equal(struct stack_element a, struct stack_element b);
extern struct stack_element op_or(struct stack_element a, struct stack_element b);
extern struct stack_element op_and(struct stack_element a, struct stack_element b);
extern struct stack_element op_not_equal(struct stack_element a, struct stack_element b);
extern struct stack_element op_greater(struct stack_element a, struct stack_element b);
extern struct stack_element op_lower(struct stack_element a, struct stack_element b);
extern struct stack_element op_greater_or_equal(struct stack_element a, struct stack_element b);
extern struct stack_element op_lower_or_equal(struct stack_element a, struct stack_element b);
extern struct stack_element op_bitwise_or(struct stack_element a, struct stack_element b);
extern struct stack_element op_bitwise_and(struct stack_element a, struct stack_element b);
extern struct stack_element op_bitwise_xor(struct stack_element a, struct stack_element b);
extern struct stack_element op_left_shift(struct stack_element a, struct stack_element b);
extern struct stack_element op_right_shift(struct stack_element a, struct stack_element b);

extern struct stack_element op_not(struct stack_element a);
extern struct stack_element op_bitwise_not(struct stack_element a);
extern struct stack_element op_sizeof(struct stack_element a);
extern struct stack_element op_typeof(struct stack_element a);

void op_std_out(struct stack_element a);
extern struct stack_element op_std_in(struct stack_element a);

extern void op_vstore(struct stack_element a, int index);
extern struct stack_element op_vload(int index);

char type_name(type t);
