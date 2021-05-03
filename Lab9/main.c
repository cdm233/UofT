#include <stdio.h>
#include <stdlib.h>
// #include "contactList.h"
#include <string.h>
#include <ctype.h>

// IF IT'S EASIER, YOU NEED NOT BE OVERLY GENERAL/FLEXIBLE
// BUT CAN ASSUME THESE LIMITS
#define MAXCONTACTS 30 /* max # of contacts */
#define MAXPHONES 10 /* max # of phone numbers for each contact */

#define PHONE_NUMBER_MAX_LENGTH 12

// declare the node in the linked list
typedef struct nodes{
      char name[128];
      char phoneNumber[MAXPHONES][PHONE_NUMBER_MAX_LENGTH];
      int numberOfConatacts;
      struct nodes *link;
} node, *nodePtr;

typedef struct linkedLists{
      node *head;
} linkedList;

// declare global variable since passing arguments is not allowed
linkedList list;

// this function creates a node with given information
nodePtr createNode(char name[128], char phone[MAXPHONES][PHONE_NUMBER_MAX_LENGTH], int length){
   node *new = (node*) malloc(sizeof(node));
    if(new != NULL){
         strcpy(new->name, name);
         new->numberOfConatacts = length;
         for(int i = 0; i < length; i++){
            strcpy(new->phoneNumber[i], phone[i]);
         }
        new->link = NULL;
    }
    return new;
}

// this function inserts a node at frount of a LL
int insertAtFront(linkedList *list, char name[128], char phone[MAXPHONES][PHONE_NUMBER_MAX_LENGTH], int length){
    if(list->head == NULL){ // if the LL is empty
        list->head = createNode(name, phone, length);
        return list->head != NULL;
    }
    // else
    node *temp = createNode(name, phone, length);
    if(temp == NULL){
        return 0;
    }

    temp->link = list->head;
    list->head = temp;
    
    return 1;
}



// INCLUDE YOUR OWN "HELPER" ROUTINES AS YOU SEE FIT

/*
 * convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
int convertInputToDataStructure(linkedList *list) {
   int lastOne = 0, count = 0, newContact = 0, phoneCount = 0, numberOfContacts = 0;
   char name[50];
   char phone[MAXPHONES][PHONE_NUMBER_MAX_LENGTH];
   
   while(!lastOne){ // while the current node is not the last

      // it's a new contack whenever the string changes from number to character
      if(newContact){
         insertAtFront(list, name, phone, phoneCount);
         newContact = 0;
         phoneCount = 0;
      }

      if(!atoi(contactList[count])){ // if it's name
         strcpy(name, contactList[count]);
      }else{ // if it's phone number
         strcpy(phone[phoneCount], contactList[count]);
         phoneCount++;
      }
       // if the next node is empty, insert the contact to the LL and break out
      if(!contactList[count + 1]){
         insertAtFront(list, name, phone, phoneCount);
         lastOne = 1;
         break;
      }

      if(atoi(contactList[count + 1]) == 0){
         newContact = 1;
         numberOfContacts++;
      }
      count++;
   }
   return numberOfContacts;
}

// this function prints the list in aphabetical order
void ListAllContacts(){
  nodePtr temp = list.head;
   while(temp != NULL){ // while the current node is not NULL
      printf("Name: %s\n", temp->name);
      printf("Phone(s): ");
      // number of contacts
      int count = temp->numberOfConatacts - 1;
      
      while(count >= 0){ // while it's not the last phone number
         printf("%s", temp->phoneNumber[count]);
         count--;
         if(count >= 0){
            printf(" ");
         }
      }
      printf("\n");
      // link current node to next node
      temp = temp->link;
   }
}

/*
 * printMenu - Prints out the user menu
 */
void printMenu() {
   printf("\n\nEnter a command by number\n");
   printf("1. List all contacts in alphabetical order\n");
   printf("2. Print phone(s) for a contact\n");
   printf("3. Find duplicate entries\n");
   printf("4. Delete contact\n");
   printf("5. Exit the program\n");
   printf("Your input: ");
}

//eliminate trailing \n
char* rtrim(char* str)
{
   int i;
   for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; i--)
      str[i] = '\0';
   return str;
}

// this function prints the phone numbers of a contact
void PrintContact() {
   printf("Enter name: ");
   char name[128];
   char *n = fgets(name, sizeof(name), stdin);
   n = rtrim(n);

   nodePtr temp = list.head;
   while(temp != NULL){
      if(!strcmp(name, temp->name)){
         printf("Name: %s\n", temp->name);
         printf("Phone(s): ");
         int count = temp->numberOfConatacts - 1;
         
         while(count >= 0){
            printf("%s", temp->phoneNumber[count]);
            if(count > 0){
               printf(" ");
            }
            count--;
         }
         printf("\n");
         return;
      }
      temp = temp->link;
   }
   // if the contact is not found
   printf("Contact not found\n");
}


