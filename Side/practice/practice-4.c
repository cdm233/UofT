#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int countSpaces(char *s) {
    // fill in the function to return the number
    // of spaces in the supplied string
    int num = 0;
    for(int i = 0; s[i] != '\0';i++){
        if(s[i] == ' '){
            num ++;
        }
    }
    return num;
}

int main(){
    countSpaces("hellow world");
    return 0;
}