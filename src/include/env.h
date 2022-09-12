#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "structs.h"
int var_compare(const void *a, const void *b, void *udata);
uint64_t var_hash(const void *item, uint64_t seed0, uint64_t seed1);
void init_env();
extern struct hashmap *globals;
