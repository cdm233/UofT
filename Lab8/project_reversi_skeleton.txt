/*
 * File:        Lab8Part1.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * Derek Chen *
 *
 * Date: March 20, 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========

// linked list for moves' data
typedef struct nodes{
    int row;
    int col;
    int score;
    struct nodes *link;
}node, nodePtr;

typedef struct lists{
    node *head;
}linkedList;

void initializeBoard(char board[][26], int);
int checkScore(char board[][26], int, char);
int checkBoard(char board[][26], int, char);
char oppose(char);
bool checkValidMove(char board[][26], int, char, int, int);
bool insertAtFront(linkedList *list, int row, int col, double score);
node *createNode(int row, int col, double score);
void sFlip(char board[][26], int n, char turn, int row, int col);

// this function creates a node 
node *createNode(int row, int col, double score){
    node *new = (node*) malloc(sizeof(node));
    if(new != NULL){
        new->row = row;
        new->col = col;
        new->score = score;
        new->link = NULL;
    }
    return new;
}

// this function inserts a node at the front of the given LL
bool insertAtFront(linkedList *list, int row, int col, double score){
    if(list->head == NULL){
        list->head = createNode(row, col, score);
        return list->head != NULL;
    }
    node *temp = createNode(row, col, score);
    if(temp == NULL){
        return false;
    }

    temp->link = list->head;
    list->head = temp;
    
    return true;
}

// this function initializes the board
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

// this function checks the final score of the game for the computer
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

// this function checks the states of the board
int checkBoard(char board[][26], int n, char turn){
    bool hasSpace = false, hasValidMoves = false, checked = false;
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col] == 'U'){
                hasSpace = true;
                for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
                    for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
                        if(!checked){
                            hasValidMoves = checkLegalInDirection(board, n, row, col, turn, deltaRow, deltaCol);
                            if(hasValidMoves){
                                checked = true;
                            }
                        }
                    }
                }
            }
        }
    }
    if(!hasSpace){
        return -1;
    }
    if(!hasValidMoves){
        return 0;
    }else{
        return 1;
    }
}

// this function returns the opposite colour of the given
char oppose(char colour){
    return colour == 'W' ? 'B' : 'W';
}

// this function flips the board according to the given coordinate
void sFlip(char board[][26], int n, char turn, int row, int col){
    char oppositeColour = turn == 'W' ? 'B' : 'W';
    int m = 0;
    int details[8][3];
    for(int dr = -1; dr <= 1; dr ++){
        for(int dc = -1; dc <= 1; dc ++){
            if(!(dr == 0 && dc == 0)){
                int number = 0;
                if(!positionInBounds(n, row + dr, col + dc)){ // passed this 
                    continue;
                }
                for(int i = row + dr, j = col + dc; positionInBounds(n, i, j); i += dr, j += dc){
                    if(i == row + dr && j == col + dc && board[i][j] != oppositeColour){ 
                        number = 0;
                        break;
                    }
                    
                    if(board[i][j] == 'U'){
                        number = 0;
                        break;
                    }else if(board[i][j] == oppositeColour){
                        number++;
                    }
                    if(board[i][j] == turn){
                        details[m][0] = dr;
                        details[m][1] = dc;
                        details[m][2] = number;
                        number = 0;
                        m++;
                        break;
                    }
                }
            }
        }
    }
    // sometimes memory leaks, this is back up
    int rrow = row, ccol = col;
    for(int i = 0; i < m; i++){
        for(int j = 0; j <= details[i][2]; j++){ // i is deltaRow
            board[rrow + j*details[i][0]][ccol + j*details[i][1]] = turn;
        }
    }
}

// this function checks if the move is valid
bool checkValidMove(char board[][26], int n, char turn, int row, int col){
    bool checked = false, hasValidMoves = false;
    for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
        for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
            if(!(deltaRow == 0 && deltaCol == 0)){
                if(!checked){
                    hasValidMoves = checkLegalInDirection(board, n, row, col, turn, deltaRow, deltaCol);
                    if(hasValidMoves){
                        checked = true;
                    }
                }
            }
        }
    }
    return hasValidMoves;
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

    if(row < n && row >= 0 && col < n && col >= 0){
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
    char oppositeColour = oppose(colour);

    if(!positionInBounds(n, row + deltaRow, col + deltaCol)){
        return false;
    }
    for(int i = row + deltaRow, j = col + deltaCol; positionInBounds(n, i, j); i += deltaRow, j += deltaCol){
        if(i == row + deltaRow && j == col + deltaCol && board[i][j] != oppositeColour){ 
            return false;
        }
        if(board[i][j] == 'U'){
            return false;
        }

        if(!positionInBounds(n, i, j)){
            return false;
        }

        if(board[i][j] == colour){
            return true;
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
    
    char oppositeColour = oppose(turn);
    linkedList moves;
    moves.head = NULL;

    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col] == 'U'){
                int tilesToFlip = 0, totalTiles = 0;
                bool valid = false;
                for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
                    for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
                        if(!(deltaRow == 0 && deltaCol == 0)){
                            // if it's not in board, continue next loop
                            if(!positionInBounds(n, row + deltaRow, col + deltaCol)){
                                continue;
                            }

                            for(int i = row + deltaRow, j = col + deltaCol; positionInBounds(n, i, j); i += deltaRow, j += deltaCol){
                                if(i == row + deltaRow && j == col + deltaCol && board[i][j] != oppositeColour){ 
                                    tilesToFlip = 0;
                                    break;
                                }
                                if(board[i][j] == 'U'){
                                    tilesToFlip = 0;
                                    break;
                                }else if(board[i][j] == oppositeColour){
                                    tilesToFlip ++;
                                }

                                if(!positionInBounds(n, i, j)){
                                    tilesToFlip = 0;
                                }

                                // if the tile on board is the same colour as turn, it's a valid move
                                if(board[i][j] == turn){
                                    totalTiles += tilesToFlip;
                                    tilesToFlip = 0;
                                    valid = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if(valid){
                    // if this tile is valid, push data to LL
                    insertAtFront(&moves, row, col, totalTiles);
                    totalTiles = 0;
                }
            }
        }
    }
    node *temp = moves.head;
    int lowestRow = n, lowestCol = n;
    int highest = 0;

    // the following loop will set row and col accordingly
    while(temp != NULL){
        if(temp->score > highest){
            highest = temp->score;
            lowestRow = temp->row;
            lowestCol = temp->col;

            *row = temp->row;
            *col = temp->col;
        }else if(temp->score == highest){
            if(temp->row < lowestRow){
                lowestRow = temp->row;
                lowestCol = temp->col;
                
                *row = temp->row;
                *col = temp->col;
            }else if(temp->row == lowestRow){
                if(temp->col < lowestCol){
                    lowestCol = temp->col;
                    
                    *row = temp->row;
                    *col = temp->col;
                }
            }
        }
        temp = temp->link;
    }
    return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    // Complete your main function here
    int boardDimension, gameFinished = false;
    char board[26][26], computerColour; // board initialized as 26 by 26 static array
    char currentPlayer = 'B';
    bool wPlayerNoMove = false, bPlayerNoMove = false;

    printf("Enter the board dimension: ");
    // scanf leaves newline in the buffer; solution is to put a whitespace before %
    scanf(" %d",&boardDimension);

    printf("Computer plays (B/W) : ");
    scanf(" %c", &computerColour);

    // initializes board
    initializeBoard(board, boardDimension);

    // prints board
    printBoard(board, boardDimension);

    while(!gameFinished){
        int row, col;
        int result = checkBoard(board, boardDimension, currentPlayer);
        if(result == 0){
            if(currentPlayer == 'W'){
                wPlayerNoMove = true;
            }else{
                bPlayerNoMove = true;
            }
            printf("%c player has no valid move.\n", currentPlayer);
            // if both player has no move, the game ends
            if(wPlayerNoMove && bPlayerNoMove){
                gameFinished = true;
                continue;
            }
            currentPlayer = oppose(currentPlayer);
            continue;
        }else if(result == -1){
            // if there is no more space, the game ends
            gameFinished = true;
            continue;
        }

        if(currentPlayer == computerColour){
            makeMove(board, boardDimension, currentPlayer, &row, &col);
            printf("Computer places %c at %c%c.\n", currentPlayer, row + 'a', col + 'a');
        }else{
            printf("Enter move for colour %c (RowCol): ", currentPlayer);
            scanf(" %c%c", &row, &col);

            row = row - 'a';
            col = col - 'a';
        }

        if(checkValidMove(board, boardDimension, currentPlayer, row, col)){
            sFlip(board, boardDimension, currentPlayer, row, col);
        }else{
            // if the user input is invalid, the game ends and computer wins
            printf("Invalid move.\n");
            gameFinished == true;
            printf("%c player wins.", oppose(currentPlayer));
            return 0;
        }
        
        printBoard(board, boardDimension);

        // switch player
        currentPlayer = oppose(currentPlayer);
    }

    // calculate score of computer
    int score = checkScore(board, boardDimension, computerColour);

    if(score > boardDimension * boardDimension - score){
        printf("%c player wins.", computerColour);
    }else if(score < boardDimension * boardDimension - score){
        printf("%c player wins.", computerColour == 'W' ? 'B' : 'W');
    }else{
        printf("tie.");
    }
    return 0;
}
#endif // DO NOT DELETE THIS LINE