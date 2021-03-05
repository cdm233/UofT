/*
 * Date: Jan 16, 2021 
 * Lab Purpose: To calculate the total charge rounded to the nearest nickel with the one input. 
 * Name: Derek Chen
 * Student #: 1006751267
 * */
 
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{   
    double price, totalCharge;
    
    printf("Enter the price as a float with two decimals: "); // prompt required string
    scanf("%lf",&price); // ask for user input

    // conversion: 
    // totalCharge = floor(20*(price + 0.02))/20; //2.93 => 2.95 => 5.9
    
    totalCharge = round(20*price)/20;
    
    // print the result:
    printf("The total charge is: %.2lf\n",totalCharge);
    
    return 0;
}