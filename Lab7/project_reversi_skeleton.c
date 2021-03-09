/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * You Name Here *
 *
 * Date: Jan 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
/* None for now */
void configureBoard(char board[][26], char move[3]);
void initializeBoard(char board[][26], int n);

// this function configures the board with inputs
void configureBoard(char board[][26], char move[3]){
    char player = move[0];
    int rowIndex = (int) move[1] - 'a', colIndex = (int) move[2] - 'a';

    board[rowIndex][colIndex] = player;
}

// this function initializes the board and the initial four center tiles
void initializeBoard(char board[][26], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i + 1 == n/2){
                if(i * j == (n-2) * (n-2) / 4){
                    board[i][j] = 'W';
                }else if(i * j == ((n-2) / 2) * ((n-2) / 2 + 1)){
                    board[i][j] = 'B';
                }else{
                    board[i][j] = 'U';
                }
            }else if(i == n/2){
                if(i * j == ((n-2) / 2) * ((n-2) / 2 + 1)){
                    board[i][j] = 'B';
                }else if(i * j == ((n-2) / 2 + 1) * ((n-2) / 2 + 1)){
                    board[i][j] = 'W';
                }else{
                    board[i][j] = 'U';
                }
            }else{
                board[i][j] = 'U';
            }
        }
    }
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
    // prints the column indexes
    for(int i = 0; i <= n; i++){
        if(i == 0){
            printf("  ");
        }else{
            printf("%c", initial);
            initial++;
        }
    }

    printf("\n");

    // main loop for board generation
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
    bool hasOppositeColour = false;

    if(deltaRow != 0){
        for(int i = row + deltaRow; i < n && i > 0; i += deltaRow){
            if(deltaCol != 0){ // this is in the diagonal direction
                for(int j = col + deltaCol; j < n && j > 0; j += deltaCol){
                    if(board[i][j] == oppositeColour){
                        hasOppositeColour = true;
                    }
                    if(hasOppositeColour && board[i][j] == colour){
                        printf("\nthis is a valid position! (diagonal)\nposition:%d %d", row, col);
                        return true;
                    }
                }
            }else{ // deltaCol == 0, this is in the direction of up and down
                if(board[i][col] == oppositeColour){
                    hasOppositeColour = true;
                }
                if(hasOppositeColour && board[i][col] == colour){
                    printf("\nthis is a valid position! (up&down)\nposition:%d %d", row, col);
                    return true;
                }
            }
        }    
    }else{ // in the direction of left or right
        for(int j = col + deltaCol; j < n && j > 0; j += deltaCol){
            if(board[row][j] == oppositeColour){
                hasOppositeColour = true;
            }
            if(hasOppositeColour && board[row][j] == colour){
                printf("\nthis is a valid position! (left&right)\nposition:%d %d", row, col);
                return true;
            }
        }
    }

    return false;             
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
    return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    // Complete your main function here
    int boardDemension;
    char board[26][26];
    char clearBuffer;

    printf("Enter the board dimension:");
    // scanf leaves newline in the buffer; solution is to put a whitespace before %
    scanf(" %d",&boardDemension);

    // initializes board
    initializeBoard(board, boardDemension);

    // prints board
    printBoard(board, boardDemension);

    printf("Enter board configuration:");
    char move[3];

    while(move[0] != '!' && move[1] != '!' && move[2] != '!'){
        scanf(" %c%c%c", &move[0], &move[1], &move[2]);
        printf("%c%c%c", move[0], move[1], move[2]);
        configureBoard(board, move);
    }

    // below for loops checks in all 8 direction
    for(int x = 0; x < boardDemension; x++){
        for(int y = 0; y < boardDemension; y++){
            if(board[x][y] == 'U'){ // only checks if the tile is not occupied
                for(int i = -1; i <= 1; i ++){
                    for(int j = -1; j <= 1; j ++){
                        if(!(i == 0 && j == 0)){
                            checkLegalInDirection(board, boardDemension, x, y, 'W', 1, 1);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
#endif // DO NOT DELETE THIS LINE