/*
 * DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 * 
 */

// this function deletes the given contact
void DeleteContact() {
   printf("Enter name: ");
   char name[128];
   char *n = fgets(name, sizeof(name), stdin);
   n = rtrim(n);
   
   nodePtr temp = list.head;
   while(temp != NULL){
      nodePtr nextNode = temp->link;
      if(!strcmp(name, temp->name)){
         list.head = nextNode;
         return;
      }
      // check if the next node is the intended node
      if(nextNode != NULL){
         if(!strcmp(name, nextNode->name)){
            // move the previous node's link to next node's link
            // this way the linked list skips the intended node
            temp->link = nextNode->link;
         }
      }else{
         temp->link = NULL;
      }
      temp = temp->link;
   }
}


/*
 * findDuplicates finds the names of contacts with 
 * a phone number in common
 */

// struct used to store duplicates' information
typedef struct duplicates{
   char name1[128];
   char name2[128];
   char phones[MAXPHONES][PHONE_NUMBER_MAX_LENGTH];
} duplicate;

void FindDuplicates() {
   int checked = 0;
   int hasDup = 0;
   node *currentNode = list.head;
   // use bubble sort to find all duplicates 
   while(currentNode != NULL){
      node *nextNode = currentNode->link;
      while(nextNode != NULL){
         checked = 0;
         // looping through all contacts
         for(int i = 0; i < currentNode->numberOfConatacts; i++){
            if(checked){
               break;
            }
            for(int j = 0; j < nextNode->numberOfConatacts; j++){
               // because we are not asked to print all common phone number
               // skip if one common phone number already found
               if(checked){
                  break;
               }
               if(!strcmp(currentNode->phoneNumber[i], nextNode->phoneNumber[j])){
                  printf("%s and %s have a phone number in common\n", currentNode->name, nextNode->name);
                  checked = 1;
                  hasDup = 1;
               }
            }
         }
         
         nextNode = nextNode->link;
      }
      currentNode = currentNode->link;
   }
   if(!hasDup){
      printf("No duplicates found");
   }
} 

// this function swappes the two nodes' content
void swap(node* node1, node* node2){
   char tempName[50], phones[MAXPHONES][PHONE_NUMBER_MAX_LENGTH];
   int count = 0, length = 0;

   // store information into temp variable
   strcpy(tempName, node1->name);
   length = node1->numberOfConatacts;
   while(count != node1->numberOfConatacts){
      strcpy(phones[count], node1->phoneNumber[count]);
      count++;
   }
   count = 0;
   

   strcpy(node1->name, node2->name);
   // clears the phones number
   while(count != length){
      strcpy(node1->phoneNumber[count], "");
      count++;
   }
   count = 0;

   node1->numberOfConatacts = node2->numberOfConatacts;
   while(count != node2->numberOfConatacts){
      strcpy(node1->phoneNumber[count], node2->phoneNumber[count]);
      count++;
   }
   count = 0;

   strcpy(node2->name, tempName);

   // clear
   while(count != node2->numberOfConatacts){
      strcpy(node2->phoneNumber[count], "");
      count++;
   }
   count = 0;
   
   node2->numberOfConatacts = length;
   for(int i = 0; i <= length; i++, count++){
      strcpy(node2->phoneNumber[count], phones[i]);
   }
}

// sort the linked list 
void sortLL(linkedList* list, int count){
   node *currentNode = list->head;
   // this is a bubble sort
   while(currentNode != NULL){
      node *nextNode = currentNode->link;
      // printf("current node: %s, next node: %s\n", currentNode->name, nextNode->name);
      while(nextNode != NULL){
         
         if(nextNode->name && currentNode->name){
            if(strcmp(currentNode->name, nextNode->name) > 0){
               // if the next node's name is 'larger' than the previous node's
               // swap
               swap(currentNode, nextNode);
            }
         }

         nextNode = nextNode->link;
      }
      currentNode = currentNode->link;
   }
}

int main()
{  
   int numOfContacts = 0;
   list.head = NULL;
   
   // first move data from contactList.h to a data structure
   numOfContacts = convertInputToDataStructure(&list);
   // then sort the linked list in aphabetical order 
   sortLL(&list, numOfContacts);
   
   char notDone = 1;
   while (notDone) {
      printMenu();
      char userChoice[100];
      char* s = fgets(userChoice, sizeof(userChoice), stdin);
      if (!s)
      {
         printf("Wrong input\n");
         continue;
      }
      s = rtrim(s); /* eliminate trailing \n */
      //printf("selection = %s\n", s);
      int userSelection = atoi(s);

      switch (userSelection) {
         case 1: ListAllContacts(); break;
         case 2: PrintContact(); break;
         case 3: FindDuplicates(); break;
         case 4: DeleteContact(); break;
         case 5: notDone = 0; break;
         default: printf("Bad command...\n"); break;
         }
     
   }
   
   // PUT ANY POST_RUN CODE HERE

   return 0;
}