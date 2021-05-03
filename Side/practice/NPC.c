#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int getCheckDigit(long code) {
    // fill in the function to return the 12th digit of the
    // provided UPC code

    int oddSum = 0, evenSum = 0;
    for(int i = 0; i < 11; i++){
        oddSum += code % 10;
        code /= 10;

        evenSum += code % 10;
        code /= 10;
    }
    int result = (oddSum * 3 + evenSum)%10;
    if(result != 0){
        return 10 - result;
    }else{
        return 0;
    }
}

int main(){
    long num = 36000291452;
    getCheckDigit(num);
    return 0;
}