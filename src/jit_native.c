#include "include/jit_native.h"
#include "include/main.h"
#include "include/bc_parser.h"
#include <stdlib.h>
#include "string.h"

jit_type_t stack_element;
jit_uint stack_element_size;
jit_type_t stack_element_value;
jit_uint stack_element_value_size;
native_function native_functions[1024];

jit_type_t native_vstore_signature;
jit_type_t native_vload_signature;
char *native_names[1024];
char *native_type_names[128];

native_function create_two_args_function(function_ptr fptr, opcode code)
{
    jit_type_t params[] = {stack_element, stack_element};
    native_function native_f = {.function = fptr, .args = 2, .name = code};
    native_f.signature = jit_type_create_signature(jit_abi_cdecl, stack_element, params, 2, 1);
    native_f.returning = 1;
    return native_f;
}
native_function create_arg_function(function_ptr_1 fptr, opcode code)
{
    native_function native_f = {.function = fptr, .args = 1, .name = code};
    native_f.signature = jit_type_create_signature(jit_abi_cdecl, stack_element, &stack_element, 1, 1);
    native_f.returning = 1;
    return native_f;
}
void types_init()
{
    jit_type_t values[] = {jit_type_int, jit_type_sys_char, jit_type_sys_bool, jit_type_void_ptr, jit_type_sys_long};
    stack_element_value = jit_type_create_union(values, 4, 1);
    stack_element_value_size = jit_type_get_size(stack_element_value);
    jit_type_t elements[] = {jit_type_ubyte, stack_element_value};
    stack_element = jit_type_create_struct(elements, 2, 1);
    stack_element_size = jit_type_get_size(stack_element);

    jit_type_t p1[] = {stack_element, jit_type_sys_int};
    jit_type_t p2[] = {jit_type_sys_int};
    native_vstore_signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, p1, 2, 1);
    native_vload_signature = jit_type_create_signature(jit_abi_cdecl, stack_element, p2, 1, 1);

    native_names[BIN_ADD] = "native_add";
    native_names[BIN_SUB] = "native_sub";
    native_names[BIN_DIV] = "native_div";
    native_names[BIN_MUL] = "native_mul";
    native_names[BIN_NOT_EQUAL] = "native_not_equal";
    native_names[BIN_OR] = "native_or";
    native_names[BIN_AND] = "native_and";
    native_names[BIN_GREATER] = "native_greater";
    native_names[BIN_LOWER] = "native_lower";
    native_names[BIN_GREATER_OR_EQUAL] = "native_greater_or_equal";
    native_names[BIN_LOWER_OR_EQUAL] = "native_lower";
    native_names[BIN_BITWISE_AND] = "native_bitwise_and";
    native_names[BIN_BITWISE_OR] = "native_bitwise_or";
    native_names[BIN_BITWISE_XOR] = "native_bitwise_xor";
    native_names[BIN_BITWISE_NOT] = "native_bitwise_not";
    native_names[BIN_LEFT_SHIFT] = "native_left_shift";
    native_names[BIN_RIGHT_SHIFT] = "native_right_shift";
    native_names[BIN_MOD] = "native_mod";
    native_names[BIN_SIZEOF] = "native_sizeof";
    native_names[BIN_TYPEOF] = "native_typeof";
    native_names[BIN_DUMP] = "native_std_out";
    native_names[BIN_INPUT] = "native_std_in";

    native_functions[BIN_ADD] = create_two_args_function(native_add, BIN_ADD);
    native_functions[BIN_SUB] = create_two_args_function(native_sub, BIN_SUB);
    native_functions[BIN_DIV] = create_two_args_function(native_div, BIN_DIV);
    native_functions[BIN_MUL] = create_two_args_function(native_mul, BIN_MUL);
    native_functions[BIN_EQUAL] = create_two_args_function(native_equal, BIN_EQUAL);
    native_functions[BIN_NOT_EQUAL] = create_two_args_function(native_not_equal, BIN_NOT_EQUAL);
    native_functions[BIN_OR] = create_two_args_function(native_or, BIN_OR);
    native_functions[BIN_AND] = create_two_args_function(native_and, BIN_AND);
    native_functions[BIN_GREATER] = create_two_args_function(native_greater, BIN_GREATER);
    native_functions[BIN_LOWER] = create_two_args_function(native_lower, BIN_LOWER);
    native_functions[BIN_GREATER_OR_EQUAL] = create_two_args_function(native_greater_or_equal, BIN_GREATER_OR_EQUAL);
    native_functions[BIN_LOWER_OR_EQUAL] = create_two_args_function(native_lower, BIN_LOWER_OR_EQUAL);
    native_functions[BIN_BITWISE_AND] = create_two_args_function(native_bitwise_and, BIN_BITWISE_AND);
    native_functions[BIN_BITWISE_OR] = create_two_args_function(native_bitwise_or, BIN_BITWISE_OR);
    native_functions[BIN_BITWISE_XOR] = create_two_args_function(native_bitwise_xor, BIN_BITWISE_XOR);
    native_functions[BIN_LEFT_SHIFT] = create_two_args_function(native_left_shift, BIN_LEFT_SHIFT);
    native_functions[BIN_RIGHT_SHIFT] = create_two_args_function(native_right_shift, BIN_RIGHT_SHIFT);
    native_functions[BIN_MOD] = create_two_args_function(native_mod, BIN_MOD);
    native_functions[BIN_NOT] = create_arg_function(native_not, BIN_NOT);
    // native_functions[BIN_BITWISE_NOT] = create_arg_function(native_bitwise_not, BIN_BITWISE_NOT);
    native_functions[BIN_SIZEOF] = create_arg_function(native_sizeof, BIN_SIZEOF);
    native_functions[BIN_TYPEOF] = create_arg_function(native_typeof, BIN_TYPEOF);
    native_functions[BIN_DUMP] = create_arg_function(native_std_out, BIN_DUMP);
    native_functions[BIN_INPUT] = create_arg_function(native_std_in, BIN_INPUT);

    native_type_names[NUMBER] = TOKEN_TYPE_NUMBER;
    native_type_names[STRING] = TOKEN_TYPE_STRING;
    native_type_names[BOOL] = TOKEN_TYPE_BOOL;
    native_type_names[CHAR] = TOKEN_TYPE_CHAR;
    native_type_names[PTR] = TOKEN_TYPE_PTR;
    native_type_names[TYPE] = TOKEN_TYPE_TYPE;

    native_functions[BIN_DUMP].returning = 0;
}

