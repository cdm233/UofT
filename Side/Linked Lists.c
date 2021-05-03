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

linkedList joinLists(linkedList *list1, linkedList *list2){
    node *temp = list2->head;
    linkedList jointed;
    jointed.head = NULL;
    
    while(temp != NULL){
        if(temp->link == NULL){
            break;
        }
        temp = temp->link;
    }
    temp->link = list1->head;
    jointed.head = list2->head;
    return jointed;
}

// reverse a LL without allocating new memory
nodePtr reverse(linkedList list) {
    nodePtr rlist = NULL;    
    nodePtr temp = list.head;
    while (temp != NULL) {
        nodePtr np = temp;
        temp = temp->link;
        np->link = rlist;
        rlist = np;
    }
    return rlist;
}

int main(void) {
    linkedList lists;
    linkedList lists1;
    lists.head = NULL;
    lists1.head= NULL;

    insertAtFront(&lists, 0, 0, 0);
    insertAtFront(&lists, 1, 0, 0);
    insertAtFront(&lists, 2, 0, 0);
    insertAtFront(&lists, 3, 0, 0);
    insertAtFront(&lists, 4, 0, 0);

    lists.head = reverse(lists);

    // nodePtr temp = lists.head;
    // temp = temp->link;
    // temp->col = 99;
    // temp->link = NULL;
    
    // insertAtFront(&lists1, 2, 0, 0);
    // insertAtFront(&lists1, 2, 1, 3);
    // insertAtFront(&lists1, 1, 3, 2);
    // traverse(&lists);

    traverse(&lists);
    // printf("\n");
    // traverse(&lists1);

    return 0;
}