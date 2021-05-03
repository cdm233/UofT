// include all of this in your solution
#include  <stdio.h>
#include  <stdlib.h>
#include <stdbool.h>

typedef struct node {  
    int data;  struct node *left, *right;
} Node;

typedef struct bstree {    
    Node *root;
} BSTree;

void initBSTree(BSTree *tree) {    
    tree->root = NULL;
}

Node *createNode(int value) {
  Node *p= (Node *) malloc(sizeof(Node));
  if (p != NULL) {
    p->data = value;
    p->left = p->right = NULL;
  }
  return p;
}

void recursiveTraverse(Node *n){
    if(n == NULL){
        return;
    }

    printTree(n->left);
    printf("%d ", n->data);
    printTree(n->right);
}

 //this is your prototype
 void duplicateLeftNode(BSTree *tree){
}

 int main(){
    //  duplicateLeftNode();
     return 0;
 }