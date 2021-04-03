#include <stdio.h>
#include <stdlib.h>
#include "contactList.h"
#include <string.h>
#include <ctype.h>

// IF IT'S EASIER, YOU NEED NOT BE OVERLY GENERAL/FLEXIBLE
// BUT CAN ASSUME THESE LIMITS
#define MAXCONTACTS 30 /* max # of contacts */
#define MAXPHONES 10 /* max # of phone numbers for each contact */

#define PHONE_NUMBER_MAX_LENGTH 12


// INCLUDE YOUR OWN "HELPER" ROUTINES AS YOU SEE FIT


void ListAllContacts()
{
   // YOUR CODE HERE
}


/*
 * convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
void convertInputToDataStructure() {

   // YOUR CODE HERE

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

void PrintContact() {
       // YOUR CODE HERE
}


/*
 * DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 * 
 */

void DeleteContact() {
    // YOUR CODE HERE
}


/*
 * findDuplicates finds the names of contacts with 
 * a phone number in common
 */

void FindDuplicates() {
    
    // YOUR CODE HERE

}

int main()
{
   // first move data from contactList.h to a data structure
   convertInputToDataStructure();
   
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
