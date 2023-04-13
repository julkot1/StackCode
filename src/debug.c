#include "include/bc_parser.h"
#include "include/main.h"
#include "include/vm.h"
#include "include/debug.h"

char *type_str(type t)
{
    if (BOOL == t)
        return TOKEN_TYPE_BOOL;
    else if (NUMBER == t)
        return TOKEN_TYPE_NUMBER;
    else if (STRING == t)
        return TOKEN_TYPE_STRING;
    else if (CHAR == t)
        return TOKEN_TYPE_CHAR;
    else if (PTR == t)
        return TOKEN_TYPE_PTR;
    else if (ARRAY == t)
        return TOKEN_TYPE_ARRAY;
    return TOKEN_TYPE_TYPE;
}
char *op_str(opcode op)
{
    if (BIN_PUSH == op)
        return TOKEN_PUSH;
    else if (BIN_ADD == op)
        return TOKEN_ADD;
    else if (BIN_SUB == op)
        return TOKEN_SUB;
    else if (BIN_DIV == op)
        return TOKEN_DIV;
    else if (BIN_MUL == op)
        return TOKEN_MUL;
    else if (BIN_DUMP == op)
        return TOKEN_DUMP;
    else if (BIN_POP == op)
        return TOKEN_POP;
    else if (BIN_DUP == op)
        return TOKEN_DUP;
    else if (BIN_SWAP == op)
        return TOKEN_SWAP;
    else if (BIN_JMP == op)
        return TOKEN_JMP;
    else if (BIN_JMP_IF == op)
        return TOKEN_JMP_IF;
    else if (BIN_JMP_IF_NOT == op)
        return TOKEN_JMP_IF_NOT;
    else if (BIN_LABEL == op)
        return TOKEN_LABEL;
    else if (BIN_EQUAL == op)
        return TOKEN_EQUAL;
    else if (BIN_NOT == op)
        return TOKEN_NOT;
    else if (BIN_NOT_EQUAL == op)
        return TOKEN_NOT_EQUAL;
    else if (BIN_OR == op)
        return TOKEN_OR;
    else if (BIN_AND == op)
        return TOKEN_AND;
    else if (BIN_GREATER == op)
        return TOKEN_GREATER;
    else if (BIN_LOWER == op)
        return TOKEN_LOWER;
    else if (BIN_GREATER_OR_EQUAL == op)
        return TOKEN_GREATER_OR_EQUAL;
    else if (BIN_LOWER_OR_EQUAL == op)
        return TOKEN_LOWER_OR_EQUAL;
    else if (BIN_BITWISE_AND == op)
        return TOKEN_BITWISE_AND;
    else if (BIN_BITWISE_OR == op)
        return TOKEN_BITWISE_OR;
    else if (BIN_BITWISE_XOR == op)
        return TOKEN_BITWISE_XOR;
    else if (BIN_BITWISE_NOT == op)
        return TOKEN_BITWISE_NOT;
    else if (BIN_LEFT_SHIFT == op)
        return TOKEN_LEFT_SHIFT;
    else if (BIN_RIGHT_SHIFT == op)
        return TOKEN_RIGHT_SHIFT;
    else if (BIN_EOP == op)
        return TOKEN_EOP;
    else if (BIN_TYPEOF == op)
        return TOKEN_TYPEOF;
    else if (BIN_MOD == op)
        return TOKEN_MOD;
    else if (BIN_SIZEOF == op)
        return TOKEN_SIZEOF;
    else if (BIN_VLOAD == op)
        return TOKEN_VLOAD;
    else if (BIN_VSTORE == op)
        return TOKEN_VSTORE;
    else if (BIN_INPUT == op)
        return TOKEN_INPUT;
    else if (BIN_CALL == op)
        return TOKEN_CALL;
    else if (BIN_ARR_APPEND == op)
        return TOKEN_ARR_APPEND;
    else if (BIN_ARR_NEW_STACK == op)
        return TOKEN_ARR_NEW_STACK;
    else if (BIN_ARR_STORE == op)
        return TOKEN_ARR_STORE;
    else if (BIN_ARR_LOAD == op)
        return TOKEN_ARR_LOAD;
    return TOKEN_EOP;
}
void print_value(payload_value val, type t)
{
    printf("(%s) ", type_str(t));
    if (BOOL == t)
        printf("%s", val.number ? "true" : "false");
    else if (NUMBER == t)
        printf("%d", val.number);
    else if (STRING == t)
        printf("%s", val.ptr);
    else if (CHAR == t)
        printf("%c", val.byte);
    else if (TYPE == t)
        printf("%s", type_str(val.all));
}
void print_payload_ptr(operation op)
{
    if (op.code == BIN_VLOAD || op.code == BIN_VSTORE)
    {
        pool_element el = __p->var_pool.elements[op.payload.all];
        printf("var_pool[%d] = ", op.payload.all);
        print_value(el.static_val, el.type);
    }
    else if (op.code == BIN_PUSH)
    {
        pool_element *el = op.payload.ptr;
        if (el->type == STRING)
        {
            printf("(%s) \"%s\"", type_str(STRING), (char *)el->val);
        }
    }
}

