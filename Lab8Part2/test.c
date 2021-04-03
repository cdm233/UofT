#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



bool positionInBounds(int n, int row, int col) {
    (void)n;
    (void)row;
    (void)col;

    if(row < n && row >= 0 && col < n && col >= 0){
        return true;
    }
    return false;  
}

int makeMove1(const char board[26][26], int n, char turn, int *row, int *col, int *s) { // turn = W; n = 8
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
    *s = result[2];

    return 0;
}

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

void copyBoard(const char board[][26], char boardCopy[][26], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            boardCopy[i][j] = board[i][j];
        }
    }
}

void makeSmarterMove(const char board[26][26], int n, char turn, int *row, int *col){
    int result[3] = {}, highest = 0, lowestRow = n, lowestCol = n;
    char oppositeColour = turn == 'W' ? 'B' : 'W';
    // linkedList moves;
    // moves.head = NULL;

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
                                    // 2 steps ahead
                                    int nextRow, nextCol, nextScore, lanes;
                                    int details[8][3];
                                    char boardCopy[26][26];
                                    copyBoard(board, boardCopy, n);
                                    makeMove1(boardCopy, n, turn, &nextRow, &nextCol, &nextScore);
                                    checkValidMove(boardCopy, n, oppositeColour, col, row, &lanes, details);
                                    for(int i = 0; i < lanes; i++){
                                        flip(boardCopy, n, turn, row, col, details[i]);
                                    }
                                    makeMove1(boardCopy, n, turn, &nextRow, &nextCol, &nextScore);
                                    ori += nextScore;
                                    insertAtBack(&moves, row, col, ori);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    *row = result[0];
    *col = result[1];
}

int main(){
    return 0;
}