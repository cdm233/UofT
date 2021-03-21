#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
 * Author:      APS105H1 Teaching Team
 * Modified by: * Derek Chen *
 *
 * Date: Jan 2021
 */

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========

void configureBoard(char board[][26], char move[3]);
void initializeBoard(char board[][26], int n);
void printValidMoves(char board[][26], int boardDemension, char colour);
void checkValidMove(char board[][26], int boardDemension, char colour, int, int, int *, int details[8][3]);
void flip(char board[][26], int boardDemension, char colour, int, int, int detail[3]);

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

void printValidMoves(char board[][26], int boardDemension, char colour){
    printf("Available moves for %c:\n", colour);
    // for loops used to iterate every tile of the board
    for(int x = 0; x < boardDemension; x++){
        for(int y = 0; y < boardDemension; y++){
            if(board[x][y] == 'U'){ // only checks if the tile is not occupied
                bool printed = false; // the same tile can only be printed once 
                for(int i = -1; i <= 1; i ++){
                    for(int j = -1; j <= 1; j ++){
                        if(!(i == 0 && j == 0)){ // deltaRow and deltaCol cannot both be 0
                            if(checkLegalInDirection(board, boardDemension, x, y, colour, i, j) && !printed){
                                printf("%c%c\n", 'a' + x, 'a' + y); // prints the coordinate in letter
                                printed = true;
                            }
                        }
                    }
                }
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
    bool adjacentOppositeColour = false; 

    // checks if the tile in the given direction is within the board
    if(!positionInBounds(n, row + deltaRow, col + deltaCol)){
        return false;
    }

    if(deltaRow != 0){
        // initializes the col index
        int j = col + deltaCol;

        // j needs to increase at the same time as i to unsure it's in the diagonal directgion
        for(int i = row + deltaRow; i < n && i > 0; i += deltaRow, j += deltaCol){ 
            if(deltaCol != 0){ // this is in the diagonal direction
                if(i == row + deltaRow && j == col + deltaCol){
                    // check if there is a immediate adjacent opposite colour in the given direction
                    if(board[i][j] == oppositeColour){ 
                        adjacentOppositeColour = true;
                    }else{ // if there is not then no need to continue
                        return false;
                    }
                }

                // the given direction is only valid if there is also a player's colour in the end
                if(board[i][j] == colour && adjacentOppositeColour){
                    return true;
                }
            }else{ // deltaCol == 0, this is in the direction of up and down
                if(i == row + deltaRow){
                    if(board[i][col] != oppositeColour){
                        return false;
                    }
                }
                if(board[i][col] == colour){
                    return true;
                }
            }
        }    
    }else{ // in the direction of left or right
        for(int j = col + deltaCol; j < n && j > 0; j += deltaCol){
            if(j == col + deltaCol){
                if(board[row][j] != oppositeColour){
                    return false;
                }
            }
            if(board[row][j] == colour){
                return true;
            }
        }
    }

    // just in case everything fails
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
    char board[26][26]; // board initialized as 26 by 26 static array

    printf("Enter the board dimension: ");
    // scanf leaves newline in the buffer; solution is to put a whitespace before %
    scanf(" %d",&boardDemension);

    // initializes board
    initializeBoard(board, boardDemension);

    // prints board
    printBoard(board, boardDemension);

    // board configuration entry phase
    printf("Enter board configuration:\n");
    char move[3];

    // // loop will terminate if all three inputs are '!'
    while(move[0] != '!' && move[1] != '!' && move[2] != '!'){
        scanf(" %c%c%c", &move[0], &move[1], &move[2]);
        configureBoard(board, move);
    }

    // prints board
    printBoard(board, boardDemension);

    // prints all avaliable moves for both players
    printValidMoves(board, boardDemension, 'W');
    printValidMoves(board, boardDemension, 'B');

    int row = 0, col = 0;

    int details[8][3], numberOfTargets = 0;
    int *num = &numberOfTargets;

    char currentPlayer = 'W';

    printf("Enter a move:");
    scanf(" %c%c%c", &currentPlayer, &col, &row);

    row = row - 'a'; 
    col = col - 'a'; 

    printf("\n");

   checkValidMove(board, boardDemension, currentPlayer, col, row, num, details);
    if(numberOfTargets != 0){
        printf("Valid move.\n");
        for(int i = 0; i < numberOfTargets; i++){
            flip(board, boardDemension, currentPlayer, row, col, details[i]);
        }
    }else{
        printf("Invalid move.\n");
    }
    printBoard(board, boardDemension);
    return 0;
}
#endif // DO NOT DELETE THIS LINE