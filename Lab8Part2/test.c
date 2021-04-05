// #include "project_reversi_skeleton.h" // DO NOT modify this line
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

void sFlip(char board[][26], int n, char turn, int row, int col){
    char oppositeColour = turn == 'W' ? 'B' : 'W';
    int number = 0, m = 0;
    int details[8][3];
    for(int dr = -1; dr <= 1; dr ++){
        for(int dc = -1; dc <= 1; dc ++){
            if(!(dr == 0 && dc == 0)){
                if(!positionInBounds(n, row + dr, col + dc)){ // passed this 
                    continue;
                }
                if(dr == 1 && dc == 0){
                    printf(" ");
                }
                for(int i = row + dr, j = col + dc; positionInBounds(n, i, j); i += dr, j += dc){
                    if(i == row + dr && j == col + dc && board[i][j] != oppositeColour){ 
                        break;
                    }
                    
                    if(board[i][j] == 'U'){
                        break;
                    }else if(board[i][j] == oppositeColour){
                        number++;
                    }
                    if(board[i][j] == turn){
                        // printf("?\n");
                        details[m][0] = dr;
                        details[m][1] = dc;
                        details[m][2] = number;
                        m++;
                        break;
                    }
                }
            }
        }
    }
    for(int i = 0; i < m;i++){
        printf("%d %d\n",details[i][0],details[i][1]);
        for(int j = 0; j <= details[i][2]; j++){ // i is deltaRow
            board[row + j*details[i][0]][col + j*details[i][1]] = turn;
        }
    }
}

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

int main(){
    char b[26][26];
    int bd = 6;
    initializeBoard(b, bd);
    printBoard(b, bd);

    sFlip(b, bd, 'W', 1, 3);

    printBoard(b, bd);
    return 0;
}