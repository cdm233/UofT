#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int recursiveAdd(int num) {
    if(num == 1){
        return 1;
    }
    return num + recursiveAdd(num - 1);
}

int fib(int n) {    
    // fill in the function
    if (n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int countDigits(int num) {
   if(num < 10 ){
        return 1;
   }
   return 1 + countDigits(num / 10);
}

int main(){
    // int r = recursiveAdd(6);
    int f = fib(7);
    return 0;
}