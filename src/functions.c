#include "include/functions.h"
#include "include/main.h"
#include "include/bc_parser.h"
#include <stdlib.h>
#include "string.h"

inline struct stack_element op_add_numbers(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, .val.number = (a.val.number + b.val.number)};
}
inline struct stack_element op_add_strings(pool_element *p_a, pool_element *p_b)
{
    pool_element *element = malloc(sizeof(pool_element));
    int size = p_a->size + p_b->size;
    element->size = size;
    element->type = STRING;
    element->static_element = 0;
    element->ref_counter = 1;
    element->val = malloc(sizeof(char) * size);
    sprintf((char *)(element->val), "%s%s", (char *)(p_a->val), (char *)(p_b->val));
    return (struct stack_element){
        PTR,
        .val.ptr = element};
}
inline struct stack_element op_add_string_number(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){};
}
inline struct stack_element op_add(struct stack_element a, struct stack_element b)
{
    if (a.t == NUMBER && b.t == NUMBER)
        return op_add_numbers(a, b);
    else if (a.t == PTR && b.t == PTR)
    {
        pool_element *p_a = ((pool_element *)a.val.ptr);
        pool_element *p_b = ((pool_element *)b.val.ptr);
        if (p_a->type == STRING && p_b->type == STRING)
            return op_add_strings(p_a, p_b);
    }
    return (struct stack_element){};

    /*
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
*/
}
inline void op_vstore(struct stack_element a, int index)
{
    if (a.t == PTR)
    {
        __p->var_pool.elements[index].ref_counter = -1;
        __p->var_pool.elements[index].static_element = 0;
        __p->var_pool.elements[index].val = a.val.ptr;
        __p->var_pool.elements[index].type = a.t;
        return;
    }
    __p->var_pool.elements[index].ref_counter = 1;
    __p->var_pool.elements[index].static_element = 1;
    __p->var_pool.elements[index].static_val = a.val;
    __p->var_pool.elements[index].type = a.t;
}
inline void op_std_out(struct stack_element a)
{
    if (a.t == NUMBER)
        printf("%d\n", a.val.number);
    else if (a.t == PTR)
        printf("%s", (char *)((pool_element *)a.val.ptr)->val);
    else if (a.t == TYPE)
    {
        printf("%d", a.val.all);
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
    input[input_len - 1] = '\0';
    el->ref_counter = 1;
    el->size = input_len;
    el->static_element = 0;
    el->val = input;
    el->type = STRING;
    return el;
}
struct stack_element op_std_in(struct stack_element a)
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
inline struct stack_element op_vload(int index)
{
    if (__p->var_pool.elements[index].type == PTR)
    {
        ((pool_element *)__p->var_pool.elements[index].val)->ref_counter++;
        return (struct stack_element){
            .t = __p->var_pool.elements[index].type, .val.ptr = __p->var_pool.elements[index].val};
    }
    return (struct stack_element){
        .t = __p->var_pool.elements[index].type, .val = __p->var_pool.elements[index].static_val};
}
inline struct stack_element op_sub(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number - b.val.number};
}
inline struct stack_element op_div(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number / b.val.number};
}
inline struct stack_element op_mul(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number * b.val.number};
}
inline struct stack_element op_mod(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number % b.val.number};
}
inline struct stack_element op_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number == b.val.number};
}
inline struct stack_element op_or(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number || b.val.number};
}
inline struct stack_element op_and(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number && b.val.number};
}
inline struct stack_element op_not_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number != b.val.number};
}
inline struct stack_element op_greater(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number > b.val.number};
}
inline struct stack_element op_lower(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number < b.val.number};
}
inline struct stack_element op_greater_or_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number >= b.val.number};
}
inline struct stack_element op_lower_or_equal(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number <= b.val.number};
}
inline struct stack_element op_bitwise_or(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number | b.val.number};
}
inline struct stack_element op_bitwise_and(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number & b.val.number};
}
inline struct stack_element op_bitwise_xor(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number ^ b.val.number};
}
inline struct stack_element op_left_shift(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number << b.val.number};
}
inline struct stack_element op_right_shift(struct stack_element a, struct stack_element b)
{
    return (struct stack_element){NUMBER, a.val.number >> b.val.number};
}

inline struct stack_element op_not(struct stack_element a)
{
    return (struct stack_element){NUMBER, !a.val.number};
}
inline struct stack_element op_bitwise_not(struct stack_element a)
{
    return (struct stack_element){NUMBER, ~a.val.number};
}
inline struct stack_element op_sizeof(struct stack_element a)
{
    if (a.t != PTR)
        return (struct stack_element){NUMBER, sizeof(a.val)};
    return (struct stack_element){NUMBER, ((pool_element *)a.val.ptr)->size};
}
inline struct stack_element op_typeof(struct stack_element a)
{
    if (a.t != PTR)
        return (struct stack_element){TYPE, a.t};
    return (struct stack_element){TYPE, ((pool_element *)a.val.ptr)->type};
}