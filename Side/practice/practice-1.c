#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int matrix1Row, matrix1Col;
    
    printf("Enter number of rows: ");
    scanf("%d", &matrix1Row);
    printf("Enter number of columns: ");
    scanf("%d", &matrix1Col);

    int matrix1[matrix1Row][matrix1Col];
    int matrix2[matrix1Row][matrix1Col];

    printf("\nEnter elements of matrix A:\n");

    for(int i = 0; i < matrix1Row; i++){
        printf("Enter elements of row%d: ", i+1);
        for(int j = 0; j < matrix1Col; j++){
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("\nEnter elements of matrix B:\n");

    for(int i = 0; i < matrix1Row; i++){
        printf("Enter elements of row%d: ", i+1);
        for(int j = 0; j < matrix1Col; j++){
            scanf("%d", &matrix2[i][j]);
        }
    }
    int sum[matrix1Row][matrix1Col];
    for(int i = 0; i < matrix1Row; i++){
        for(int j = 0; j < matrix1Col; j++){
            sum[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    printf("\nSum of A and B is: \n");
    for(int i = 0; i < matrix1Row; i++){
        for(int j = 0; j < matrix1Col; j++){
            printf("%d", sum[i][j]);
            if((j+1) != matrix1Col){
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}