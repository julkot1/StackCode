#include "include/env.h"
#include "include/hashmap.h"
struct hashmap *globals;
int var_compare(const void *a, const void *b, void *udata)
{
    const variable *a_var = a;
    const variable *b_var = b;
    return strcmp(a_var->name, b_var->name);
}

uint64_t var_hash(const void *item, uint64_t seed0, uint64_t seed1)
{
    const variable *var = item;
    return hashmap_sip(var->name, strlen(var->name), seed0, seed1);
}

void init_env()
{
    globals = hashmap_new(sizeof(variable), 0, 0, 0, var_hash, var_compare, NULL, NULL);
}
void free_env()
{
    hashmap_free(globals);
}