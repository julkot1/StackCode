//
// Created by julian on 2/6/24.
//

#ifndef CAMEL_FUNCTIONS_H
#define CAMEL_FUNCTIONS_H
extern void op_push(element a, program *p);
extern element op_pop(program *p);
extern void op_dump(element a, program *p);
extern void op_dup(program *p);
extern void op_swap(program *p);

extern element op_add(element a, element b, program *p);
extern element op_sub(element a, element b, program *p);
extern element op_div(element a, element b, program *p);
extern element op_mul(element a, element b, program *p);
extern element op_mod(element a, element b);

extern void op_label(operation op, program *p);
extern void op_jmp(operation op, program *p);
extern void op_jmp_if(operation op,program *p);
extern void op_jmp_if_not(operation op, program *p);



extern element op_or(element a, element b);
extern element op_and(element a, element b);
extern element op_not(element a);

extern element op_equal(element a, element b);
extern element op_greater(element a, element b);
extern element op_lower(element a, element b);
extern element op_greater_or_equal(element a, element b);
extern element op_lower_or_equal(element a, element b);

extern element op_bitwise_or(element a, element b);
extern element op_bitwise_and(element a, element b);
extern element op_bitwise_not(element a);
extern element op_bitwise_xor(element a, element b);
extern element op_left_shift(element a, element b);
extern element op_right_shift(element a, element b);

extern void op_vstore(element pop, operation op, program *p);
extern element op_vload(operation op, program *p);

extern element op_sizeof(element a, program *p);
#endif //CAMEL_FUNCTIONS_H
