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
    int deltaRow = -1;
    int n = 2;
    for(int i = 0; i < n && i > -1; i += deltaRow){
        printf("?");
    }
}