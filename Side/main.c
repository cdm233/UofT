/*
    Date: March 4, 2021
    Name: Derek Chen
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <GL/gl.h>

int main(int argc, char *argv[]){
    char pixel = '*';
    int num = 0;
    while(1){
        num++;
        system("cls");
        printf("%d \n", num);
        sleep(1/20);
    }
    return 0;
}