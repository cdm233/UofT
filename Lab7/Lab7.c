/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * You Name Here *
 *
 * Date: Jan 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
/* None for now */


// ========= Function implementation ==========
/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
    (void)board;
    (void)n;
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

    printf("Enter the board dimension:");
    scanf("%d",&boardDemension);
    
    char board[boardDemension + 1][boardDemension + 1];

    // initialize board
    char cRow = 'a', cCol = 'a';
    for(int i = 0;i < boardDemension + 1; i++){
        if(i != 0){
            board[i][0] = cRow;
            cRow ++;
        }
        for(int j = 0;j < boardDemension + 1; j++){
            if(i == 0){
                if(j == 0){
                    board[i][j] = ' ';
                }else{
                    board[i][j] = cCol;
                    cCol ++;
                }
            }else{
                if(j != 0){
                    board[i][j] = 'U';
                }
            }
            if(j == 0){
                printf("%c ",board[i][j]);
            }else{
                printf("%c",board[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}
#endif // DO NOT DELETE THIS LINE