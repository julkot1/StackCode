//
// Created by julian on 2/2/24.
//
#include "../include/bc_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

program p_bc;
char **const_key_array;
char **label_key_array;
function *current_fun = NULL;
void *const_pool;
int line_idx = 0;
op_node *op_start, *op_tail;
operation **op_array;
size_t const_pool_size = 0, const_pool_ptr_s = 0, function_ptr, label_ptr = 0;


void parse_bin(FILE *in, FILE *out)
{
    char buffer[255];
    file_section current_section = NOT_DEFINED;
    file_section prev_section = NOT_DEFINED;
    p_bc.meta = malloc(sizeof(program_meta));
    while (fgets(buffer, sizeof(buffer), in) != NULL)
    {
        line_idx++;
        prev_section = current_section;
        parse_line(&current_section, out, buffer);
        if(prev_section == SECTION_HEADER && current_section != SECTION_HEADER)
            write_header(out);
        if(prev_section == SECTION_DATA  && current_section != SECTION_DATA)
            write_const_pool(out);
    }

    write_function();
    match_labels();
    save(out);
    free_list();
    free(p_bc.meta);
    free(const_pool);
}

void match_labels()
{
    for (int i = 0; i < p_bc.meta->functions_size; ++i)
    {
        for (int j = 0; j < p_bc.functions[i].code_size; ++j)
        {
            if(op_array[i][j].code == BIN_LABEL)
            {
                create_label(op_array[i][j].payload.ptr);
                op_array[i][j].payload.idx = label_ptr-1;
            }
        }
    }
    for (int i = 0; i < p_bc.meta->functions_size; ++i)
    {
        for (int j = 0; j < p_bc.functions[i].code_size; ++j)
        {
            if(op_array[i][j].code == BIN_JMP_IF_NOT || op_array[i][j].code == BIN_JMP_IF || op_array[i][j].code == BIN_JMP)
            {
                match_label_name(&op_array[i][j]);
            }
        }
    }
}

void match_label_name(operation *op)
{
    for (int i = 0; i < label_ptr; ++i)
    {
        if(strcmp(label_key_array[i], op->payload.ptr) == 0)
        {
            op->payload.idx = i;
            break;
        }
    }
}

void save(FILE *out)
{
    fwrite(p_bc.meta, sizeof(*p_bc.meta), 1, out);
    fwrite(p_bc.const_pool, sizeof(pool_element), p_bc.meta->const_pool_size, out);
    fwrite(const_pool, sizeof(char), const_pool_ptr_s, out);
    save_functions(out);
}

void save_functions(FILE *out)
{
    size_t code_ptr = 0;
    for (int i = 0; i < p_bc.meta->functions_size; ++i)
    {
        p_bc.functions[i].code_addr = code_ptr;
        code_ptr +=  p_bc.functions[i].code_size * sizeof(operation);
    }
    fwrite(p_bc.functions, sizeof(function), p_bc.meta->functions_size, out);

    for (int i = 0; i < p_bc.meta->functions_size; ++i)
    {
        fwrite(op_array[i], sizeof (operation), p_bc.functions[i].code_size, out);
    }
}

void write_const_pool(FILE *out)
{
    p_bc.meta->const_stack_size = const_pool_ptr_s;
}

void write_header(FILE *out)
{

    const_key_array = malloc(p_bc.meta->const_pool_size * sizeof(char*));
    label_key_array = malloc(p_bc.meta->labels_size * sizeof(char*));
    label_key_array[1] = malloc(sizeof(char) * 2);
    p_bc.const_pool = malloc(sizeof (pool_element) * p_bc.meta->const_pool_size);
    p_bc.functions = malloc(sizeof(function) * p_bc.meta->functions_size);
    op_array = malloc(sizeof (operation *) * p_bc.meta->functions_size);
}


void parse_line(file_section *section, FILE *out, char *line)
{
    line_type_t line_type = get_line_type(line, *section);
    switch (line_type) {
        case CHANGE_HEADER_LINE:
            change_header(section, line);
            break;
        case ATTRIBUTE_LINE:
            write_meta(line);
            break;
        case OPERATION_LINE:
            write_operation(line);
            break;
        case CONST_DEF_LINE:
            write_const(out,line);
            break;
    }
}

