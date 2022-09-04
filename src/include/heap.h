#pragma once
#define HEAP_SIZE 268435456

typedef unsigned char byte_h;
typedef unsigned long size_h;

#ifndef MEM_HEAP
#define MEM_HEAP
byte_h heap[HEAP_SIZE];
#endif

void *alloc(size_h size);
void del(void *ptr);