void print_payload(operation op)
{
    if (PTR == op.payload_type)
        print_payload_ptr(op);
    else
        print_value(op.payload, op.payload_type);
}
void print_token(operation op)
{
    printf("token: %s ", op_str(op.code));
    if (is_payload_operation(op.code))
        print_payload(op);
    printf("\n");
}
void debug_token(operation op, context *ctx)
{
    print_token(op);
    while (1)
    {
        char code[100];
        printf(">>");
        fgets(code, sizeof(code), stdin);
        if (code[0] == '\n')
            return;
        char *cmd;
        cmd = strtok(code, " \n");
        if (strcmp(cmd, DEBUG_NEXT_TOKEN) == 0)
            return;
        if (strcmp(cmd, DEBUG_LIST_STACK_TOKEN) == 0)
            debug_list_stack();
        else if (strcmp(cmd, DEBUG_CTX_TOKEN) == 0)
            debug_ctx(ctx);
        else if (strcmp(cmd, DEBUG_LIST_TOKENS_TOKEN) == 0)
            debug_list_tokens(ctx->fn);
        else if (strcmp(cmd, DEBUG_QUIT_TOKEN) == 0)
            exit(EXIT_SUCCESS);
        else if (strcmp(cmd, DEBUG_HELP_TOKEN) == 0)
            print_help();
        else if (strcmp(cmd, DEBUG_PRINT_VAR_TOKEN) == 0)
        {
            cmd = strtok(NULL, " \n");
            debug_print_var(atoi(cmd));
        }
    }
}
void print_stack_element(struct stack_element el)
{

    if (el.t == PTR)
    {
        pool_element *pel = el.val.ptr;

        if (pel->type == STRING)
        {
            printf("(%s) \"%s\" (ref: %d addr: %p)", type_str(STRING), (char *)pel->val, pel->ref_counter, pel->val);
        }

        if (pel->type == ARRAY)
        {
            array *arr = pel->val;
            printf("(%s length: %zu, capacity: %zu): [", type_str(ARRAY), arr->length, arr->capacity);
            for (size_t i = 0; i < arr->length; i++)
            {
                print_stack_element(arr->elements[i]);
                if (i != arr->length - 1)
                    printf(", ");
            }

            printf("] (ref: %d addr: %p)", pel->ref_counter, pel->val);
        }
        return;
    }
    print_value(el.val, el.t);
}
void print_element_from_stack(int id)
{
    struct stack_element el = __p->stack[id];
    printf("%d: ", __p->ptr - id - 1);
    print_stack_element(el);
}

void debug_list_stack()
{
    int size = __p->ptr;
    printf("stack ptr: %d\n", size);
    for (size_t i = size; i != 0; i--)
    {
        print_element_from_stack(i - 1);
        if (i != 1)
            printf(" | ");
    }
    printf("\n");
}
void debug_list_tokens(function *fn)
{
    for (size_t i = 0; i < fn->code_size; i++)
    {
        print_token(fn->code[i]);
    }
}
void debug_ctx(context *ctx)
{
    char *fn_name = __p->meta.function_names[ctx->fn->id];
    printf("function: %s\n", fn_name);
    printf("state: %d\n", ctx->state);
    if (ctx->parent != NULL)
    {
        fn_name = __p->meta.function_names[ctx->parent->fn->id];
        printf("parent function: %s\n", fn_name);
    }
}
void debug_print_var(int id)
{
    printf("id: %d ", id);
    pool_element el = __p->var_pool.elements[id];
    if (el.type == PTR)
    {

        pool_element *pel = el.val;
        if (pel->type == STRING)
        {
            printf("(%s) \"%s\" (ref: %d addr: %p)", type_str(STRING), (char *)pel->val, pel->ref_counter, pel->val);
        }

        if (pel->type == ARRAY)
        {
            array *arr = pel->val;
            printf("(%s length: %zu, capacity: %zu): [", type_str(ARRAY), arr->length, arr->capacity);
            for (size_t i = 0; i < arr->length; i++)
            {
                print_stack_element(arr->elements[i]);
                if (i != arr->length - 1)
                    printf(", ");
            }

            printf("] (ref: %d addr: %p)\n", pel->ref_counter, pel->val);
        }
        return;
    }
    else if (el.static_element)
    {
        print_value(el.static_val, el.type);
    }
    printf("\n");
}

void print_help()
{
    printf("help:\n");
    printf("next - next state\n");
    printf("stack - print stack\n");
    printf("tokens - list tokens of current function\n");
    printf("ctx - print current context\n");
    printf("var [id] - print var with [id]\n");
    printf("help - print help");
    printf("quit - exit program\n");
}
