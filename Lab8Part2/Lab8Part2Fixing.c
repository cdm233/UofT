#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initializeBoard(char board[][26], int n);
void checkValidMove(char board[][26], int boardDemension, char colour, int, int, int *, int details[8][3]);
void flip(char board[][26], int boardDemension, char colour, int, int, int detail[3]);
int checkBoard(char board[][26], int boardDemension, char);
int numberToFlip(char board[][26], int, char, int, int, int, int);
int checkScore(char board[][26], int, char);

bool positionInBounds(int n, int row, int col) {
    (void)n;
    (void)row;
    (void)col;
 
    if(row < n && row >= 0 && col < n && col >= 0){
        return true;
    }
    return false;  
}

char oppose(char colour){
    return colour == 'W' ? 'B' : 'W';
}

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
                        // printf("?\n");
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
    int rrow = row, ccol = col;
    for(int i = 0; i < m; i++){
        // printf("row,col: %d%d\n", row, col);
        // printf("deltaRow, deltaCol: %d %d\n",details[i][0],details[i][1]);
        for(int j = 0; j <= details[i][2]; j++){ // i is deltaRow
            board[rrow + j*details[i][0]][ccol + j*details[i][1]] = turn;
        }
    }
}

typedef struct nodes{
    int row;
    int col;
    double score;
    struct nodes *link;
}node, nodePtr;

typedef struct lists{
    node *head;
}linkedList;

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

void copyBoard(const char src[][26], char des[][26], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            des[i][j] = src[i][j];
        }
    }
}

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

int tilesPlaces(const char board[][26], int n){
    int count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] != 'U'){
                count++;
            }
        }
    }
    return count;
}

double prediction(const char board[][26], int n, char turn, linkedList *moves){
    char oppositeColour = oppose(turn);
    if(tilesPlaces(board, n) > n*n-5){
        printf(" ");
    }
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col] == 'U'){
                int tilesToFlip = 0, totalTiles = 0;
                bool valid = false;
                for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
                    for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
                        if(!(deltaRow == 0 && deltaCol == 0)){
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

                                if(!positionInBounds(n, i + deltaRow, j + deltaCol)){
                                    tilesToFlip = 0;
                                }

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
                    insertAtFront(moves, row, col, (double) totalTiles);
                    totalTiles = 0;
                }
            }
        }
    }
}

void traverse(linkedList *moves, char colour){
    node *temp = moves->head;
    while (temp != NULL){
        linkedList predictedMoves;
        predictedMoves.head = NULL;
        char preColour = oppose(colour);
        // prediction();
    }
}

double highestScore(linkedList *list, int *preRow, int *preCol){
    double higest = -20.0;
    double preScore = 0.0;
    node *preTemp = list->head;
    while(preTemp != NULL){
        if(preTemp->score > higest){
            // printf("higest: %d, now: %d\n",higest, preTemp->score);
            *preRow = preTemp->row;
            *preCol = preTemp->col;
            preScore = preTemp->score;
            higest = preScore;
        }
        preTemp = preTemp->link;
    }
    return preScore;
}

double lowestScore(linkedList *list, int *preRow, int *preCol){
    double lowest = 100.0;
    double preScore = 0.0;
    node *preTemp = list->head;
    while(preTemp != NULL){
        if(preTemp->score < lowest){
            *preRow = preTemp->row;
            *preCol = preTemp->col;
            preScore = preTemp->score;
        }
    }
    return preScore;
}

void printList(linkedList *list){
    node *temp = list->head;
    int number = 0;
    while(temp != NULL){
        printf("%dth node: %c%c%lf\n", number, temp->row + 'a', temp->col + 'a', temp->score);
        number++;
        temp = temp->link;
    }
}

