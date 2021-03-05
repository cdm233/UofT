/*
 * Date: Feb. 3, 2021 
 * Lab Purpose: This program draws a triangle with *
 * Name: Derek Chen
 * Student #: 1006751267
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int rows, indexRow, indexColumn;
    printf("Enter the number of rows in the triangle: ");
    scanf("%d",&rows);
    
    // this for loop only prints the first n - 1 rows
    for(indexRow = 1; indexRow <= rows - 1; indexRow++){ 
        
        // if it's the first row, then only need to print one *
        if(indexRow == 1){
            
            // printf spaces before *
            for(indexColumn = 1; indexColumn < rows; indexColumn ++){
                printf(" ");
            }
            printf("*"); // prints the first *
        }else{ // this is the middle part
            
            // prints spaces before the first *
            for(indexColumn = 1; indexColumn <= rows - indexRow; indexColumn ++){
                printf(" ");
            }
            printf("*");
            
            // prints spaces after the first *
            for(indexColumn = 1; indexColumn <= (2*(indexRow-1) - 1); indexColumn ++){
                printf(" ");
            }
            printf("*");
        }
        printf("\n");
    }
    
    // last row, prints all *
    
    for(indexRow = 0; indexRow < rows * 2 - 1; indexRow++){
        printf("*");
    }
    printf("\n");
    return 0;
}
