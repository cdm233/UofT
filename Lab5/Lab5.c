/*
 * Date: Feb. 9, 2021 
 * Lab Purpose: This program draws a Pascal’s Triangle with the use of functions
 * Name: Derek Chen
 * Student #: 1006751267
 * */
#include <stdio.h>

// prototyping functions
int choose(int, int);
void printSpace(int);
int mag(int);
void printSpace(int);

// define the function triangle, which is used to construct the Pascal's Triangle
void triangle(int rows){
    //initialize variables
    int indexRow, indexCol, spaces;
    int number;
    
    printf("");

    for(indexRow = 0; indexRow < rows; indexRow++){
        indexCol = 0;
        
        // for loop used to prints spaces before the first number of the rows
        for(spaces = 0; spaces < (rows - indexRow - 1); spaces++){
            printf("   ");
        }
        
        /*
            prints the number and spaces after each number

            the number of spaces to be printed after each number
            depends on how many digits it has
        */
        for(indexCol = 0; indexCol <= indexRow; indexCol++){
            number = choose(indexRow, indexRow - indexCol);
            printf("%d",number);
            printSpace(6 - mag(number));
        }
        // end of the row, starts new row
        printf("\n");
    }
}

// define the function choose 
int choose(int n, int r){
    int result = factorial(n) / (factorial(r) * factorial(n-r));
    return result;
}

// define the function factorial
int factorial(int n){
    int i, result = 1;
    
    for(i = 1; i <= n; i++){
        result *= i;
    }
    
    return result;
}

// define printSpace 
// which will depend on how many digit the precious number has
void printSpace(int space){
    int i;
    for(i = 0;i < space; i ++){
        printf(" ");
    }
}

// define the function mag, which calculates the magnitude of the number
int mag(int number){
    int result = 0;
    
    while(number > 0){
        number /= 10;
        result ++;
    }
    
    return result;
}

int main(int argc, char **argv)
{
    int rows = 1;
    
    while(0 <= rows && rows <= 13){
        // prompt the user for input
        printf("Enter the number of rows: ");
        scanf("%d",&rows);
    
        // the range of the triangle is from 0 to 13 inclusive
        if(0 <= rows && rows <= 13){
            triangle(rows);
        }
    }
	return 0;
}