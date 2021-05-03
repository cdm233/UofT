#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// int main(){
//     int number = 0;
//     int largest = -1;
//     printf("Enter an integer: ");
//     scanf("%d", &number);

//     if(number < 0){
//         number = -number;
//     }

//     while(number != 0){
//         if((number % 10) % 4 == 0 && number % 10 != 0){
//             if((number % 10) > largest){
//                 largest = number % 10;
//             }
//         }
//         number /= 10;
//     }
//     printf("\n");
//     if(largest == -1){
//         printf("No match found!");
//     }else if(largest == 2){
//         printf("TWO is the largest Digit!");
//     }else{
//         printf("EIGHT is the largest Digit!");
//     }
//     return 0;
// }

// void printNChar(int numC, char c)
// {
// 	for (int i = 1; i <= numC; i++){
// 		printf("%c", c);
// 	}
// }

// int main(){
// 	int num = 2;
// 	printf("Enter an integer value (num): ");
// 	scanf("%d",&num);
// 	printNChar(num, '@');
//     printf("\n");
// 	for(int i = 0; i < num - 2; i++){
// 		for(int j = 0; j < num; j ++){
// 			if(j == 0){
// 				printf("@");
// 			}else if(j == i + 1){
// 				printf("@");
// 			}else if(j == num - 1){
// 				printf("@");
// 			}else{
// 				printf(" ");
// 			}
// 		}
// 		printf("\n");
// 	}
// 	printNChar(num, '@');
// }

// not finished:::

// char *acronymMaker(char *inString){
//     //"the Faculty of Applied Science and Engineering"
//     int count = 0, pre = 0;
//     int size = 0;

//     while(true){
//         printf("first");
//         char word[200];
//         if(inString[count] == ' '){
//             strncpy(word, inString + count, pre);
//             printf("%s\n", word);
//         }
//         count ++;
//         pre -= count;
//         // printf("%c", inString[count]);
//         if(inString[count] == '\0'){
//             strncpy(word, inString, count);
//             break;
//         }
//     }

// }

void removeAll(char * str, const char toRemove, int index)
{
    int i;

    while(str[index] != '\0')
    {
        /* If duplicate character is found */
        if(str[index] == toRemove)
        {
            /* Shift all characters from current position to one place left */
            i = index;
            while(str[i] != '\0')
            {
                str[i] = str[i + 1];
                i++;
            }
        }
        else
        {
            index++;
        }
    }
}

//prototype for the function
void bubbleSortChar(char list[]){
//here is where to put your code
    char string[100] = {};
    char temp;

    int count = 0, newC = 0;
    while(list[count] != '\0'){
        if(list[count] != ' '){
            string[newC] = list[count];
            newC ++;
        }
        count++;
    }

    string[newC] = '\0';

    int n = newC;

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (string[i] > string[j]) {
                temp = string[i];
                string[i] = string[j];
                string[j] = temp;
            }
        }
    }
    int i = 0;

    while(string[i] != '\0')
    {
        /* Remove all duplicate of character string[i] */
        removeAll(string, string[i], i + 1);
        i++;
    }

    printf("result=%s", string);
}

int main(){
    char *aa = "the Faculty of Applied Science and Engineering";
    // acronymMaker(aa);
    bubbleSortChar("Toronto is my city");
    // printf("%s",ar);
    return 0;
}