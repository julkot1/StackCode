#include "include/bc_parser.h"
#include <stdio.h>
#include <stdlib.h>

int function_idx;

program *parse_program_bc(const char *file_path)
{
    function_idx = 0;
    program *pr = malloc(sizeof(program));
    FILE *fd = fopen(file_path, "r");
    size_t len = 0;
    char *line = NULL;
    while (getline(&line, &len, fd) != -1)
    {

        char *header = strtok(line, " ");
        char *data = strtok(NULL, "\n");

        parse_section(fd, get_section(header), data, pr);
    }
    fclose(fd);

    return pr;
}
file_section get_section(const char *str)
{
    if (strcmp(str, TOKEN_SECTION_FUNCTIONS) == 0)
        return SECTION_FUNCTION;
    else if (strcmp(str, TOKEN_SECTION_DATA) == 0)
        return SECTION_DATA;
    return SECTION_CONST;
}
void parse_section(FILE *fd, file_section section, char *data, program *pr)
{

    if (section == SECTION_DATA)
        parse_data(fd, pr);
    else if (section == SECTION_CONST)
        parse_const_pool(fd, pr);
    else if (section == SECTION_FUNCTION)
        parse_function_bc(fd, data, pr);
}
void parse_function_bc(FILE *fd, char *name, program *pr)
{

    size_t name_len = strlen(name);

    pr->meta.function_names[function_idx] = malloc(name_len * sizeof(char));
    strcpy(pr->meta.function_names[function_idx], name);
    pr->functions[function_idx].id = function_idx;
    size_t len = 1;
    pr->functions[function_idx].code_size = 1;
    op_node *root = malloc(sizeof(op_node));
    op_node *tmp = root;
    char *line = NULL;
    do
    {
        getline(&line, &len, fd);
        if (*line == '\n')
            break;
        line[len - 2] = '\0';
        tmp->op = parse_operation(line, pr);
        tmp->next = malloc(sizeof(op_node));
        tmp = tmp->next;
        pr->functions[function_idx].code_size++;
    } while (1);
    pr->functions[function_idx].code = malloc(pr->functions[function_idx].code_size * sizeof(operation));

    tmp = root;
    int op_idx = 0;
    while (tmp != NULL)
    {
        pr->functions[function_idx].code[op_idx] = tmp->op;
        tmp = tmp->next;
        op_idx++;
    }

    function_idx++;
}

void parse_const_pool(FILE *fd, program *pr)
{
    pr->const_pool.elements = malloc(sizeof(pool_element) * pr->meta.const_pool_size);
    pr->const_pool.ptr = 0;
    size_t len = 0;
    char *data;
    char *line = NULL;
    do
    {
        getline(&line, &len, fd);
        if (*line == '\n')
            break;
        data = strtok(line, " ");
        size_t l = strlen(data);
        if (data[0] = '\"' && data[l - 2] == '\"')
        {
            pool_element *el = &((pr->const_pool.elements)[pr->const_pool.ptr]);
            el->ref_counter = 0;
            el->size = l - 3;
            el->type = STRING;
            el->val = malloc(sizeof(char) * el->size);
            strncpy(el->val, data + 1, el->size);
            pr->const_pool.ptr++;
        }
    } while (1);
}

void parse_data(FILE *fd, program *pr)
{

    size_t len = 0;
    char *line = NULL;
    do
    {
        getline(&line, &len, fd);
        if (*line == '\n')
            break;
        char *name = strtok(line, " ");
        char *val = strtok(NULL, "");
        val[strlen(val) - 1] = '\0';
        parse_data_value(name, val, pr);
    } while (1);
}
void parse_data_value(const char *name, const char *val, program *pr)
{
    if (strcmp(name, TOKEN_DATA_LABELS) == 0)
        pr->meta.labels_size = atoi(val);
    else if (strcmp(name, TOKEN_DATA_STACK_SIZE) == 0)
        pr->meta.stack_size = atoi(val);
    else if (strcmp(name, TOKEN_DATA_CONST_SIZE) == 0)
        pr->meta.const_pool_size = atoi(val);
    else if (strcmp(name, TOKEN_DATA_VAR_SIZE) == 0)
    {
        pr->meta.var_pool_size = atoi(val);
        pr->var_pool.elements = malloc(sizeof(pool_element) * pr->meta.var_pool_size);
    }
    else if (strcmp(name, TOKEN_DATA_FUNCTIONS) == 0)
    {
        pr->meta.functions_size = atoi(val);
        pr->functions = malloc(sizeof(function) * pr->meta.functions_size);
        pr->meta.function_names = malloc(sizeof(char *) * pr->meta.functions_size);
    }
}