void write_operation(char *line)
{
    opcode code = get_opcode(line);

    bc_type bc_payload_type;
    operation op = {.code=0,.payload = 0, .payload_type = 0};
    op.code = code;
    if(is_payload(code))
    {
        char *payload_str = get_payload_str(line);
        bc_payload_type = get_payload_type(payload_str);
        check_payload_bc_type(code, bc_payload_type);
        get_payload(&op, bc_payload_type, payload_str);
    }

    add_op_to_list(op);
    current_fun->code_size++;

}

void create_label(char *str)
{
    label_key_array[label_ptr] = malloc(strlen(str)* sizeof(char));
    strcpy(label_key_array[label_ptr],str);
    label_ptr++;
}

void get_payload(operation *op, bc_type type, const char *payload_str)
{
    op->payload_type = get_vm_payload(type);
    if(op->code == BIN_PUSH && type == bc_LABEL) op->payload_type = PTR;
    op->payload = get_vm_payload_value(op->payload_type, type, payload_str, op->code);
}

value get_vm_payload_value(type type, bc_type bc_type, const char *str, opcode op)
{
    value result;
    if(bc_type == bc_LABEL)
    {
        if(op == BIN_PUSH)result = get_const(str);
        else result = get_label(str);
    }
    else if(bc_type == bc_FUNCTION)result = get_function(str);
    else if(bc_type == bc_VAR)result = get_var(str);
    else if(type == BOOL) result = get_bool(str);
    else if(type == NUMBER) result = get_number(str);
    else if(type == CHAR) result = get_char(str);
    else result = get_type(str);


    return result;
}

value get_const(const char *str)
{
    value result = {.ptr = 0};
    for (int i = 0; i < p_bc.meta->const_pool_size; ++i)
    {
        if(strcmp(str, const_key_array[i]) == 0)
        {
            result.idx = i;
            break;
        }
    }
    return result;
}

value get_type(const char *str)
{
    value result;
    if(strcmp(str, TOKEN_TYPE_BOOL) == 0)result.number = BOOL;
    if(strcmp(str, TOKEN_TYPE_NUMBER) == 0)result.number = NUMBER;
    if(strcmp(str, TOKEN_TYPE_STRING) == 0)result.number = STRING;
    if(strcmp(str, TOKEN_TYPE_TYPE) == 0)result.number = TYPE;
    if(strcmp(str, TOKEN_TYPE_PTR) == 0)result.number = PTR;
    if(strcmp(str, TOKEN_TYPE_CHAR) == 0)result.number = CHAR;
    if(strcmp(str, TOKEN_TYPE_ARRAY) == 0)result.number = ARRAY;
    return result;
}

value get_char(const char *str)
{
    value result;
    result.byte = str[1];
    return result;
}

value get_number(const char *str)
{
    value result;
    result.number = atoi(str);
    return result;
}

value get_bool(const char *str)
{
    value result;
    if(strcmp(str, TOKEN_BOOL_FALSE) == 0)result.number = false;
    if(strcmp(str, TOKEN_BOOL_TRUE) == 0)result.number = true;
    return result;
}

value get_var(const char *str)
{
    return get_number(str+1);
}

value get_function(const char *str)
{
    value result = {.number = 0};
    for (int i = 0; i < p_bc.meta->functions_size; ++i)
    {
        if(strcmp(str, p_bc.functions[i].name) == 0)
        {
            result.idx = p_bc.functions[i].id;
            break;
        }
    }
    return result;
}

value get_label(const char *str) {
    value result;
    result.ptr = malloc(sizeof (char) * strlen(str));
    strcpy(result.ptr, str);
    return result;
}

type get_vm_payload(bc_type type)
{
    if(type == bc_FUNCTION || type == bc_NUMBER || type == bc_VAR || type == bc_LABEL)return NUMBER;
    if(type == bc_BOOL)return BOOL;
    if(type == bc_CHAR)return CHAR;
    if(type == bc_TYPE)return TYPE;
}

