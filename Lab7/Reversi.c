/*
 * File:        Reversi.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * Derek Chen *
 * Student#:    1006751267
 * Date:        March 28, 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
/* None for now */
void initializeBoard(char board[][26], int n);
void checkValidMove(char board[][26], int boardDemension, char colour, int, int, int *, int details[8][3]);
void flip(char board[][26], int boardDemension, char colour, int, int, int detail[3]);
int checkBoard(char board[][26], int boardDemension, char);
int numberToFlip(char board[][26], int, char, int, int, int, int);
int checkScore(char board[][26], int, char);

// this function initializes the board and the initial four center tiles
void initializeBoard(char board[][26], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i + 1 == n/2){ // the upper middle row
                if(i * j == (n-2) * (n-2) / 4){
                    board[i][j] = 'W';
                }else if(i * j == ((n-2) / 2) * ((n-2) / 2 + 1)){
                    board[i][j] = 'B';
                }else{
                    board[i][j] = 'U';
                }
            }else if(i == n/2){ // the lower middle row
                if(i * j == ((n-2) / 2) * ((n-2) / 2 + 1)){
                    board[i][j] = 'B';
                }else if(i * j == ((n-2) / 2 + 1) * ((n-2) / 2 + 1)){
                    board[i][j] = 'W';
                }else{
                    board[i][j] = 'U';
                }
            }else{ // every other places
                board[i][j] = 'U';
            }
        }
    }
}

// this function calculates how many tiles to flip, assuming the given direction is valid
int numberToFlip(char board[][26], int n, char colour, int col, int row, int deltaRow, int deltaCol){
    int number = 0;
    for(int i = row + deltaRow, j = col + deltaCol; j < n && j >= 0 && i < n && i >= 0; i += deltaRow, j += deltaCol){
        if(board[i][j] == colour){
            return number;
        }else{
            number ++;
        }
    }
}

// this function checks if the tile is valid
void checkValidMove(char board[][26], int boardDemension, char colour, int x, int y, int *num, int details[8][3]){
    int count = 0, tilesNum = 0;
    for(int i = -1; i <= 1; i ++){
        for(int j = -1; j <= 1; j ++){
            if(!(i == 0 && j == 0)){ // deltaRow and deltaCol cannot both be 0
                if (checkLegalInDirection(board, boardDemension, x, y, colour, i, j)){
                    details[count][0] = i;
                    details[count][1] = j;
                    details[count][2] = numberToFlip(board, boardDemension, colour, y, x, i, j);
                    
                    // pointer changes the valid of numberOfTarget outside of the function
                    *num = ++count;
                }
            }
        }
    }
}

// this function flips a certain amount of tiles in the given direction
void flip(char board[][26], int boardDemension, char colour, int x, int y, int detail[3]){
    int tilesToFlip = detail[2];
    for(int i = 0; i <= tilesToFlip; i++){ // i is deltaRow
        if(i == 0){
            board[y][x] = colour;
            continue;
        }
        board[y + i*detail[0]][x + i*detail[1]] = colour;
    }
}

// this function checks if the game is over or if the player has no avaliable move
int checkBoard(char board[][26], int boardDemension, char colour){
    bool hasSpace = false;
    for(int i = 0; i < boardDemension; i++){
        for(int j = 0; j < boardDemension; j++){
            if(board[i][j] == 'U'){
                hasSpace = true;
                int details[8][3], numberOfTargets = 0;
                int *num = &numberOfTargets;
                checkValidMove(board, boardDemension, colour, i, j, num, details);

                if(numberOfTargets != 0){
                    // this means the player has valid move
                    return 1;
                }
            }
        }
    }

    if(!hasSpace){
        // there is no space on board, game ends
        return -1;
    }else{
        // given player has no avaliable move
        return 0;
    }
}

// this function calculated the score of given player
int checkScore(char board[][26], int n, char computerColour){
    int num = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] == computerColour){
                num ++;
            }
        }
    }

    return num;
}