int makeMove1(const char board[26][26], int n, char turn, int *row, int *col) {
    char oppositeColour = oppose(turn);
    linkedList moves;
    moves.head = NULL;

    char boarCopy[26][26];

    prediction(board, n, turn, &moves); // produces base line

    if(tilesPlaces(board, n) < n * (n/4)){ // early game do corner
        node *temp1 = moves.head;
        int closest = 2*n;
        
        printf("early game\n");

        while (temp1 != NULL){
            if((temp1->row - 1) <= n/2 && (temp1->col - 1) <= n/2){
                if((temp1->row + temp1->col) < closest){
                    *row = temp1->row;
                    *col = temp1->col;
                }
            }else if(temp1->row > n/2 && (temp1->col - 1) <= n/2){
                if((n - temp1->row + temp1->col) < closest){
                    *row = temp1->row;
                    *col = temp1->col;
                }
            }else if((temp1->row - 1) <= n/2 && temp1->col > n/2){  
                if((temp1->row + n - temp1->col) < closest){
                    *row = temp1->row;
                    *col = temp1->col;
                }
            }else{
                if((n - temp1->row + n - temp1->col) < closest){
                    *row = temp1->row;
                    *col = temp1->col;
                }
            }
            temp1 = temp1->link;
        }
    }else{ // late game do tiles
        node *temp = moves.head;
        printf("valid moves:\n");
        printList(&moves);
        while (temp != NULL){
            copyBoard(board, boarCopy, n);
            // printf("now for %c%c\n", temp->row + 'a', temp->col + 'a');
            for(int step = 0; step < 7; step++){
                // printf("step%d:\n",step);
                // printBoard(boarCopy, n);

                // printf("placed at:\n");

                linkedList predictedMoves;
                predictedMoves.head = NULL;
                char preColour = oppose(turn);
                sFlip(boarCopy, n, turn, temp->row, temp->col);
                prediction(boarCopy, n, preColour, &predictedMoves);
                
                int preRow = 0, preCol = 0;
                double preScore = 0.0, higest = 0.0;

                preScore = highestScore(&predictedMoves, &preRow, &preCol);
                temp->score -= preScore;
                sFlip(boarCopy, n, preColour, preRow, preCol);

                // printf("%c %c%c\n", preColour, preRow + 'a', preCol + 'a');

                linkedList predictedMovesTurn;
                predictedMovesTurn.head = NULL;

                prediction(boarCopy, n, turn, &predictedMovesTurn);
                preScore = highestScore(&predictedMovesTurn, &preRow, &preCol);
                temp->score += preScore;
                // printf("%c %c%c\n", turn, preRow + 'a', preCol + 'a');

                sFlip(boarCopy, n, preColour, preRow, preCol);
            }
            printf("scored:%.2lf\n", temp->score);
            temp = temp->link;
        }
        // double s = highestScore(&moves, row, col);
        double higest = 0.0;
        double preScore = 0.0;
        node *preTemp = moves.head;
        while(preTemp != NULL){
            if(preTemp->score > higest){
                // printf("higest: %.2lf, now: %.2lf\n",higest, preTemp->score);
                *row = preTemp->row;
                *col = preTemp->col;
                preScore = preTemp->score;
                higest = preScore;
            }
            preTemp = preTemp->link;
        }
        // printf("final: %.2lf\n",preScore);
    }
}

