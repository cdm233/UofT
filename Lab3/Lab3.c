/*
 * Date: Jan 23, 2021 
 * Lab Purpose: This is a simplified version of Blackjack with:
 *  • this program will loop if the user does not input valid value (neither 1 nor 0)
 * Name: Derek Chen
 * Student #: 1006751267
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int newCard(){ // this function will create a new random integer
    int newCardValue;
    
    newCardValue = rand() % 13 + 1;
    
    return newCardValue;
}

int main(int argc, char **argv)
{
    int playerCard,dealerCard; // initialize variables
    int playerCardPrint,dealerCardPrint;
    int hitOrStay; 
	int validUserInput = 0; // used as boolean type
    
    if(argc == 1){ // set up new random seed
        srand(time(NULL));
    }else{
        srand(atoi(argv[1]));
    }
   
    dealerCard = newCard(); // dealer's and player's first card
    playerCard = newCard(); 
    playerCardPrint = playerCard;
    dealerCardPrint = dealerCard;
    
    if(dealerCard > 10){ // reset value if it's greater than 10
        dealerCard = 10;
    }
    
    if(playerCard > 10){
        playerCard = 10;
    }
    
    // show player and dealer's first card
    printf("First cards: player %d, dealer %d\n",playerCardPrint,dealerCardPrint); 
    
    while(validUserInput == 0){ // while loop used to ensure user input 0 or 1
        printf("Type 1 for Hit, 0 to Stay: ");
        scanf("%d",&hitOrStay);
        validUserInput = hitOrStay == 1 || hitOrStay == 0 ? 1 : 0;
    }
    
    validUserInput = 0; // reset checker after valid user input
    
    // main while loop for the user to recieve cards, will stop if the user decides to stay( hitOrStay == 0 )
    while(hitOrStay == 1){ 
        int newPlaerCard,newPlaerCardPrint; //variables used only within the loop
        
        // dealing new card to the player
        newPlaerCard = newCard();
        newPlaerCardPrint = newPlaerCard;
        
        if(newPlaerCard > 10){
            newPlaerCard = 10;
        }
        
        playerCard += newPlaerCard;
        
        // print player's new card and current total value
        printf("Player gets a %d, worth is %d\n", newPlaerCardPrint, playerCard);
        
        // check if player is busted ( card value greater than 21 )
        if(playerCard > 21){ 
            // diaplay the game result and end the game as the player goes over 21
            printf("Player over 21, Dealer wins\n");
            return 0;
        }else{ // if player not busted, ask if player wants to stay
            while(validUserInput == 0){ // while loop used to ensure user input 0 or 1
                printf("Type 1 for Hit, 0 to Stay: ");
                scanf("%d",&hitOrStay);
                validUserInput = hitOrStay == 1 || hitOrStay == 0 ? 1 : 0;
            }   
            validUserInput = 0; // reset checker
        }
    }
    
    // the main while loop ends if player decides to stay, dealer will now recieve cards 
    printf("Dealer gets: ");
    
    // the dealer will keep recieving new cards until it reaches 17 or is busted
    while(dealerCard < 17){ 
        int newDealerCardValue = newCard();
        int newDealerCardValuePrint = newDealerCardValue;
        
        if(newDealerCardValue > 10){
            newDealerCardValue = 10;
        }
        
        dealerCard += newDealerCardValue;
        
        printf("%d ", newDealerCardValuePrint);
        
        if(dealerCard > 21){
            // diaplay the game result and end the game if the dealer goes over 21
            printf("\n");
            printf("Dealer over 21, Player wins\n");
            return 0;
        }
    }
    
    // create a new line
    printf("\n");
    
    // print the final game result and end the game
    if(dealerCard > playerCard){
        printf("Dealer better than Player, Dealer wins\n");
        return 0;
    }else if(playerCard > dealerCard){
        printf("Player better than Dealer, Player wins\n");
        return 0;
    }else{
        printf("Tie!\n");
        return 0;
    }
}