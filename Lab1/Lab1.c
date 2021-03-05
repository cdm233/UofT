/*
 * Date: Jan 14, 2021 
 * Lab Purpose: To calculate the sum, twice their product, and average with the three inputs. 
 * Name: Derek Chen
 * Student #: 1006751267
 * */

#include <stdio.h>
int main(int argc, char **argv)
{
    double inputNumber1,inputNumber2,inputNumber3,sum,halfSum,twiceProduct,average; //initialize variables
    
    printf("Enter First Number: "); // prompt required string
	scanf("%lf", &inputNumber1); // record user input
    
    printf("Enter Second Number: ");
    scanf("%lf", &inputNumber2);
    
    printf("Enter Third Number: ");
    scanf("%lf", &inputNumber3);
    
    // calculations:
    sum = (inputNumber1 + inputNumber2 + inputNumber3); // since sum is being used twice, i will calculate the sum of the three numbers in advance
    halfSum = sum / 2; 
    average = sum / 3; 
    twiceProduct = (inputNumber1 * inputNumber2 * inputNumber3) * 2; 
    
    // print results:
    printf("Half the sum: %.2lf\n", halfSum);
    printf("Twice the product: %.2lf\n", twiceProduct);
    printf("Average: %.2lf\n", average);
    
	return 0;
}
