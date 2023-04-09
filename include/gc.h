#pragma once
#include "main.h"
#include "include/vm.h"
#define GC_TRASH_SIZE 512

#ifndef GC
#define GC

#define GC_EMPTY -1

typedef struct
{
    pool_element **items[GC_TRASH_SIZE];
    int front;
    int rear;
} gc_trash_t;

extern gc_trash_t gc_trash;
extern size_t trash_ptr, freed_ptr;

void gc_push(pool_element **el);
void gc_collect();
void gc_init();
int gc_is_empty();
int gc_is_full();
void gc_collect_scope(context *ctx);
#endif