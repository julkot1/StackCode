#pragma once
#include "../../include/main.h"
#include <stdio.h>
#include <string.h>

program *parse_program_bc(const char *file_path);
void parse_data(FILE *fd, program *pr);
void parse_section(FILE *fd, file_section section, char *data, program *pr);
void parse_const_pool(FILE *fd, program *pr);
void parse_function_bc(FILE *fd, char *name, program *pr);
operation parse_operation(char *line, program *pr);
opcode str_to_opcode(const char *str);
char *opcode_str(char *str);
file_section get_section(const char *str);
void parse_data_value(const char *name, const char *val, program *pr);
int is_payload_operation(opcode op);