#include "include/functions.h"
#include "include/main.h"
#include "include/bc_parser.h"
#include "include/gc.h"
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
inline struct stack_element op_add_string_number(pool_element *a, struct stack_element b)
{
    pool_element *el = malloc(sizeof(pool_element));
    el->type = STRING;
    size_t size = snprintf(NULL, 0, "%d", b.val.number) + a->size;
    el->val = malloc(size * sizeof(char));
    el->size = size;
    el->ref_counter = 1;
    sprintf(el->val, "%s%d", (char *)a->val, b.val.number);
    return (struct stack_element){.t = PTR, .val.ptr = el};
}
inline struct stack_element op_add_number_string(struct stack_element a, pool_element *b)
{
    pool_element *el = malloc(sizeof(pool_element));
    el->type = STRING;
    size_t size = snprintf(NULL, 0, "%d", a.val.number) + b->size;
    el->val = malloc(size * sizeof(char));
    el->size = size;
    el->ref_counter = 1;
    sprintf(el->val, "%d%s", a.val.number, (char *)b->val);
    return (struct stack_element){.t = PTR, .val.ptr = el};
}
extern struct stack_element op_add_arrays(array *a, array *b)
{
    size_t size = a->length + b->length;
    pool_element *el = malloc(sizeof(pool_element));
    array *arr = malloc(sizeof(array));
    arr->capacity = size;
    arr->length = size;
    arr->elements = malloc(sizeof(struct stack_element) * arr->capacity);
    memcpy(arr->elements, a->elements, a->length * sizeof(struct stack_element));
    memcpy(arr->elements + a->length, b->elements, b->length * sizeof(struct stack_element));
    el->ref_counter = 1;
    el->static_element = 0;
    el->type = ARRAY;
    el->size = arr->capacity;
    el->val = arr;
    return (struct stack_element){.t = PTR, .val.ptr = el};
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
        if (p_a->type == ARRAY && p_b->type == ARRAY)
            return op_add_arrays(p_a->val, p_b->val);
    }
    else if (a.t == PTR || b.t == PTR)
    {
        if (a.t == PTR)
        {
            pool_element *p_a = ((pool_element *)a.val.ptr);
            if (p_a->type == STRING && b.t == NUMBER)
                return op_add_string_number(p_a, b);
        }
        else if (b.t == PTR)
        {
            pool_element *p_b = ((pool_element *)b.val.ptr);
            if (p_b->type == STRING && a.t == NUMBER)
                return op_add_number_string(a, p_b);
        }
    }
    return (struct stack_element){};
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
inline struct stack_element op_arr_new(struct stack_element length, struct stack_element capacity, struct stack_element init)
{
    array *arr = malloc(sizeof(array));
    arr->capacity = capacity.val.number;
    arr->length = length.val.number;
    arr->elements = calloc(arr->capacity, sizeof(pool_element));
    for (size_t i = 0; i < arr->length; i++)
    {
        arr->elements[i].t = init.t;
        arr->elements[i].val = init.val;
        if (init.t == PTR)
        {
            ((pool_element *)init.val.ptr)->ref_counter++;
        }
    }
    pool_element *el = malloc(sizeof(pool_element));
    el->ref_counter = 1;
    el->size = arr->capacity * sizeof(pool_element);
    el->type = ARRAY;
    el->static_element = 0;
    el->val = arr;
    return (struct stack_element){.t = PTR, .val.ptr = el};
}
inline struct stack_element op_arr_append(struct stack_element arr, struct stack_element a)
{
    if (arr.t != PTR)
        return;
    pool_element *el = arr.val.ptr;
    if (el->type != ARRAY)
        return;
    array *arr_ptr = el->val;
    if (arr_ptr->length + 1 >= arr_ptr->capacity)
        return;
    if (a.t == PTR)
    {
        if (((pool_element *)(a.val.ptr))->val == arr_ptr)
        {
            ((pool_element *)(a.val.ptr))->ref_counter--;
            return;
        }
    }
    arr_ptr->elements[arr_ptr->length].t = a.t;
    arr_ptr->elements[arr_ptr->length].val = a.val;
    arr_ptr->length++;
    return arr;
}
inline struct stack_element op_arr_store(struct stack_element arr, struct stack_element idx, struct stack_element a)
{
    if (arr.t != PTR)
        return;
    pool_element *el = arr.val.ptr;
    if (el->type != ARRAY)
        return;
    array *arr_ptr = el->val;
    if (arr_ptr->length <= idx.val.number)
        return;
    if (a.t == PTR)
    {
        if (((pool_element *)(a.val.ptr))->val == arr_ptr)
        {
            ((pool_element *)(a.val.ptr))->ref_counter--;
            return;
        }
    }
    if (arr_ptr->elements[idx.val.number].t == PTR)
    {
        pool_element *e = arr_ptr->elements[idx.val.number].val.ptr;
        e->ref_counter--;
        if (e->ref_counter == 0)
            gc_push(e);
    }
    arr_ptr->elements[idx.val.number].t = a.t;
    arr_ptr->elements[idx.val.number].val = a.val;
    return arr;
}
inline struct stack_element op_arr_load(struct stack_element arr, struct stack_element idx)
{
    if (arr.t != PTR)
        return;
    pool_element *el = arr.val.ptr;
    if (el->type != ARRAY)
        return;
    array *arr_ptr = el->val;
    if (arr_ptr->length <= idx.val.number)
        return;
    if (arr_ptr->elements[idx.val.number].t == PTR)
    {
        ((pool_element *)(arr_ptr->elements[idx.val.number].val.ptr))->ref_counter++;
    }
    return arr_ptr->elements[idx.val.number];
}