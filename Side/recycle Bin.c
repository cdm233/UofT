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

typedef  struct linkedList {
    Node *head;
} LinkedList;

struct apnode{

};

// use these prototypes to generate your code. Please do NOT change them
struct apnode *createAirportNode(char *APC){ //returns NULL if memory could not be allocated      
    //your code here
    Node *new = (Node*) malloc(sizeof(Node));
    if(new != NULL){
        new->next = NULL;
    }
    return new;
}
bool insertIntoPriorityList(LinkedList *priorityList, char *APC){
//your code goes here

}