void check_payload_bc_type(opcode code, bc_type type)
{
    if(code == BIN_LABEL || code == BIN_JMP || code == BIN_JMP_IF || code == BIN_JMP_IF_NOT)
        if(type == bc_LABEL)return;
    if(code == BIN_CALL && type == bc_FUNCTION)return;
    if(code == BIN_VLOAD || code == BIN_VSTORE)
        if(type == bc_VAR)return;
    if(code == BIN_PUSH)
        if(type != bc_FUNCTION && type != bc_VAR)return;
    fprintf(stderr, "An error occurred (line: %d):\nInvalid operation payload type", line_idx);
    exit(EXIT_FAILURE);
}

bc_type get_payload_type(char *str) {
    if(is_number(str))return bc_NUMBER;
    if(is_type(str))return bc_TYPE;
    if(is_bool(str))return bc_BOOL;
    if(is_char(str))return bc_CHAR;
    if(is_label(str))return bc_LABEL;
    if(is_var(str))return bc_VAR;
    return bc_FUNCTION;
}

bool is_var(char *str) {
    if(str[0] != TOKEN_VAR_POOL_ELEMENT) return false;
    return is_number(str+1);
}

bool is_label(const char *str) {
    return str[0] == TOKEN_SPECIAL_VAL;
}

bool is_char(char *str) {
    if(strlen(str) != 3)return false;
    return str[0] == '\'' && str[2] == '\'';
}

bool is_bool(char *str) {
    return strcmp(str, TOKEN_BOOL_FALSE) == 0 || strcmp(str, TOKEN_BOOL_TRUE) == 0;
}

bool is_type(char *str) {
    return  strcmp(str, TOKEN_TYPE_STRING) == 0 ||
            strcmp(str, TOKEN_TYPE_NUMBER) == 0 ||
            strcmp(str, TOKEN_TYPE_BOOL) == 0 ||
            strcmp(str, TOKEN_TYPE_CHAR) == 0 ||
            strcmp(str, TOKEN_TYPE_ARRAY) == 0 ||
            strcmp(str, TOKEN_TYPE_TYPE) == 0 ||
            strcmp(str, TOKEN_TYPE_PTR) == 0;
}

bool is_number(char *str) {
    char *endptr;
    long num = strtol(str, &endptr, 10);

    if (*endptr == '\0' || *endptr == '\n')
        return true;
    return false;
}

void add_op_to_list(operation op)
{
    op_node * new = malloc(sizeof(op_node));
    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    new->op = op;
    new->next = NULL;

    if (op_start == NULL)
    {
        op_start = new;
        op_tail = new;
    }
    else
    {
        op_tail->next = new;
        op_tail = new;
    }
}

char *get_payload_str(char *line) {
    char *str = (char *) ((line + 4));
    size_t n = strchr(str, ' ') - str;
    str = str+n+1;
    str[strlen(str)-1]= '\0';
    return str;
}

int is_payload(opcode op) {
    return  op == BIN_PUSH ||
            op == BIN_LABEL ||
            op == BIN_JMP ||
            op == BIN_JMP_IF ||
            op == BIN_JMP_IF_NOT ||
            op == BIN_VSTORE ||
            op == BIN_VLOAD ||
            op == BIN_CALL;
}

