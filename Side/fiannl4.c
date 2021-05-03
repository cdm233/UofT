#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// here are the definitions of the node and of the linked list
typedef struct  node {
    char *APCode;
    int priority;
    struct node *next;
} Node;

typedef struct linkedList {
    Node *head;
} LinkedList;

// use these prototypes to generate your code. Please do NOT change them

bool insertIntoPriorityList(LinkedList *priorityList, char *APC){
//your code goes here

}