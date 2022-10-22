#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "structs.h"
#include <search.h>

#define MAX_VAR 4096
#define ALLOCATOR_MAX_SIZE 1048576

variable *alloc(variable var);
void del(variable *ptr);

void init_env();
void free_env();

variable *sotore_var(variable var);
variable *get_var(const char *name);
int has_var(const char *name);
void free_var(const char *name);