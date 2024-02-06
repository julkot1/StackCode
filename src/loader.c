//
// Created by julian on 2/2/24.
//
#include "../include/loader.h"

program load(FILE *in)
{
    size_t p_size = get_file_size(in);
    void *program_ptr = malloc(p_size);
    fread(program_ptr, p_size, 1, in);

    program p;
    get_pointers(program_ptr, &p);

    return p;
}
void get_pointers(void *program_ptr, program *p)
{
    p->meta = program_ptr;
    p->const_pool = program_ptr + sizeof(program_meta);
    p->functions = (function *) (program_ptr + sizeof(program_meta) + p->meta->const_pool_size*sizeof(pool_element) +  p->meta->const_stack_size);

    for (int i = 0; i < p->meta->functions_size; ++i)
    {
        p->functions[i].code_addr += (size_t) (
                ((char *) program_ptr + sizeof(program_meta) + p->meta->const_pool_size * sizeof(pool_element) +
                 p->meta->const_stack_size) + p->meta->functions_size * sizeof(function));
    }
    for (int i = 0; i < p->meta->const_pool_size; ++i)
    {
        p->const_pool[i].addr += (size_t)(
                (char *) program_ptr + sizeof(program_meta) + p->meta->const_pool_size * sizeof(pool_element));
    }
    p->var_pool = (element *) (p->functions[p->meta->functions_size - 1].code_addr +
                               p->functions[p->meta->functions_size - 1].code_size *
                               sizeof(operation));
    p->stack = (element *) ((char *) p->var_pool + p->meta->var_pool_size * sizeof(element));
}
size_t get_file_size(FILE *in)
{
    fseek(in, 0, SEEK_END);
    size_t file_size = ftell(in);
    fseek(in, 0, SEEK_SET);
    return file_size;
}