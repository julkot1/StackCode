//
// Created by julian on 2/2/24.
//

#ifndef CAMEL_BC_PARSER_H
#define CAMEL_BC_PARSER_H
#include "tokens.h"
#include "vm.h"
#include <stdbool.h>
typedef enum {
    OPERATION_LINE,
    CHANGE_HEADER_LINE,
    CONST_DEF_LINE,
    ATTRIBUTE_LINE
} line_type_t;
typedef enum
{
    bc_NUMBER,
    bc_BOOL,
    bc_CHAR,
    bc_TYPE,
    bc_LABEL,
    bc_FUNCTION,
    bc_VAR
} bc_type;


void parse_bin(FILE *in, FILE *out);
void parse_line(file_section *section, FILE *out, char *line);
line_type_t get_line_type(const char *line, file_section section);
void change_header(file_section *section, char *line);

void write_meta(char *line);
void write_const(FILE *pFile, char *line);
void write_header(FILE *out);
void write_const_pool(FILE *out);
void write_to_const_pool(void *value, size_t size);
void write_function();
void write_operation(char *line);

int check_attribute(char *line, const char *token, size_t *attr);

char *get_name(char *line);
void *get_value(const char *line, size_t *val_size);
void *get_string(const char *line, size_t *val_size);
void *get_array(const char *line, size_t *val_size);

type get_pool_type(const char *line);


void save(FILE *out);
void free_list();

void save_functions(FILE *out);
void create_function(char *line);

opcode get_opcode(char *line);
void add_op_to_list(operation op);

bool is_number(char *str);
bool is_type(char *str);
bool is_bool(char *str);
bool is_char(char *str);
bool is_label(const char *str);
bool is_var(char *str);

char *get_payload_str(char *line);
void check_payload_bc_type(opcode code, bc_type type);
void get_payload(operation *op, bc_type type, const char *payload_str);
type get_vm_payload(bc_type type);
bc_type get_payload_type(char *str);
int is_payload(opcode op);

value get_vm_payload_value(type type, bc_type bc_type, const char *str, opcode op);
value get_label(const char *str);
value get_function(const char *str);
value get_var(const char *str);
value get_bool(const char *str);
value get_number(const char *str);
value get_char(const char *str);
value get_type(const char *str);
value get_const(const char *str);

void create_label(char *str);
void match_labels();
void match_label_name(operation *op);
#endif //CAMEL_BC_PARSER_H
