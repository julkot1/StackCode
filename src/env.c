#include "include/env.h"
#ifndef ENV_ALLOCATOR
#define ENV_ALLOCATOR
variable var_allocator[ALLOCATOR_MAX_SIZE];
variable *var_freed[ALLOCATOR_MAX_SIZE];

int var_freed_idx = 0;
int var_idx = 0;
#endif
void init_env()
{
    hcreate(MAX_VAR);
}
void free_env()
{
    hdestroy();
}
variable *alloc(variable var)
{
    if (var_freed_idx == 0)
    {
        var_allocator[var_idx] = var;
        return &var_allocator[var_idx++];
    }

    variable *var_ptr = var_freed[var_freed_idx--];
    *var_ptr = var;

    return var_ptr;
}
void del(variable *ptr)
{
    var_freed[++var_freed_idx] = ptr;
}
int has_var(const char *name)
{
    return hsearch((ENTRY){.key = name}, FIND) != NULL;
}
variable *get_var(const char *name)
{
    ENTRY *e = hsearch((ENTRY){.key = name}, FIND);
    if (e == NULL)
        return NULL;
    return (variable *)(e->data);
}
variable *sotore_var(variable var)
{
    variable *v_ptr = alloc(var);
    ENTRY e;

    e.data = (void *)v_ptr;
    e.key = v_ptr->name;
    hsearch(e, ENTER);
    return v_ptr;
}
void free_var(const char *name)
{
    variable *v_ptr = get_var(name);
    if (v_ptr != NULL)
    {
        del(v_ptr);
    }
}