#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// add recursively
int recursiveAdd(int num) {
    if(num == 1){
        return 1;
    }
    return num + recursiveAdd(num - 1);
}

// find fibonacci series recursively
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

// counts digits recursively
int countDigits(int num) {
   if(num < 10 ){
        return 1;
   }
   return 1 + countDigits(num / 10);
}

// factorial recursively
int fac(int n){
    if(n == 1){
        return 1;
    }
    return n * fac(n - 1);
}

// recursive selection sort 
int minIndex(int arr[], int start, int end){
    int sml = INT_MAX;
    int index;
    for (int i = start; i < end; i++) { //{26,15,5,2,7,9,2,65,12,64,23,54,36,96,123};
        if (arr[i] < sml) {
            sml = arr[i];
            index = i;
        }
    }
    return index;
}

void recSelSort(int arr[], int start_index, int end_index){
    if (start_index >= end_index)
        return;
    int min_index;
    int temp;
 
    min_index = minIndex(arr, start_index, end_index);
 
    temp = arr[start_index];
    arr[start_index] = arr[min_index];
    arr[min_index] = temp;
 
    recSelSort(arr, start_index + 1, end_index);
}

// rec prints multiple of n then prints it back ward
void fun2(int n){
    if (n <= 0){
        return;
    }
    if (n > 1000){
        return;
    }
    printf("%d ", n);
    fun2(2*n);
    printf("%d ", n);
}  

// recursive find largest
int findLargest(int a[],int n)
{
    int x;
    if(n == 1){
        return a[0];
    }
    else{
        x = findLargest(a, n-1);
    }
    if(x > a[n-1]){
        return x;
    }else{
        return a[n-1];
    }
}

// recursive product, returns a*b
int recProduct(int a, int b){
    if (b == 0)   return 0;
    return (a + recProduct(a, b-1));
}

// recursive power, returns a^b
int recpower(int a, int b){
    if (b == 0){
        return 1;
    }
    if (b % 2 == 0){
        return recpower(a*a, b/2);
    }
    return recpower(a*a, b/2) * a;
}

int main(){
    // int re = fac(10);
    // printf("%d", re);

    int arrary[] = {26,15,5,2,7,9,2,65,12,64,23,54,36,96,123};


    int size = sizeof(arrary)/sizeof(int);
    // fun2(100);
    printf("%d",recProduct(3,6));
    // int mini = minIndex(arrary, 0, size);
    // printf("%d",mini);
    // recSelSort(arrary, 0, size);
    // int count = 0;
    // while(count < size){
    //     printf("%d ", arrary[count]);
    //     count++;
    // }
}