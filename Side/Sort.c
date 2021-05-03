#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void printArr(int arrary[], int length){
    int count = 0;
    while(count < length){
        printf("%d ", arrary[count]);
        count++;
    }
    printf("\n");
}

// inserstion sort
void insertion_sort(int arrary[], int length){
    int top, item, i;
    for(top = 1; top < length; top++){
        item = arrary[top];
        i = top - 1;
        while(i >= 0 && arrary[i] > item){
            arrary[i + 1] = arrary[i];
            i--;
        }
        if(i != top - 1){
            arrary[i + 1] = item;
        }
    }
}

// basic selection sort
void selection_sort(int arrary[], int length){ //{26,15,5,2,7,9,2,65,12,64,23,54,36,96,123};
    int top, largeLoc, i, temp;
    for(top = length - 1; top > 0; top--){
        largeLoc = 0;
        // printArr(arrary, length);
        for(i = 1; i <= top; i++){
            if(arrary[i] > arrary[largeLoc]){
                largeLoc = i;
            }
            temp = arrary[top];
            arrary[top] = arrary[largeLoc];
            arrary[largeLoc] = temp;
        }
    }
}

// basic sort (bubble sort)
void sort(int arrary[], int length){
    for(int i = 0; i < length; i++){
        for(int j = i + 1; j < length; j++){
            if(arrary[j] < arrary[i]){
                int temp = arrary[i];
                arrary[i] = arrary[j];
                arrary[j] = temp;
            }
        }
    }
}

void printList(int arrary[], int size){
    int count = 0;
    while(count < size){
        printf("%d ", arrary[count]);
        count++;
    }
    printf("\n");
}

// quick sort
void quick_sort(int arrary[], int low, int high){
    if(low < high){
        int left = low;
        int right = high;
        int pivot = arrary[low];
        int n = 0;
        while(left < right){
            n++;
            printList(arrary, high - low + 1);
            while(arrary[right] >= pivot && left < right){
                right --;
            }
            printf("right: %d ", right);
            arrary[left] = arrary[right];
            while (arrary[left] <= pivot && left < right){
                left ++;
            }
            printf("left: %d\n", left);
            arrary[right] = arrary[left];
        }
        arrary[left] = pivot;
        printf("looped %d times\n", n);
        printList(arrary, high - low + 1);

        quick_sort(arrary, low, left - 1);
        quick_sort(arrary, right + 1, high);
    }
    return;
}

int main(){
    // int arrary[] = {26,15,5,2,7,9,2,65,12,64,23,54,36,96,123};
    int size = 1000;
    int arrary[size];

    srand(time(NULL));
    for(int i = 0; i < size; i++){
        arrary[i] = rand()%size;
    }
    // sort(arrary, size);
    // selection_sort(arrary, size);
    // sort(arrary, size);

    clock_t begin = clock();

    /* here, do your time-consuming job */
    sort(arrary, size);
    // selection_sort(arrary, size);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    // time_spent *= 1000.0;

    printArr(arrary, size);
    printf("%lf",time_spent);


    // int count = 0;
    // while(count < size){
    //     printf("%d ", arrary[count]);
    //     count++;
    // }
}