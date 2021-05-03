#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

bool isEmpty(Node *head){
    return head->next == NULL;
}


// Question 1: Count the number of nodes in a list
int countnodes(Node *head ){
    int count = 0;
    
    return count;
}

// Question 2: Count the number of nodes that have a particular value
int countvalues(Node *head, int value) {
    int count = 0;
    return count;
}

// Question 3: Print all the nodes in a linked list
void printList(Node *head) {
}

// Question 4: Search through the linked list for a particular key
bool search(Node *head, int searchKey) {
    return false;
}

// Question 5: Add n data items to an ordered list, where each data item is chosen randomly from between 0 and 99
Node * insert_n(Node *head, int n) {
    return head;
}

// Question 6: Given two ordered lists genrate a new on ethat has the merged elements of both lists
Node * merge(Node *l1, Node *l2) {
    Node *newlist = NULL;
    return newlist;
}

// Question 7: Given a list, reverse the order of the elements without allocating any new memory
Node *reverse(Node *head) {
    Node *rlist = NULL;
    return rlist;
}

int main(){
    // int r = recursiveAdd(6);
    int f = fib(7);
    return 0;
}