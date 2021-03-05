/*
    Date: Feb. 24, 2021
    Lab Purpose: This is a battleship game
    Name: Derek Chen
    Student#: 1006751267
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARDROWS 9
#define BOARDCOLS 11

bool dumpComputer = false; //causes dump of computer board before game if true (for debugging)

// boards. 0 means empty, non-zero means ship is there, number is size, -tive means hit on a ship
int playerBoard[BOARDROWS + 1][BOARDCOLS + 1];
int computerBoard[BOARDROWS + 1][BOARDCOLS + 1];
int compShotBoard[BOARDROWS + 1][BOARDCOLS + 1];

int getRand(int lowval, int highval) {
    return (rand() % (highval + 1 - lowval) + lowval);
}

int getShot(bool fromUser, int board[BOARDROWS + 1][BOARDCOLS + 1]) {
    int row, col;

    while (1) {
        if (fromUser) {
            printf("Give a shot (row, col):");
            scanf("%d%d", & row, & col);
            
            if (col < 1 || col > BOARDCOLS || row < 1 || row > BOARDROWS) {
                printf("Invalid input\n");
            }
            else { //valid input
                break;
            } 
        } else {
            //computer generated
            row = getRand(1, BOARDROWS);
            col = getRand(1, BOARDCOLS);
            
            if (compShotBoard[row][col] == 0) {
                //make sure haven't shot here before
                compShotBoard[row][col] = 1; //valid shot
                break;
            }
        }
    } //will leave this loop with valid input
    if (board[row][col] != 0) {
        if (board[row][col] > 0){
            board[row][col] = -1 * board[row][col]; //make sure is -tive
        }
        return -1 * board[row][col]; //a hit!
    }

    return 0; //miss
}

bool allShipsNotHit(int board[BOARDROWS + 1][BOARDCOLS + 1]) {
    int i, j;

    for (i = 1; i <= BOARDROWS; i++) {
        for (j = 1; j <= BOARDCOLS; j++) {
            if (board[i][j] > 0) { //ship and not hit
                return (true);
            }
        }
    }

    return (false); //no ships found not all hit
}

bool noneLeft(int valueToFind, int board[BOARDROWS + 1][BOARDCOLS + 1]) {
    int i, j;
    for (i = 1; i <= BOARDROWS; i++) {
        for (j = 1; j <= BOARDCOLS; j++) {
            if (board[i][j] == valueToFind) //ship and not hit
                return (false);
        }
    }

    return (true); //no ships found, all hit
}

int isValid(int x, int y, int ori, int size,
    int target[BOARDROWS + 1][BOARDCOLS + 1], int *conflict) {

    // initial check, only checks if input is valid

    // pointer used to change the value of conflictWithShip within the function
    // reset and assign false to conflictWithShip
    *conflict = 0;

    // check if passes x and y value are within the board
    if (x < 1 || x > BOARDCOLS) {
        return false;
    }

    if (y < 1 || y > BOARDROWS) {
        return false;
    }

    // checks if the orientation is either 0 or 1
    if (ori != 1 && ori != 0) {
        return false;
    }

    // if inputs pass initial check
    // second check, check if inputs contradict with the board
    if (ori == 0 && ((x - 1) + size) > BOARDCOLS) {
        return false;
    }

    if (ori == 1 && ((y - 1) + size) > BOARDROWS) {
        return false;
    }

    // final check, check if input contradict with existing ships
    int i;
    if (ori == 0) { // check if orientation is 0
        // checks if each tile that the new ship is going to occupy
        for (i = 0; i < size; i++) {
            // if the tile occupied is not empty, it means collision took place 
            if (target[y][x + i] != 0) {
                // only print error message if populating player board 
                if(target == playerBoard){
                    printf("Conflicts with ship already placed\n");
                    *conflict = 1;
                }
                return false;
            }
        }
    } else { // check if orientation is 1
        for (i = 0; i < size; i++) {
            // same logic as above
            if (target[y + i][x] != 0) {
                if(target == playerBoard){
                    printf("Conflicts with ship already placed\n");
                    *conflict = true;
                }
                return false;
            }
        }
    }

    // if passes all checks, return true
    return true;
}

// checks if all five inputs are valid
int finalValidCheck(int arr[5]) {
    int i;

    for (i = 0; i < 5; i++) { // 
        if(arr[0] == 0){
            return false;
        }else if (arr[0] == 1 && arr[i] != arr[0]) {
            return false;
        }
    }

    return true;
}

// this function recives the coordinate of the ship, orientation, size,
// and the board to which it will be inserted to
void insertBattleShip(int xIndex, int yIndex, int orientation,
    int size, int target[BOARDROWS + 1][BOARDCOLS + 1]) {

    int i;

    if (orientation == 0) { // insert ship horizontally if it's in orientation 0
        for (i = 0; i < size; i++) {
            target[yIndex][xIndex + i] = size;
        }
    } else {
        for (i = 0; i < size; i++) { // insert ship vertically if it's in orientation 1
            target[yIndex + i][xIndex] = size;
        }
    }
}

// populates the board
void populateBoard(bool getUserInput, int board[BOARDROWS + 1][BOARDCOLS + 1]) {
    bool validInput = false;
    
    // bool type variable to check if collision between ships take place 
    int conflictWithShip = 0, *conflictPTR = &conflictWithShip;

    if (getUserInput) { // populate the board with uer input
        printf("Rows are 1 - 9, Columns are 1 - 11\n");
        printf("Orientation is 0 for across, 1 for down\n");

        int fiveValidInput[5] = {0,0,0,0,0}, counter = 0;
        
        // keeps looping until all five inputs are valid
        while (!validInput) {
            int xIndex, yIndex, orientation, checkValid;

            printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:", (5 - counter));
            scanf("%d %d %d", & yIndex, & xIndex, & orientation);
            
            // checks if the user input is valid
            checkValid = isValid(xIndex, yIndex, orientation, 5 - counter, playerBoard, conflictPTR);

            if (checkValid) { // if the user input is valid, insert battleship 
                fiveValidInput[counter] = 1;
                insertBattleShip(xIndex, yIndex, orientation, 5 - counter, playerBoard);
                counter++;
            } else { // if the user input is not valid, print invalid input; 
                     // however, it's it's due to collision with another ship,
                     // then do not print
                     
                fiveValidInput[counter] = 0;
                if(!conflictWithShip){
                    printf("Invalid Input\n");
                }
            }

            // check if all five inputs are valid
            validInput = finalValidCheck(fiveValidInput);
        }
    }else{ // populate the board randomly      
        int fiveValidInputC[5] = {0,0,0,0,0};
        int validComputerInput = false;
        int size = 0;

        // it will keep looping if not all five randomized values 
        // are valid at the same time
        while (!validComputerInput) {
            int xIndex, yIndex, orientation, checkValid;
            int x, y, ori;
            bool check = false;

            // randomize value for each
            y = getRand(1,9);
            x = getRand(1,11);
            ori = getRand(0,1);

            checkValid = isValid(x, y, ori, 5 - size, computerBoard, conflictPTR);

            if (checkValid) { // same as above
                fiveValidInputC[size] = 1;
                insertBattleShip(x, y, ori, 5 - size, computerBoard);
                size++;
            } else {
                fiveValidInputC[size] = 0;
            }
            validComputerInput = finalValidCheck(fiveValidInputC);
        }
    }
}

void showBoard(int board[BOARDROWS + 1][BOARDCOLS + 1]) {
    int i, j;
    
    printf("   Cols\n");
    printf("    1  2  3  4  5  6  7  8  9 10 11\n");
    printf("     ________________________________\n");
    
    for (i = 1; i <= BOARDROWS; i++) {
        printf("R%d|", i);
        for (j = 1; j <= BOARDCOLS; j++) {
            if (board[i][j] >= 0)
                printf(" ");
            printf("%d ", board[i][j]);
        }

        printf("|\n");
    }

    printf("  __________________________________\n");
}

int main(int argc, char ** argv) {
    bool playerBoardOK, computerBoardOK;
    int i, j;
    // initialize the seed randomly.

    srand(time(NULL));  

    //init the boards
    for (i = 0; i < BOARDROWS; i++) {
        for (j = 0; j < BOARDCOLS; j++) {
            playerBoard[i][j] = 0;
            computerBoard[i][j] = 0;
            compShotBoard[i][j] = 0;
        }
    }

    populateBoard(true, playerBoard);
    populateBoard(false, computerBoard);
    printf("Your board is\n");
    
    showBoard(playerBoard);
    
    if (dumpComputer) {
        printf("\n\nComputer board is\n");
        showBoard(computerBoard);
    }

    // play starts here
    playerBoardOK = true;
    computerBoardOK = true;
    
    while (playerBoardOK && computerBoardOK) {
        int hit = getShot(true, computerBoard); //shot from user
        
        if (hit) {
            printf("HIT on size %d\n", hit);
            
            if (noneLeft(hit, computerBoard)) {
                printf("Sunk computer's %d\n", hit);
            }
        } else {
            printf("MISS!!\n");
        }

        hit = getShot(false, playerBoard);

        if (hit) {
            printf("Computer hits! Size=%d\n", hit);

            if (noneLeft(hit, computerBoard)){
                printf("Sunk your %d\n", hit);
            }
        } else {
            printf("Computer miss!\n");
        }

        playerBoardOK = allShipsNotHit(playerBoard);
        computerBoardOK = allShipsNotHit(computerBoard);
        //    showBoard(playerBoard);	//debug
        //    showBoard(computerBoard);	//debug
    }

    if (playerBoardOK) {
        printf("You win!\n");
    }
    else {
        printf("You lose.\n");
    }
    showBoard(computerBoard);

    return 0;
}