#pragma once

#include "include/gc.h"

size_t trash_ptr, freed_ptr;
gc_trash_t gc_trash;
void gc_init()
{

    gc_trash.front = -1;
    gc_trash.rear = -1;
}
void gc_push(pool_element *el)
{
    if ((el)->ref_counter != 0)
        return;
    if (gc_is_full())
    {
        printf("Queue is full!\n");
    }
    else
    {
        if (gc_trash.front == -1)
            gc_trash.front = 0;
        gc_trash.rear++;
        gc_trash.items[gc_trash.rear] = el;
    }
}

int gc_is_empty()
{
    if (gc_trash.rear == -1)
        return 1;
    else
        return 0;
}

int gc_is_full()
{
    if (gc_trash.rear == GC_TRASH_SIZE - 1)
        return 1;
    else
        return 0;
}
pool_element **dequeue()
{
    pool_element *item;
    if (gc_is_empty())
    {
        return NULL;
    }
    else
    {
        item = gc_trash.items[gc_trash.front];
        gc_trash.front++;
        if (gc_trash.front > gc_trash.rear)
        {
            gc_trash.front = gc_trash.rear = -1;
        }
    }
    return item;
}
void gc_collect()
{
    if (gc_is_empty())
        return;
    pool_element *el;
    while ((el = dequeue()) != NULL)
    {
        if (mode == DEBUG)
        {
            printf("gc freed: %p\n", (el)->val);
        }
        if (!(el)->static_element)
        {
            free((el)->val);
            continue;
        }
        free(el);
    }
}
void gc_collect_scope(context *ctx)
{
    for (int i = 0; i < ctx->var_ptr; i++)
    {
        ctx->declared_vars[i]->ref_counter--;
        if (ctx->declared_vars[i]->ref_counter == 0)
            gc_push(&ctx->declared_vars[i]);
    }
}