opcode get_opcode(char *line)
{
    char *str = (char *) ((line + 4));
    size_t n = strchr(str, ' ') - str;
    if (strchr(str, ' ') == NULL ) {
        n = strchr(str, '\n') - str;
    }
    if (strncmp(str, TOKEN_PUSH, n) == 0)
        return BIN_PUSH;
    else if (strncmp(str, TOKEN_ADD, n) == 0)
        return BIN_ADD;
    else if (strncmp(str, TOKEN_SUB, n) == 0)
        return BIN_SUB;
    else if (strncmp(str, TOKEN_DIV, n) == 0)
        return BIN_DIV;
    else if (strncmp(str, TOKEN_MUL, n) == 0)
        return BIN_MUL;
    else if (strncmp(str, TOKEN_DUMP, n) == 0)
        return BIN_DUMP;
    else if (strncmp(str, TOKEN_POP, n) == 0)
        return BIN_POP;
    else if (strncmp(str, TOKEN_DUP, n) == 0)
        return BIN_DUP;
    else if (strncmp(str, TOKEN_SWAP, n) == 0)
        return BIN_SWAP;
    else if (strncmp(str, TOKEN_JMP, n) == 0)
        return BIN_JMP;
    else if (strncmp(str, TOKEN_JMP_IF, n) == 0)
        return BIN_JMP_IF;
    else if (strncmp(str, TOKEN_JMP_IF_NOT, n) == 0)
        return BIN_JMP_IF_NOT;
    else if (strncmp(str, TOKEN_LABEL, n) == 0)
        return BIN_LABEL;
    else if (strncmp(str, TOKEN_EQUAL, n) == 0)
        return BIN_EQUAL;
    else if (strncmp(str, TOKEN_NOT, n) == 0)
        return BIN_NOT;
    else if (strncmp(str, TOKEN_NOT_EQUAL, n) == 0)
        return BIN_NOT_EQUAL;
    else if (strncmp(str, TOKEN_OR, n) == 0)
        return BIN_OR;
    else if (strncmp(str, TOKEN_AND, n) == 0)
        return BIN_AND;
    else if (strncmp(str, TOKEN_GREATER, n) == 0)
        return BIN_GREATER;
    else if (strncmp(str, TOKEN_LOWER, n) == 0)
        return BIN_LOWER;
    else if (strncmp(str, TOKEN_GREATER_OR_EQUAL, n) == 0)
        return BIN_GREATER_OR_EQUAL;
    else if (strncmp(str, TOKEN_LOWER_OR_EQUAL, n) == 0)
        return BIN_LOWER_OR_EQUAL;
    else if (strncmp(str, TOKEN_BITWISE_AND, n) == 0)
        return BIN_BITWISE_AND;
    else if (strncmp(str, TOKEN_BITWISE_OR, n) == 0)
        return BIN_BITWISE_OR;
    else if (strncmp(str, TOKEN_BITWISE_XOR, n) == 0)
        return BIN_BITWISE_XOR;
    else if (strncmp(str, TOKEN_BITWISE_NOT, n) == 0)
        return BIN_BITWISE_NOT;
    else if (strncmp(str, TOKEN_LEFT_SHIFT, n) == 0)
        return BIN_LEFT_SHIFT;
    else if (strncmp(str, TOKEN_RIGHT_SHIFT, n) == 0)
        return BIN_RIGHT_SHIFT;
    else if (strncmp(str, TOKEN_EOP, n) == 0)
        return BIN_EOP;
    else if (strncmp(str, TOKEN_TYPEOF, n) == 0)
        return BIN_TYPEOF;
    else if (strncmp(str, TOKEN_MOD, n) == 0)
        return BIN_MOD;
    else if (strncmp(str, TOKEN_SIZEOF, n) == 0)
        return BIN_SIZEOF;
    else if (strncmp(str, TOKEN_VLOAD, n) == 0)
        return BIN_VLOAD;
    else if (strncmp(str, TOKEN_VSTORE, n) == 0)
        return BIN_VSTORE;
    else if (strncmp(str, TOKEN_INPUT, n) == 0)
        return BIN_INPUT;
    else if (strncmp(str, TOKEN_CALL, n) == 0)
        return BIN_CALL;
    else if (strncmp(str, TOKEN_ARR_NEW_STACK, n) == 0)
        return BIN_ARR_NEW_STACK;
    else if (strncmp(str, TOKEN_ARR_APPEND, n) == 0)
        return BIN_ARR_APPEND;
    else if (strncmp(str, TOKEN_ARR_STORE, n) == 0)
        return BIN_ARR_STORE;
    else if (strncmp(str, TOKEN_ARR_LOAD, n) == 0)
        return BIN_ARR_LOAD;
    return BIN_EOP;
}

void write_const(FILE *out, char *line)
{
    char *name = get_name(line+4);
    size_t size = 0;
    p_bc.const_pool[const_pool_size].t = get_pool_type(line + 5 + strlen(name));
    const_key_array[const_pool_size] = malloc(strlen(name)* sizeof(char));
    strcpy(const_key_array[const_pool_size],name);

    void *value = get_value(line + 5 + strlen(name), &size);

    p_bc.const_pool[const_pool_size].addr = const_pool_ptr_s;
    p_bc.const_pool[const_pool_size].size = size;
    write_to_const_pool(value, size);
    free(value);
    const_pool_size++;
}

void write_to_const_pool(void *value, size_t size)
{
    if(const_pool == NULL)
    {
        const_pool = malloc(sizeof (char)*size);
    }
    else if(const_pool_ptr_s < const_pool_ptr_s+size)
    {
        const_pool = realloc(const_pool, const_pool_ptr_s+size);
    }
    memcpy(const_pool+const_pool_ptr_s, value, size);
    const_pool_ptr_s += size;
}

