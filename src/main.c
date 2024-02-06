#include <stdio.h>
#include "../include/bc_parser.h"
#include "../include/loader.h"


int main()
{
    FILE  *in = fopen("app.bc", "r");
    FILE  *out= fopen("app.bin", "wb");
    parse_bin(in,out);
    fclose(in);
    fclose(out);

    FILE  *bin= fopen("app.bin", "rb");
    load(bin);
    fclose(bin);

    return 0;
}
