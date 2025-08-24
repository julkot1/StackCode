#include "Header.h"

STC_CREATE_VTABLE(add_table, stc_function_2_t);
STC_CREATE_VTABLE(sub_table, stc_function_2_t);
STC_CREATE_VTABLE(mul_table, stc_function_2_t);
STC_CREATE_VTABLE(div_table, stc_function_2_t);

STC_CREATE_VTABLE(le_table, stc_function_2_t);
STC_CREATE_VTABLE(lt_table, stc_function_2_t);
STC_CREATE_VTABLE(gt_table, stc_function_2_t);
STC_CREATE_VTABLE(ge_table, stc_function_2_t);
STC_CREATE_VTABLE(eq_table, stc_function_2_t);
STC_CREATE_VTABLE(neq_table, stc_function_2_t);
STC_CREATE_VTABLE(and_table, stc_function_2_t);
STC_CREATE_VTABLE(or_table, stc_function_2_t);

// Arithmetic
DEFINE_STC_BINOP(add, +);
DEFINE_STC_BINOP(sub, -);
DEFINE_STC_BINOP(mul, *);
DEFINE_STC_BINOP(div, /);

// Logic: all output STC_BOOL_TYPE
DEFINE_STC_BINOP_TYPED(le, <=, STC_BOOL_TYPE);
DEFINE_STC_BINOP_TYPED(lt, <, STC_BOOL_TYPE);
DEFINE_STC_BINOP_TYPED(gt, >, STC_BOOL_TYPE);
DEFINE_STC_BINOP_TYPED(ge, >=, STC_BOOL_TYPE);
DEFINE_STC_BINOP_TYPED(eq, ==, STC_BOOL_TYPE);
DEFINE_STC_BINOP_TYPED(neq, !=, STC_BOOL_TYPE);

// Boolean logic (only for BOOL type)
DEFINE_STC_BOOL_BINOP_TYPED(and, &&)
DEFINE_STC_BOOL_BINOP_TYPED(or, ||)

// Boolean unary not
DEFINE_STC_BOOL_UNOP_TYPED(not, !)

void lib_init init()
{
    STC_ADD_TO_VTABLE_OPERATION(add_table, add);
    STC_ADD_TO_VTABLE_OPERATION(sub_table, sub);
    STC_ADD_TO_VTABLE_OPERATION(mul_table, mul);
    STC_ADD_TO_VTABLE_OPERATION(div_table, div);

    STC_ADD_TO_VTABLE_OPERATION(le_table, le);
    STC_ADD_TO_VTABLE_OPERATION(lt_table, lt);
    STC_ADD_TO_VTABLE_OPERATION(gt_table, gt);
    STC_ADD_TO_VTABLE_OPERATION(ge_table, ge);
    STC_ADD_TO_VTABLE_OPERATION(eq_table, eq);
    STC_ADD_TO_VTABLE_OPERATION(neq_table, neq);

    STC_ADD_TO_VTABLE(and_table, STC_BOOL_TYPE, STC_BOOL_TYPE, and_BOOL_BOOL);
    STC_ADD_TO_VTABLE(or_table, STC_BOOL_TYPE, STC_BOOL_TYPE, or_BOOL_BOOL);
}

stc_value token("+") add(stc_value a, stc_value b)
{
    stc_function_2_t add_func = add_table[a.type][b.type];
    if (add_func != NULL)
    {
        return add_func(a, b);
    }
	return (stc_value){.type = STC_I64_TYPE, .val = 0};

}

stc_value token("-") sub(stc_value a, stc_value b)
{
    stc_function_2_t sub_func = sub_table[a.type][b.type];
    if (sub_func != NULL)
    {
        return sub_func(a, b);
    }
	return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("*") mul(stc_value a, stc_value b)
{
    stc_function_2_t mul_func = mul_table[a.type][b.type];
    if (mul_func != NULL)
    {
        return mul_func(a, b);
    }
	return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("/") div(stc_value a, stc_value b)
{
    stc_function_2_t div_func = div_table[a.type][b.type];
    if (div_func != NULL)
    {
        return div_func(a, b);
    }
	return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("<=") le(stc_value a, stc_value b)
{
    stc_function_2_t le_func = le_table[a.type][b.type];
    if (le_func != NULL)
        return le_func(a, b);
	return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("<") lt(stc_value a, stc_value b)
{
    stc_function_2_t lt_func = lt_table[a.type][b.type];
    if (lt_func != NULL)
        return lt_func(a, b);
	return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token(">") gt(stc_value a, stc_value b)
{
    stc_function_2_t gt_func = gt_table[a.type][b.type];
    if (gt_func != NULL)
        return gt_func(a, b);
	return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token(">=") ge(stc_value a, stc_value b)
{
    stc_function_2_t ge_func = ge_table[a.type][b.type];
    if (ge_func != NULL)
        return ge_func(a, b);
	return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("==") eq(stc_value a, stc_value b)
{
    stc_function_2_t eq_func = eq_table[a.type][b.type];
    if (eq_func != NULL)
        return eq_func(a, b);
    return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("!=") neq(stc_value a, stc_value b)
{
    stc_function_2_t neq_func = neq_table[a.type][b.type];
    if (neq_func != NULL)
        return neq_func(a, b);
    return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("and") and(stc_value a, stc_value b)
{
    stc_function_2_t and_func = and_table[a.type][b.type];
    if (and_func != NULL)
        return and_func(a, b);
    return (stc_value){.type = STC_I64_TYPE, .val = 0};
}

stc_value token("or") or(stc_value a, stc_value b)
{
    stc_function_2_t or_func = or_table[a.type][b.type];
    if (or_func != NULL)
        return or_func(a, b);
    return (stc_value){.type = STC_I64_TYPE, .val = 0};
}


stc_value token("not") notV(stc_value a)
{
    if (a.type == STC_BOOL_TYPE)
        return not_BOOL(a);
    return (stc_value){.type = STC_I64_TYPE, .val = 0};
}
