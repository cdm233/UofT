#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int size;
    printf("Enter the array size: ");
    scanf("%d", &size);

    printf("\n");

    double largest = 0.0;

    for(int i = 0; i < size; i++){
        double temp;
        printf("Enter Number %d: ", i + 1);
        scanf(" %lf", &temp);
        if(temp > largest){
            largest = temp;
        }
    }
    printf("\n");
    
    printf("Largest = %.2lf", largest);

    return 0;
}