inline struct stack_element native_add(struct stack_element a, struct stack_element b)
{
    if (a.t == NUMBER && b.t == NUMBER)
        return (struct stack_element){NUMBER, .val.number = (a.val.number + b.val.number)};
    else if (a.t == PTR && b.t == PTR)
    {
        pool_element *p_a = ((pool_element *)a.val.ptr);
        pool_element *p_b = ((pool_element *)b.val.ptr);
        if (p_a->type == STRING && p_b->type == STRING)
        {
            int size = p_a->size + p_b->size;
            pool_element *element = malloc(sizeof(pool_element));
            element->size = size;
            element->type = STRING;
            element->ref_counter = 1;
            element->val = malloc(sizeof(char) * size);
            sprintf((char *)(element->val), "%s%s", (char *)(p_a->val), (char *)(p_b->val));
            return (struct stack_element){PTR, .val.ptr = element};
        }
    }
    else
    {
        pool_element *pool_el;
        struct stack_element const_el;
        int left_join = 0;
        if (a.t == PTR)
        {
            pool_el = ((pool_element *)a.val.ptr);
            const_el = b;
        }
        else if (b.t == PTR)
        {
            pool_el = ((pool_element *)b.val.ptr);
            const_el = a;
            left_join = 1;
        }
        if (const_el.t == NUMBER)
        {
            pool_element *element = malloc(sizeof(pool_element));
            int size = pool_el->size + 20;
            element->val = malloc(sizeof(char) * size);
            element->type = STRING;
            element->ref_counter = 1;
            if (left_join)
                sprintf((char *)(element->val), "%d%s", const_el.val.number, (char *)(pool_el->val));
            else
                sprintf((char *)(element->val), "%s%d", (char *)(pool_el->val), const_el.val.number);
            element->size = strlen((char *)(element->val));
            return (struct stack_element){PTR, .val.ptr = element};
        }
    }

    return (struct stack_element){NUMBER, .val.number = (0)};
}
inline void native_vstore(struct stack_element a, int index)
{
    __p->var_pool.elements[index].ref_counter = 1;
    __p->var_pool.elements[index].static_element = 1;
    __p->var_pool.elements[index].static_val = a.val;
    __p->var_pool.elements[index].type = a.t;
}
inline void native_std_out(struct stack_element a)
{
    if (a.t == NUMBER)
        printf("%d\n", a.val.number);
    else if (a.t == PTR)
        printf("%s", (char *)((pool_element *)a.val.ptr)->val);
    else if (a.t == TYPE)
    {
        printf("%s", native_type_names[a.val.all]);
    }
}
pool_element *read_string_input()
{
#define CHUNK 200
    char *input = NULL;
    char tempbuf[CHUNK];
    pool_element *el = malloc(sizeof(pool_element));
    size_t input_len = 0,
           temp_len = 0;
    do
    {
        fgets(tempbuf, CHUNK, stdin);
        temp_len = strlen(tempbuf);
        input = realloc(input, input_len + temp_len + 1);
        strcpy(input + input_len, tempbuf);
        input_len += temp_len;
    } while (temp_len == CHUNK - 1 && tempbuf[CHUNK - 2] != '\n');

    el->ref_counter = 1;
    el->size = input_len;
    el->static_element = 0;
    el->val = input;
    return el;
}
struct stack_element native_std_in(struct stack_element a)
{
    struct stack_element res;
    res.t = (type)(a.val.all);
    if (a.val.all == NUMBER)
        scanf("%d", &(res.val.number));
    if (a.val.all == STRING)
    {
        pool_element *el = read_string_input();
        res.t = PTR;
        res.val.ptr = el;
    }
    return res;
}
inline struct stack_element native_vload(int index)
{
    return (struct stack_element){
        .t = __p->var_pool.elements[index].type, .val = __p->var_pool.elements[index].static_val};
}
inline struct stack_element native_sub(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number - b.val.number};
}
inline struct stack_element native_div(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number / b.val.number};
}
inline struct stack_element native_mul(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number * b.val.number};
}
inline struct stack_element native_mod(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number % b.val.number};
}
inline struct stack_element native_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number == b.val.number};
}
inline struct stack_element native_or(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number || b.val.number};
}
inline struct stack_element native_and(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number && b.val.number};
}
inline struct stack_element native_not_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number != b.val.number};
}
inline struct stack_element native_greater(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number > b.val.number};
}
inline struct stack_element native_lower(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number < b.val.number};
}
inline struct stack_element native_greater_or_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number >= b.val.number};
}
inline struct stack_element native_lower_or_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number <= b.val.number};
}
inline struct stack_element native_bitwise_or(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number | b.val.number};
}
inline struct stack_element native_bitwise_and(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number & b.val.number};
}
inline struct stack_element native_bitwise_xor(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number ^ b.val.number};
}
inline struct stack_element native_left_shift(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number << b.val.number};
}
inline struct stack_element native_right_shift(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number >> b.val.number};
}

inline struct stack_element native_not(struct stack_element a)
{
    return (struct stack_element){NUMBER, !a.val.number};
}
inline struct stack_element native_bitwise_not(struct stack_element a)
{
    return (struct stack_element){NUMBER, ~a.val.number};
}
inline struct stack_element native_sizeof(struct stack_element a)
{
    if (a.t != PTR)
        return (struct stack_element){NUMBER, sizeof(a.val)};
    return (struct stack_element){NUMBER, ((pool_element *)a.val.ptr)->size};
}
inline struct stack_element native_typeof(struct stack_element a)
{
    if (a.t != PTR)
        return (struct stack_element){TYPE, a.t};
    return (struct stack_element){TYPE, ((pool_element *)a.val.ptr)->type};
}