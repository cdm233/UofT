#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct nodes{
    int data;
    struct nodes *left, *right;
} node;

typedef struct bstree{
    node *root;
} tree;

node *createNode(int value){
    node *temp = (node*) malloc(sizeof(node));

    if(temp != NULL){
        temp -> data = value;
        temp -> left = NULL;
        temp -> right = NULL;
    }
    return temp;
}

void initialize(tree *t){
    t->root = NULL;
}

bool isEmpty(tree *t){
    if(t->root == NULL){
        return true;
    }
    return false;
}

// insert
bool insertTree(tree *t, int value){
    if(isEmpty(t)){
        t->root = createNode(value);
        return t->root != NULL;
    }
    node *current = t->root;
    node *parent = NULL;
    while(current != NULL){
        parent = current;
        if(value <= current->data){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    if(value <= parent->data){
        parent->left = createNode(value);
        return parent->left != NULL;
    }else{
        parent->right = createNode(value);
        return parent->right != NULL;
    }
}

// recursive insert
node *recInsertHelper(node *n, int value){
    if(n == NULL){
        return createNode(value);
    }
    if(value <= n->data){
        n->left = recInsertHelper(n->left, value);
    }else{
        n->right = recInsertHelper(n->right, value);
    }
    return n;
}

bool recInsert(tree *t, int value){
    node *inserted = recInsertHelper(t->root, value);
    t->root = inserted;
    return inserted != NULL;
}

// search tree
node *search(tree *t, int value){
    node *current = t->root;
    while(current != NULL && current->data != value){
        if(value < current->data){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    return current;
}

// recursive search
node *recSearchHelp(node *n, int value){
    if(n == NULL){
        return n;
    }

    if(n->data == value){
        return n;
    }

    if(value < n->data){
        return recSearchHelp(n->left, value);
    }else{
        return recSearchHelp(n->right, value);
    }
}

// find min
node *findMin(node* t){
    if(t != NULL){
        while(t->left != NULL){
            t = t->left;
        }
    }
    return t;
}

// find max
node *findMax(node* t){
    if(t != NULL){
        while(t->right != NULL){
            t = t->right;
        }
    }
    return t;
}

// delete node
void delete(){

}

node *recDeleteHelper(node *n, int data){
    node *temp;

    if(n == NULL);
    else if(data < n->data){
        n->left = recDeleteHelper(n->left, data);
    }else if(data > n->data){
        n->right = recDeleteHelper(n->right, data);
    }else if(n->left != NULL && n->right != NULL){
        temp = findMin(n->right);
        n->data = temp-data;
        n->right = recDeleteHelper(n->right, data);
    }else{
        temp = n;
        if(n->left == NULL){
            n = n->right;
        }else if(n->right == NULL){
            n = n->left;
        }
        free(temp);
    }
    return n;
}

//recursive print
void printTree(node *n){
    if(n == NULL){
        return;
    }

    printTree(n->left);
    printf("%d ", n->data);
    printTree(n->right);
}

// rec search number of node that is between interval
int countBetween(node * root, int mininum, int maximum) {
    if (root == NULL)
        return 0;
    if (root -> data < mininum)
        return countBetween(root -> right, mininum, maximum);
    if (root -> data > maximum)
        return countBetween(root -> left, mininum, maximum);
    return (1 + countBetween(root -> left, mininum, maximum)
    + countBetween(root -> right, mininum, maximum));
}

// rec search number of node that is below or equal to threshold
int countBelow (int threshold, node *startNode) {
    int below = 0;

    if (startNode != NULL) {
        below += countBelow(threshold, startNode->left);
        
        if (startNode->data <= threshold) {
            below++;
            // if the node is equal to threshold, no need to visit right
            if (startNode->data < threshold){
                below += countBelow(threshold, startNode->right);
            }
        }
    }
    return (below);
}

// rec search number of node that is above or equal to threshold
int countAbove (int threshold, node *startNode) {
    int above = 0;

    if (startNode != NULL) { // base case NULL, send back the 0
        // always look down left subtree, because if we got here, we must look lower
        above += countAbove(threshold, startNode->right);
        // check the current node to see if we have to count that
        if (startNode->data >= threshold) {
            above++;
            // if the current node is greater than or equal to the threshold
            // don’t have to look down right side, making use of BST structure!
            if (startNode->data > threshold)
                above += countAbove(threshold, startNode->left);
        }
    }
    return (above);
}

int main(){
    tree t;
    initialize(&t);
    bool re = insertTree(&t, 1);
    re = recInsert(&t, 2);
    re = recInsert(&t, 3);
    re = recInsert(&t, 4);
    re = recInsert(&t, 5);

    node *searched = recSearchHelp(t.root, 3);

    node *min, *max;

    max = findMax(t.root);
    min = findMin(t.root);
    
    // printf("%d", searched->data);
    // printf(" %d", max->data);
    // printf(" %d", min->data);

    printTree(t.root);

    printf("\n%d", countBelow(3, t.root));

    // printTree(t.root);
    return 0;
}