int is_type(char *c)
{
    if (strcmp(c, TOKEN_TYPE_BOOL) == 0 ||
        strcmp(c, TOKEN_TYPE_NUMBER) == 0 ||
        strcmp(c, TOKEN_TYPE_STRING) == 0 ||
        strcmp(c, TOKEN_TYPE_CHAR) == 0 ||
        strcmp(c, TOKEN_TYPE_PTR) == 0)
        return 1;
    return 0;
}
int to_type(char *c)
{
    if (strcmp(c, TOKEN_TYPE_BOOL) == 0)
        return BOOL;
    else if (strcmp(c, TOKEN_TYPE_NUMBER) == 0)
        return NUMBER;
    else if (strcmp(c, TOKEN_TYPE_STRING) == 0)
        return STRING;
    else if (strcmp(c, TOKEN_TYPE_CHAR) == 0)
        return CHAR;
    else if (strcmp(c, TOKEN_TYPE_PTR) == 0)
        return PTR;
    return NUMBER;
}
operation parse_operation(char *line, program *pr)
{
    operation op;
    char *op_str = opcode_str(line);
    op.code = str_to_opcode(op_str);
    if (is_payload_operation(op.code))
    {
        char *payload = strtok(NULL, "\n");
        if (is_type(payload))
        {
            op.payload_type = TYPE;
            op.payload.all = to_type(payload);
        }
        else if (payload[0] == TOKEN_CONST_POOL_ELEMENT)
        {
            op.payload_type = PTR;
            op.payload.ptr = &(pr->const_pool.elements[atoi(payload + 1)]);
        }
        else if (payload[0] == TOKEN_VAR_POOL_ELEMENT)
        {
            op.payload_type = PTR;
            op.payload.number = atoi(payload + 1);
        }
        else
        {
            op.payload_type = NUMBER;
            op.payload.number = atoi(payload);
        }
    }
    return op;
}
char *opcode_str(char *str)
{
    char *op_str = strtok(str, " ");
    size_t len = strlen(op_str);
    if (op_str[len - 1] == '\n')
        op_str[len - 1] = '\0';
    return op_str;
}
int is_payload_operation(opcode op)
{
    return op == BIN_PUSH || op == BIN_LABEL || op == BIN_JMP || op == BIN_JMP_IF || op == BIN_JMP_IF_NOT || op == BIN_VSTORE || op == BIN_VLOAD || op == BIN_CALL;
}
opcode str_to_opcode(const char *str)
{
    if (strcmp(str, TOKEN_PUSH) == 0)
        return BIN_PUSH;
    else if (strcmp(str, TOKEN_ADD) == 0)
        return BIN_ADD;
    else if (strcmp(str, TOKEN_SUB) == 0)
        return BIN_SUB;
    else if (strcmp(str, TOKEN_DIV) == 0)
        return BIN_DIV;
    else if (strcmp(str, TOKEN_MUL) == 0)
        return BIN_MUL;
    else if (strcmp(str, TOKEN_DUMP) == 0)
        return BIN_DUMP;
    else if (strcmp(str, TOKEN_POP) == 0)
        return BIN_POP;
    else if (strcmp(str, TOKEN_DUP) == 0)
        return BIN_DUP;
    else if (strcmp(str, TOKEN_SWAP) == 0)
        return BIN_SWAP;
    else if (strcmp(str, TOKEN_JMP) == 0)
        return BIN_JMP;
    else if (strcmp(str, TOKEN_JMP_IF) == 0)
        return BIN_JMP_IF;
    else if (strcmp(str, TOKEN_JMP_IF_NOT) == 0)
        return BIN_JMP_IF_NOT;
    else if (strcmp(str, TOKEN_LABEL) == 0)
        return BIN_LABEL;
    else if (strcmp(str, TOKEN_EQUAL) == 0)
        return BIN_EQUAL;
    else if (strcmp(str, TOKEN_NOT) == 0)
        return BIN_NOT;
    else if (strcmp(str, TOKEN_NOT_EQUAL) == 0)
        return BIN_NOT_EQUAL;
    else if (strcmp(str, TOKEN_OR) == 0)
        return BIN_OR;
    else if (strcmp(str, TOKEN_AND) == 0)
        return BIN_AND;
    else if (strcmp(str, TOKEN_GREATER) == 0)
        return BIN_GREATER;
    else if (strcmp(str, TOKEN_LOWER) == 0)
        return BIN_LOWER;
    else if (strcmp(str, TOKEN_GREATER_OR_EQUAL) == 0)
        return BIN_GREATER_OR_EQUAL;
    else if (strcmp(str, TOKEN_LOWER_OR_EQUAL) == 0)
        return BIN_LOWER_OR_EQUAL;
    else if (strcmp(str, TOKEN_BITWISE_AND) == 0)
        return BIN_BITWISE_AND;
    else if (strcmp(str, TOKEN_BITWISE_OR) == 0)
        return BIN_BITWISE_OR;
    else if (strcmp(str, TOKEN_BITWISE_XOR) == 0)
        return BIN_BITWISE_XOR;
    else if (strcmp(str, TOKEN_BITWISE_NOT) == 0)
        return BIN_BITWISE_NOT;
    else if (strcmp(str, TOKEN_LEFT_SHIFT) == 0)
        return BIN_LEFT_SHIFT;
    else if (strcmp(str, TOKEN_RIGHT_SHIFT) == 0)
        return BIN_RIGHT_SHIFT;
    else if (strcmp(str, TOKEN_EOP) == 0)
        return BIN_EOP;
    else if (strcmp(str, TOKEN_TYPEOF) == 0)
        return BIN_TYPEOF;
    else if (strcmp(str, TOKEN_MOD) == 0)
        return BIN_MOD;
    else if (strcmp(str, TOKEN_SIZEOF) == 0)
        return BIN_SIZEOF;
    else if (strcmp(str, TOKEN_VLOAD) == 0)
        return BIN_VLOAD;
    else if (strcmp(str, TOKEN_VSTORE) == 0)
        return BIN_VSTORE;
    else if (strcmp(str, TOKEN_INPUT) == 0)
        return BIN_INPUT;
    else if (strcmp(str, TOKEN_CALL) == 0)
        return BIN_CALL;
    return BIN_EOP;
}