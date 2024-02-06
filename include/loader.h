//
// Created by julian on 2/2/24.
//

#ifndef CAMEL_LOADER_H
#define CAMEL_LOADER_H

#include <stdio.h>
#include "vm.h"

program load(FILE *in);
size_t get_file_size(FILE *in);
void get_pointers(void *program_ptr, program *p);
#endif //CAMEL_LOADER_H