// ========= Function implementation ==========
/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
    (void)board;
    (void)n;

    char initial = 'a';
    // prints the first row: column indexes
    for(int i = 0; i <= n; i++){
        if(i == 0){
            printf("  ");
        }else{
            printf("%c", initial);
            initial++;
        }
    }

    printf("\n");

    // main loop to print the board
    initial = 'a';
    for(int i = 0; i < n; i++){
        printf("%c ", initial);
        initial++;
        for(int j = 0; j < n; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
    (void)n;
    (void)row;
    (void)col;

    if(row <= n && row >= 0 && col <= n && col >= 0){
        return true;
    }
    return false;  
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row,
 		int col, char colour, int deltaRow, int deltaCol) {
    (void)board;
    (void)n;
    (void)row;
    (void)col;
    (void)colour;
    (void)deltaRow;
    (void)deltaCol;

    char oppositeColour = colour == 'W' ? 'B' : 'W'; // if passed colour is B then W
    // the tile only valid if there is an opposite colour in the immediate adjacent tile

    // checks if the tile in the given direction is within the board
    if(!positionInBounds(n, row + deltaRow, col + deltaCol)){
        return false;
    }

    for(int i = row + deltaRow, j = col + deltaCol; j < n && j >= 0 && i < n && i >= 0; i += deltaRow, j += deltaCol){
        if(i == row + deltaRow && j == col + deltaCol && board[i][j] != oppositeColour){
            return false;
        }

        if(board[i][j] == colour){
            return true;
        }
    }
    // just in case everything fails
    return 0;             
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    (void)board;
    (void)n;
    (void)turn;
    (void)row;
    (void)col;

    int result[3] = {}, highest = 0, lowestRow = n, lowestCol = n;

    // check all avaliable moves
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col] == 'U'){ // only checks if the tile is not occupied
                bool checked = false; // the same tile can only be printed once 
                for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
                    for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
                        if(!(deltaRow == 0 && deltaCol == 0)){ // deltaRow and deltaCol cannot both be 0
                            char oppositeColour = turn == 'W' ? 'B' : 'W';
                            int number = 0;

                            // if the first tile in the direction is out of the board then skip
                            if(!positionInBounds(n, row + deltaRow, col + deltaCol)){
                                continue;
                            }

                            for(int i = row + deltaRow, j = col + deltaCol; j < n && j >= 0 && i < n && i >= 0; i += deltaRow, j += deltaCol){
                                // if the first tile in the direction is not the opposite color then skip
                                if(i == row + deltaRow && j == col + deltaCol && board[i][j] != oppositeColour){
                                    break;
                                }

                                // number of tiles to flip increases by one 
                                number++;

                                if(board[i][j] == turn){
                                    // if the number of tiles to flip is larger than previous higest
                                    // update highest
                                    if(number > highest){
                                        // if the row index is less then previous lowest, update
                                        if(row < lowestRow){
                                            // if the row index is less then previous lowest, update
                                            if(col < lowestCol){
                                                // only the tile the most tiles to flip, lowest row and col index will be picked        
                                                result[0] = row;
                                                result[1] = col;
                                                result[2] = number;
                                                highest = number;
                                                lowestRow = row;
                                                lowestCol = col;
                                                // break out, stop this iteration, check next tile on the board
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    *row = result[1];
    *col = result[0];

    return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    // Complete your main function here
    int boardDemension, gameFinished = false;
    char board[26][26], computerColour; // board initialized as 26 by 26 static array
    char currentPlayer = 'B';

    printf("Enter the board dimension:");
    // scanf leaves newline in the buffer; solution is to put a whitespace before %
    scanf(" %d",&boardDemension);

    printf("Computer plays (B/W) :");
    scanf(" %c", &computerColour);

    // initializes board
    initializeBoard(board, boardDemension);

    // prints board
    printBoard(board, boardDemension);

    while(!gameFinished){
        int row = 0, col = 0;
        int details[8][3], numberOfTargets = 0;
        int *num = &numberOfTargets;

        if(checkBoard(board, boardDemension, currentPlayer) == 0){
            // if the current player has no valid move, skip, let the opponent move
            printf("%c player has no valid move.\n", currentPlayer);
            currentPlayer = currentPlayer == 'B' ? 'W' : 'B';
            continue;
        }else if(checkBoard(board, boardDemension, currentPlayer) == -1){
            // if there is no space on board, ends game
            gameFinished = true;
            continue;
        }

        if(currentPlayer == computerColour){
            // if the current player is computer 
            makeMove(board, boardDemension, computerColour, &row, &col);
            printf("Computer places W at %c%c.\n", col + 'a', row + 'a');
        }else{
            printf("Enter move for colour %c (RowCol):", currentPlayer);
            scanf(" %c%c", &col, &row);

            col = col - 'a';
            row = row - 'a';
        }

        checkValidMove(board, boardDemension, currentPlayer, col, row, num, details);

        // one tile may have multiple lanes to flip, flip all of them
        if(numberOfTargets != 0){
            for(int i = 0; i < numberOfTargets; i++){
                flip(board, boardDemension, currentPlayer, row, col, details[i]);
            }
        }else{
            // if the player input an invalid move, game ends computer wins
            printf("Invalid move.\n");
            gameFinished == true;
            printf("%c player wins.", currentPlayer == 'W' ? 'B' : 'W');
            return 0;
        }

        printBoard(board, boardDemension);
        
        // change current player to next player
        currentPlayer = currentPlayer == 'B' ? 'W' : 'B';
    }
    
    // calculate score of computer
    int score = checkScore(board, boardDemension, computerColour);

    if(score > boardDemension * boardDemension - score){
        printf("%c player wins.", computerColour);
    }else if(score < boardDemension * boardDemension - score){
        printf("%c player wins.", computerColour == 'W' ? 'B' : 'W');
    }else{
        printf("tie.");
    }
    
    return 0;
}
#endif // DO NOT DELETE THIS LINE