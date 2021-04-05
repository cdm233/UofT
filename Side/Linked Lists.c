/* 
File:        Linked Lists.c
Author:      Derek Chen
Student#:    1006751267
Date:        March 30, 2021
Description: This is a complete list of basic function to manipulate linked lists

steps:
    1. first define the nodes of the linked lists with "typedef struct"
    2. create node, and nodePTR from this datatype
    3. create the head of the linked list with "typedef struct" and call it linkedlists, which
    contain one pointer pointing to the first element of the list.

note:
    1. all function should receive the linked list as a pointer
    2. link the last node of the linked list to NULL to avoid infinite loop
    3. u cant link twice in advance
    4. modification to each node should be done in the traverse function
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct nodes{
    int row;
    int col;
    int score;
    struct nodes *link;
} node, *nodePtr;

typedef struct linkedLists{
    node *head;
} linkedList;

void traverse(linkedList *list){
    nodePtr temp = list->head;
    while(temp != NULL){
        // do something
        printf("%d %d %d\n", temp->row,temp->col,temp->score);
        temp = temp->link;
    }
}

node *createNode(int row, int col, int score){
    node *new = (node*) malloc(sizeof(node));
    if(new != NULL){
        new->row = row;
        new->col = col;
        new->score = score;
        new->link = NULL;
    }
    return new;
}

bool insertAtFront(linkedList *list, int row, int col, int score){
    if(list->head == NULL){
        list->head = createNode(row, col, score);
        return list->head != NULL;
    }
    node *temp = createNode(row, col, score);
    if(temp == NULL){
        return false;
    }

    temp->link = list->head;
    list->head = temp;
    
    return true;
}

bool isEmpty(linkedList *list){
    if(list->head == NULL){
        return true;
    }
    return false;
}

// bool insertAtBack(linkedList *list, int value){
//     if(isEmpty(list)){
//         return insertAtFront(list, value);
//     }
//     node *n = list->head;

//     while(n->link != NULL){
//         n = n->link;
//     }

//     n->link = createNode(value);
//     if(n->link == NULL){
//         return false;
//     }
//     return true;
// }

// void deleteFront(linkedList *list){
//     if(isEmpty(list)){
//         return;
//     }

//     node *new = list->head->link;

//     free(list->head);
//     list->head = new;
// }

// void deleteBack(linkedList *list){
//     if(isEmpty(list)){
//         return;
//     }
//     if(list->head->link == NULL){
//         deleteFront(list);
//         return;
//     }

//     node *temp = list->head;
//     node *back = list->head;

//     while(temp->link != NULL){
//         temp = temp->link;
//         if(temp->link != NULL){
//             back = back->link;
//         }
//     }

//     free(temp);
//     back->link = NULL;
// }

// int deleteAllNode(linkedList *list){
//     int num = 0;
//     while(!isEmpty(list)){
//         deleteFront(list);
//         num++;
//     }
//     list->head = NULL;
//     return num;
// }

// recursive version of traverse
// void printList(node *node){
//     if(node != NULL){
//         printf("%d",node->data);
//         printList(node->link);
//     }
// }

// binary search only for sorted array
int binarySearch(int list[], int listLength, int target){
    int low = 0, high = listLength -1, mid;
    while(low <= high){
        mid = (low + high)/2;
        if(target == list[mid]){
            return mid;
        }else if(target < list[mid]){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }
    return -1;
}

int main(void) {
    linkedList lists;
    lists.head = NULL;

    insertAtFront(&lists, 0, 1, 1);
    insertAtFront(&lists, 1, 0, 1);
    insertAtFront(&lists, 3, 2, 1);
    
    // traverse(&lists);

    lists.head->link->score += 2;
    traverse(&lists);

    // int a[] = {1,2,3,4,6,8,9,12,16,19,21,24,26,27,29,30};

    // int l = sizeof(a)/sizeof(int);

    // int b = binarySearch(a,l,9);

    // printList(lists.head);

    // deleteBack(&lists);

    // traverse(&lists);

    return 0;
}