#include <stdio.h>

int main()
{
    int max = 50000000;
    for (int i = 1; i < max; i++)
    {
        if (max % i == 0)
        {
            printf("%d\n", i);
        }
    }
}