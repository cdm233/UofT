void removeAll(char * str, const char toRemove, int index)
{
    int i;

    while(str[index] != '\0'){
        /* If duplicate character is found */
        if(str[index] == toRemove){
            /* Shift all characters from current position to one place left */
            i = index;
            while(str[i] != '\0'){
                str[i] = str[i + 1];
                i++;
            }
        }
        else{
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

    printf("Result=%s", string);
}