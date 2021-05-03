#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(){
    const char sample[] = "This is a sample string";
    printf("Looking for character 's' in \"This is a sample string\"...");

    printf("\n");

    char *p = strchr(sample, 's');
    while(p != NULL){
        printf("Found at %d\n", p - sample + 1);
        p = strchr(p + 1, 's');
    }
    return 0;
}