/*
 * Date: Jan 16, 2021 
 * Lab Purpose: To calculate the future value of the principal with the four inputs. 
 * Name: Derek Chen
 * Student #: 1006751267
 * */
 
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    double principal,annualInterestRate,timesPerYear,numberOfYears,futureValue;
    
    printf("The amount deposited P: "); // prompt required string
    scanf("%lf",&principal); // ask for user input
    
    printf("The interest rate r: ");
    scanf("%lf",&annualInterestRate);
    
    printf("The number of times the interest is compounded n: ");
    scanf("%lf",&timesPerYear);
    
    printf("The period of time t the money is invested (in years): ");
    scanf("%lf",&numberOfYears);

    // calculations:
    // it follows the formula: P(1+r/n)^(nt)
    futureValue = principal * pow((1 + annualInterestRate / timesPerYear),timesPerYear * numberOfYears); 
    
    // print results:
    printf("The future value of the investment A: %.2lf\n", futureValue);
    
    return 0;
}