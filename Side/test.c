#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int c(char *str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

char recFindIndex(char *str, char c, int index){
    if(str[index] == '\0'){
        return -1;
    }
    if(str[index] == c){
        return index;
    }
    return recFindIndex(str, c, index + 1);
}

// int main(){
//     double e = 2.718281828459045;
//     int ee = e;

//     int ind = recFindIndex("hellow world", 'w', 0);

//     printf("%d\n",ind);
//     // printf("%d\n",c(str));
//     // printf("%d",strlen(str));
//     return 0;
// }

void func(int *p, int *q) {
    int *t;
    t = p;
    *p = *q;
    *q = *t;
}

int main(void) {
    int i = 0, j = 1;
    int *p, *q;
    p = &i;
    q = &j;
    func(p, q);
    printf("%d, %d.\n", *p, *q);
    return 0;
}