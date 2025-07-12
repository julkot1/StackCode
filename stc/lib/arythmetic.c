#include "Header.h"

STC_CREATE_VTABLE(add_table, stc_function_2_t);
STC_CREATE_VTABLE(sub_table, stc_function_2_t);
STC_CREATE_VTABLE(mul_table, stc_function_2_t);
STC_CREATE_VTABLE(div_table, stc_function_2_t);

DEFINE_STC_BINOP(add, +);
DEFINE_STC_BINOP(sub, -);
DEFINE_STC_BINOP(mul, *);
DEFINE_STC_BINOP(div, /);

void lib_init init()
{
    STC_ADD_TO_VTABLE_OPERATION(add_table, add);
    STC_ADD_TO_VTABLE_OPERATION(sub_table, add);
    STC_ADD_TO_VTABLE_OPERATION(mul_table, add);
    STC_ADD_TO_VTABLE_OPERATION(div_table, add);

}

stc_value token("+") add(stc_value a, stc_value b)
{
    stc_function_2_t add_func = add_table[a.type][b.type];
    if (add_func != NULL)
    {
        return add_func(a, b);
    }
}
