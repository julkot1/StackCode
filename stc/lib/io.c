#include "Header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MODE_R 0x0
#define MODE_W 0x1
#define MODE_E 0x2

struct stc_stream
{
    int in_fd;
    int out_fd;
    STC_I64_TYPE mode;
};

struct stc_stream current_stream;

void lib_init init_io()
{
    current_stream = {1,1, R|W};

}
stc_value print_I64(stc_value v) {
    printf("%lld\n", (long long)v.val);
    return v;
}
stc_value print_F64(stc_value v) {
    double d = I64_TO_F64(v.val);
    printf("%f\n", d);
    return v;
}
stc_value print_BOOL(stc_value v) {
    printf("%s\n", v.val ? "true" : "false");
    return v;
}
stc_value print_I8(stc_value v) {
    printf("%d\n", (int8_t)v.val);
    return v;
}
stc_value print_STRING(stc_value v) {
    printf("%s\n", (const char *)(uintptr_t)v.val);
    return v;
}
stc_value print_UNKNOWN(stc_value v) {
    printf("<unknown>\n");
    return v;
}

// Scan functions for each type
stc_value scan_I64() {
    stc_value v;
    v.type = STC_I64_TYPE;
    scanf("%lld", (long long *)&v.val);
    return v;
}
stc_value scan_F64() {
    stc_value v;
    v.type = STC_F64_TYPE;
    double d;
    scanf("%lf", &d);
    v.val = F64_TO_I64(d);
    return v;
}
stc_value scan_BOOL() {
    stc_value v;
    v.type = STC_BOOL_TYPE;
    int b;
    scanf("%d", &b);
    v.val = b ? 1 : 0;
    return v;
}
stc_value scan_I8() {
    stc_value v;
    v.type = STC_I8_TYPE;
    int i;
    scanf("%d", &i);
    v.val = (int8_t)i;
    return v;
}
stc_value scan_STRING() {
    stc_value v;
    v.type = STC_STRING_TYPE;
    char buf[256];
    scanf("%255s", buf);
    v.val = (uintptr_t)strdup(buf);
    return v;
}
stc_value scan_UNKNOWN() {
    stc_value v;
    v.type = 0xFF;
    v.val = 0;
    return v;
}

void token("print") print(stc_value v) {
    if (v.type == STC_I64_TYPE)
        print_I64(v);
    else if (v.type == STC_F64_TYPE)
        print_F64(v);
    else if (v.type == STC_BOOL_TYPE)
        print_BOOL(v);
    else if (v.type == STC_I8_TYPE)
        print_I8(v);
    else if (v.type == STC_STRING_TYPE)
        print_STRING(v);
    else
        print_UNKNOWN(v);
}

stc_value token("scan") scan(stc_value value) {
    stc_type type = value.type;
    if (type == STC_I64_TYPE)
        return scan_I64();
    else if (type == STC_F64_TYPE)
        return scan_F64();
    else if (type == STC_BOOL_TYPE)
        return scan_BOOL();
    else if (type == STC_I8_TYPE)
        return scan_I8();
    else if (type == STC_STRING_TYPE)
        return scan_STRING();
    else
        return scan_UNKNOWN();
}
