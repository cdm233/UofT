#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


int main(void)
{
    int sieve[100] = {0}, i, p = 2;
    while (p < sqrt(100))
    {
        printf("%d ", p);
        // eliminate multiples of p
        i = 2;
        while (i * p < 100)
        {
            sieve[i * p] = 1;
            i ++;
        }
        p++;
        while (sieve[p] == 1)
            p++;
    }
    for (; p < 100; p++)
        if (sieve[p] == 0)
            printf("%d ", p);

    printf("\n");
}