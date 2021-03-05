/*
 * Date: Feb 2, 2021 
 * Lab Purpose: This program returns the coin composition with the least amount of coins of a given value
 * Name: Derek Chen
 * Student #: 1006751267
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// this function will be used multiple times
int multipleOf(value,type){
    int result;
    
    // this calculates the integer multiple of the result with the indicated type of coin
    result = (value - value % type) / type; 
    
    return result;
}

// main function
int main(int argc, char **argv)
{
    // initializing variables and constants
    int validUserInput = 1;
    int const nickel = 5, dime = 10, quarter = 25;
    
    // main loop for user input
    while(validUserInput == 1){ // while loop used to ensure user input 0 or 1
    	// initialize variables
        int value, currentValue;

        // prompt to ask user input
        printf("Please give an amount in cents less than 100: ");
        scanf("%d", &value);
        
        // check if the user input is valid, if not then end program
        validUserInput = 0 < value && value < 100 ? 1 : 0; 
        if(validUserInput == 0){
            printf("Goodbye\n");
            return 0;
        }
        
        // if the uer input is 1, directly print the result
        if(value > 1){
            printf("%d cents: ", value);
            
            // the logic is the calculate how much value the 'largest' coins can represent
            // then move to the second largest coin and so on
            int quarterAmount = multipleOf(value, quarter);
            currentValue = value - quarterAmount * quarter;
            
            // if the quantity of this type of coin is greater than 1,add a 's' 
            if(quarterAmount != 0){
                if(quarterAmount > 1){
                    printf("%d quarters", quarterAmount);
                }else{
                    printf("%d quarter", quarterAmount);
                }
                
                // if the value can be represented with this type of coin only
                // then end program and print period, else continue and print comma
                if(currentValue != 0){
                    printf(", ");
                }else{
                    printf(".\n");
                    continue;
                }
            }
            
            // same logic as before 
            int dimeAmount = multipleOf(currentValue, dime);
            currentValue -= dimeAmount * dime;
            
            if(dimeAmount != 0){
                if(dimeAmount > 1){
                    printf("%d dimes", dimeAmount);
                }else{
                    printf("%d dime", dimeAmount);
                }
                
                if(currentValue != 0){
                    printf(", ");
                }else{
                    printf(".\n");
                    continue;
                }
            }
            
            int nickelAmount = multipleOf(currentValue, nickel);
            currentValue -= nickelAmount * nickel;
            
            if(nickelAmount != 0){
                if(nickelAmount > 1){
                    printf("%d nickels", nickelAmount);
                }else{
                    printf("%d nickel", nickelAmount);
                }
                
                if(currentValue != 0){
                    printf(", ");
                }else{
                    printf(".\n");
                    continue;
                }
            }
            
            // end of the process
            int centAmount = currentValue;
            currentValue = 0;
            
            if(centAmount != 0){
                if(centAmount > 1){
                    printf("%d cents", centAmount);
                }else{
                    printf("%d cent", centAmount);
                }
                
                if(currentValue != 0){
                    printf(", ");
                }else{
                    printf(".\n");
                    continue;
                }
            }
        }else{ // if the value is only 1, print 1 cent instead of 1 cents
            printf("1 cent: 1 cent.\n");
        }
    }
    return 0;
}