// this function initializes the board and the initial four center tiles
void initializeBoard(char board[][26], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i + 1 == n/2){ // the upper middle row
                if(i * j == (n-2) * (n-2) / 4){
                    board[i][j] = 'B';
                }else if(i * j == ((n-2) / 2) * ((n-2) / 2 + 1)){
                    board[i][j] = 'W';
                }else{
                    board[i][j] = 'U';
                }
            }else if(i == n/2){ // the lower middle row
                if(i * j == ((n-2) / 2) * ((n-2) / 2 + 1)){
                    board[i][j] = 'W';
                }else if(i * j == ((n-2) / 2 + 1) * ((n-2) / 2 + 1)){
                    board[i][j] = 'B';
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

    for(int i = row + deltaRow, j = col + deltaCol; positionInBounds(n, i, j); i += deltaRow, j += deltaCol){
        if(i == row + deltaRow && j == col + deltaCol && board[i][j] != oppositeColour){ 
            return false;
        }

        if(board[i][j] == 'U'){
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
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) { // turn = W; n = 8
    (void)board;
    (void)n;
    (void)turn;
    (void)row;
    (void)col;

    int result[3] = {}, highest = 0, lowestRow = n, lowestCol = n;
    char oppositeColour = turn == 'W' ? 'B' : 'W';

    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col] == 'U'){
                int number = 0, ori = 0;
                for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
                    for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
                        if(!(deltaRow == 0 && deltaCol == 0)){ 
                            if(!positionInBounds(n, row + deltaRow, col + deltaCol)){ // passed this 
                                continue;
                            }
                            for(int i = row + deltaRow, j = col + deltaCol; positionInBounds(n, i, j); i += deltaRow, j += deltaCol){
                                if(i == row + deltaRow && j == col + deltaCol && board[i][j] != oppositeColour){ 
                                    break;
                                }
                                
                                if(board[i][j] == 'U'){
                                    number = 0;
                                    break;
                                }else if(board[i][j] == oppositeColour){
                                    number++;
                                }
                                if(board[i][j] == turn){
                                    ori += number;
                                    number = 0;
                                }
                            }
                        }
                    }
                }
                if(ori > highest){
                    result[0] = row;
                    result[1] = col;
                    result[2] = ori;
                    highest = ori;
                    lowestRow = row;
                    lowestCol = col;
                    continue;
                }else if(ori == highest){
                    if(row <= lowestRow){
                        if(col < lowestCol){
                            result[0] = row;
                            result[1] = col;
                            result[2] = ori;
                            highest = ori;
                            lowestRow = row;
                            lowestCol = col;
                            continue;
                        }
                    }
                }
            }
        }
    }

    *row = result[0];
    *col = result[1];

    return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    // Complete your main function here
    int boardDemension, gameFinished = false;
    char board[26][26], computerColour; // board initialized as 26 by 26 static array
    char currentPlayer = 'B';
    bool wPlayerNoMove = false;
    bool bPlayerNoMove = false;

    bool pass = true;

    linkedList possibleMoves;
    possibleMoves.head = NULL;

    printf("Enter the board dimension: ");
    // scanf leaves newline in the buffer; solution is to put a whitespace before %
    scanf(" %d",&boardDemension);

    printf("Computer plays (B/W) : ");
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
            if(currentPlayer == 'W'){
                wPlayerNoMove = true;
            }else{
                bPlayerNoMove = true;
            }
            if(bPlayerNoMove && wPlayerNoMove){
                gameFinished = true;
                continue;
            }
            currentPlayer = currentPlayer == 'B' ? 'W' : 'B';
            printf("%c player has no valid move.\n", currentPlayer);
            continue;
        }else if(checkBoard(board, boardDemension, currentPlayer) == -1){
            // if there is no space on board, ends game
            gameFinished = true;
            continue;
        }

        if(currentPlayer == computerColour){
            // if the current player is computer 
            makeMove(board, boardDemension, computerColour, &col, &row);
            printf("Computer1 places %c at %c%c.\n", currentPlayer, col + 'a', row + 'a');
            
            // printf("Enter move for colour %c (RowCol): ", currentPlayer);
            // scanf(" %c%c", &col, &row);

            // col = col - 'a';
            // row = row - 'a';
        }else{
            // makeMove(board, boardDemension, currentPlayer, &col, &row);
            int col1, row1;
            makeMove1(board, boardDemension, currentPlayer, &col, &row);
            // if(pass){
            //     makeMove1(board, boardDemension, currentPlayer, &col, &row);
            //     if(tilesPlaces(board, boardDemension) + 1 > boardDemension * (boardDemension/4)){
            //         pass = false;
            //     }
            // }else{
            //     printf("stop");
            //     scanf("%d%d",&row,&col);
            // }

            // printf("smarter places %c %c\n", col1 + 'a', row1 + 'a');
            printf("Computer2 places %c at %c%c.\n", currentPlayer, col + 'a', row + 'a');
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
        printf("%c player wins(%d:%d).", computerColour, score, boardDemension*boardDemension-score);
    }else if(score < boardDemension * boardDemension - score){
        printf("%c player wins(%d:%d).", computerColour == 'W' ? 'B' : 'W', score, boardDemension*boardDemension-score);
    }else{
        printf("tie.");
    }
    
    return 0;
}
#endif // DO NOT DELETE THIS LINE
/*
test case 1:
4
W
ba
ab
bd
da
dd
dc
ad
*/