/*
    Date: March 4, 2021
    Name: Derek Chen
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

void test(int a[3]){
    a[2] = 1;
}

int main(){
    int a[3] = {1,2,3};
    test(a);

    printf("%d%d%d",a[0],a[1],a[2]);
    
    // char move[3]; 
    // int n;

    // printf("a");
    // scanf("%d\n",&n);

    // scanf("%c %c %c", &move[0], &move[1], &move[2]);
    // printf("%c %c %c", move[0], move[1], move[2]);
}