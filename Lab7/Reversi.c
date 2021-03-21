/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: Derek Chen *
 * Student#:    1006751267
 * Date:        Jan 2021
 */

/*
    TODO: 
        1. the last step of sample output is wrong, check when input is ad
        2. need to write the AI
        3. count player's result and print game result
*/



#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
/* None for now */
void configureBoard(char board[][26], char, char move[3]);
void initializeBoard(char board[][26], int n);
void checkValidMove(char board[][26], int boardDemension, char colour, int, int, int *, int details[8][3]);
void flip(char board[][26], int boardDemension, char colour, int, int, int detail[3]);
int checkBoard(char board[][26], int boardDemension, char);

// this function configures the board with inputs
void configureBoard(char board[][26], char colour, char move[3]){
    char player = colour;
    int rowIndex = (int) move[0] - 'a', colIndex = (int) move[1] - 'a';

    board[rowIndex][colIndex] = player;
}

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

void checkValidMove(char board[][26], int boardDemension, char colour, int x, int y, int *num, int details[8][3]){
    int count = 0, tilesNum;
    for(int i = -1; i <= 1; i ++){
        for(int j = -1; j <= 1; j ++){
            if(!(i == 0 && j == 0)){ // deltaRow and deltaCol cannot both be 0
                if ((tilesNum = checkLegalInDirection(board, boardDemension, x, y, colour, i, j)) != 0){
                    details[count][0] = i;
                    details[count][1] = j;
                    details[count][2] = tilesNum;

                    count ++;

                    *num = count;
                    // printf("col: %d, row: %d, tiles: %d\n", i, j, tilesNum);
                }
            }
        }
    }
}


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
                    return true;
                }
            }
        }
    }

    if(!hasSpace){
        return -1;
    }

    return 0;
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

    int numberToFlip = 0;

    char oppositeColour = colour == 'W' ? 'B' : 'W'; // if passed colour is B then W
    // the tile only valid if there is an opposite colour in the immediate adjacent tile
    bool adjacentOppositeColour = false; 

    // checks if the tile in the given direction is within the board
    if(!positionInBounds(n, row + deltaRow, col + deltaCol)){
        return false;
    }

    if(deltaRow != 0){
        // initializes the col index
        int j = col + deltaCol;

        // j needs to increase at the same time as i to unsure it's in the diagonal directgion
        for(int i = row + deltaRow; i < n && i >= 0; i += deltaRow, j += deltaCol){ 
            if(deltaCol != 0){ // this is in the diagonal direction
                if(i == row + deltaRow && j == col + deltaCol){
                    // check if there is a immediate adjacent opposite colour in the given direction
                    if(board[i][j] == oppositeColour){ 
                        adjacentOppositeColour = true;
                    }else{ // if there is not then no need to continue
                        return 0;
                    }
                }

                if(adjacentOppositeColour){
                    numberToFlip++;
                }

                // the given direction is only valid if there is also a player's colour in the end
                if(board[i][j] == colour && adjacentOppositeColour){
                    return numberToFlip;
                }
            }else{ // deltaCol == 0, this is in the direction of up and down
                if(i == row + deltaRow){
                    if(board[i][col] != oppositeColour){
                        return 0;
                    }
                }

                numberToFlip++;

                if(board[i][col] == colour){
                    return numberToFlip;
                }
            }
        }    
    }else{ // in the direction of left or right
        for(int j = col + deltaCol; j < n && j >= 0; j += deltaCol){
            if(j == col + deltaCol){
                if(board[row][j] != oppositeColour){
                    return 0;
                }
            }

            numberToFlip++;

            if(board[row][j] == colour){
                return numberToFlip;
            }
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

    printf("Enter move for colour %c (RowCol):", turn);
    scanf(" %c%c", col, row);

    *row = *row - 'a'; 
    *col = *col - 'a'; 

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

    char move[2];
    while(!gameFinished){
        int row = 0, col = 0;
        int *rowPointer = &row;
        int *colPointer = &col;

        int details[8][3], numberOfTargets = 0;
        int *num = &numberOfTargets;

        if(checkBoard(board, boardDemension, currentPlayer) == 0){
            printf("%c player has no valid move.\n", currentPlayer);
            currentPlayer = currentPlayer == 'B' ? 'W' : 'B';
            continue;
        }else if(checkBoard(board, boardDemension, currentPlayer) == -1){
            gameFinished = true;
            continue;
        }

        makeMove(board, boardDemension, currentPlayer, rowPointer, colPointer);

        checkValidMove(board, boardDemension, currentPlayer, col, row, num, details);

        if(numberOfTargets != 0){
            for(int i = 0; i < numberOfTargets; i++){
                flip(board, boardDemension, currentPlayer, row, col, details[i]);
            }
        }else{
            // printf("Invalid move.\n");
        }

        printBoard(board, boardDemension);
        
        currentPlayer = currentPlayer == 'B' ? 'W' : 'B';

        // configureBoard(board, currentPlayer, move);

        // printBoard(board, boardDemension);
    }

    // prints all avaliable moves for both players
    // printValidMoves(board, boardDemension, 'W');
    // printValidMoves(board, boardDemension, 'B');
    
    return 0;

    // printf("%d%d\n", row, col);
}
#endif // DO NOT DELETE THIS LINE