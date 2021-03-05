/*
 * Date: Jan 16, 2021 
 * Lab Purpose: To calculate the total charge and money saved with the two inputs. 
 * Name: Derek Chen
 * Student #: 1006751267
 * */
 
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{   
    double pricePerPound,totalWeight,totalChargeBefore,moneySaved,totalChargeAfter; //initialize variables
	
    printf("Enter the price per pound: "); // prompt required string
    scanf("%lf",&pricePerPound); // ask for user input
    
    printf("Enter the total weight: ");
    scanf("%lf",&totalWeight);
    
    // calculations:
    totalChargeBefore = pricePerPound * totalWeight; 
    // totalChargeBefore - fmod(totalChargeBefore, 3.0) returns the integer multiple of 3 dollars,
    // 30 is the result of /10 (10 cents) / 3(per 3 dollars)
    moneySaved = (totalChargeBefore - fmod(totalChargeBefore, 3.0)) / 30; 
    totalChargeAfter = totalChargeBefore - moneySaved; 
    
    // print results:
    printf("The total charge is: %.2lf\n",totalChargeAfter);
    printf("You saved: %.2lf\n",moneySaved);
    
    return 0;
}