type get_pool_type(const char *line)
{
    if(line[0] == '"') return STRING;
    if (line[0] == '[') return ARRAY;
}

void *get_value(const char *line, size_t *val_size)
{
    if(line[0] == '"') return get_string(line, val_size);
    if (line[0] == '[') return get_array(line, val_size);
}

void *get_array(const char *line, size_t *val_size)
{
    return NULL;
}

void *get_string(const char *line, size_t *val_size)
{
    size_t size = strlen(line);
    size_t i;
    for ( i = 1; i <  size; ++i)
    {
        if(line[i] == '"')
            if(line[i-1] != '\\')break;
    }
    char *val = malloc(i * sizeof (char));
    strncpy(val, line+1, i-1);
    *val_size = i;
    val[i] = '\0';
    return val;
}

char *get_name(char *line)
{
    int idx = 0;
    while ((line[idx]) != ' ')idx++;
    char *name = malloc(idx * sizeof(char) + 1);
    strncpy(name, line, idx);
    name[idx] = '\0';
    return name;
}

char *get_data(const char *line, size_t offset)
{
    return (char *)(line + offset);
}

int check_attribute(char *line, const char *token, size_t *attr)
{
    size_t prefix_size = strlen(token);
    if(prefix_size >= strlen(line))return -1;
    if(strncmp(line, token, prefix_size) == 0)
    {
        char *data = get_data(line, prefix_size+1);
        data[strlen(data)-1]='\0';
        *attr = atoi(data);
        return 1;
    }
    return -1;
}
void write_meta(char *line)
{
    if(check_attribute(line, TOKEN_HEADER_CONST_SIZE,&p_bc.meta->const_pool_size) == 1)return;
    if(check_attribute(line, TOKEN_HEADER_FUNCTIONS,&p_bc.meta->functions_size) == 1)return;
    if(check_attribute(line, TOKEN_HEADER_LABELS, &p_bc.meta->labels_size) == 1)return;
    if(check_attribute(line, TOKEN_HEADER_STACK_SIZE, &p_bc.meta->stack_size) == 1)return;
    if(check_attribute(line, TOKEN_HEADER_VAR_SIZE, &p_bc.meta->var_pool_size) == 1)return;
}

void change_header(file_section *section, char *line)
{
    if(strcmp(line, TOKEN_SECTION_HEADERS) == 0)
    {
        *section = SECTION_HEADER;
        return;
    }
    if(strcmp(line, TOKEN_SECTION_DATA) == 0)
    {
        *section = SECTION_DATA;
        return;
    }
    if(strncmp(line, TOKEN_SECTION_FUNCTION, strlen(TOKEN_SECTION_FUNCTION)) == 0)
    {
        *section = SECTION_FUNCTION;
        if(current_fun != NULL)write_function();
        create_function(line);
        return;
    }

}

void write_function()
{
    op_array[function_ptr-1] = malloc(sizeof(operation ) * current_fun->code_size);
    op_node *tmp = op_start;
    int idx = 0;
    while (tmp != NULL)
    {
        op_array[function_ptr-1][idx++] = tmp->op;
        tmp = tmp->next;
    }
}

void create_function(char *line)
{
    free_list();
    line[ strlen(line)-1] = '\0';
    strcpy( p_bc.functions[function_ptr].name, line+ strlen(TOKEN_SECTION_FUNCTION)+1);
    p_bc.functions[function_ptr].id = function_ptr;
    current_fun = &p_bc.functions[function_ptr];
    current_fun->code_size = 0;
    function_ptr++;
}


void free_list()
{
    op_node *current = op_start;
    op_node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    op_start = NULL;
    op_tail = NULL;
}

line_type_t get_line_type(const char *line, file_section section)
{
    if(section == NOT_DEFINED) return CHANGE_HEADER_LINE;
    if(line[0] == ':' && line[1]==':') return CHANGE_HEADER_LINE;

    if(section == SECTION_DATA) return CONST_DEF_LINE;
    if(section == SECTION_FUNCTION) return OPERATION_LINE;
    return ATTRIBUTE_LINE;
}