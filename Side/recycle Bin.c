/*
    if(deltaRow != 0){
        // initializes the col index
        int j = col + deltaCol;
        // j needs to increase at the same time as i to unsure it's in the diagonal directgion
        for(int i = row + deltaRow; i < n && i >= 0; i += deltaRow, j += deltaCol){ 
            if(deltaCol != 0){ // this is in the diagonal direction
                // the given direction is only valid if there is also a player's colour in the end
                if(board[i][j] == colour){
                    return number;
                }else{
                    number ++;
                }
            }else{ // deltaCol == 0, this is in the direction of up and down
                if(board[i][col] == colour){
                    return number;
                }else{
                    number ++;
                }
            }
        }    
    }else{ // in the direction of left or right
        for(int j = col + deltaCol; j < n && j >= 0; j += deltaCol){
            if(board[row][j] == colour){
                return number;
            }else{
                number ++;
            }
        }
    }
*/
/*
int number = 0;

    // initializes the col index
    int j = col + deltaCol;
    // j needs to increase at the same time as i to unsure it's in the diagonal directgion
    for(int i = row + deltaRow; i < n && i >= 0; i += deltaRow, j += deltaCol){ 
        if(deltaCol != 0){ // this is in the diagonal direction
            // the given direction is only valid if there is also a player's colour in the end
            if(board[i][j] == colour){
                return number;
            }else{
                number ++;
            }
        }
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
}*/