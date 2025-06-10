/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printBoard (int size, char board [size][size]); 
void addChess (char configuration [3], int size, char board[size][size]); 
int checkPosition (int size, char board[size][size], char row, char col, char colour); 
void flip1 (int size, char board[size][size], char row, char col, char colour);
bool checkInLine (int size, char board[size][size], int row, int col, char colour, int deltaRow, int deltaCol); 
void flip2 (int size, char board[size][size], int row, int col, char colour, int deltaRow, int deltaCol);

void winner (int size, char board[size][size]);
void makeMove(int size, char board[size][size], char colour);
int availableYes (int size, char board[size][size], char colour); 

char alphabet [26] = "abcdefghijklmnopqrstuvwxyz"; 

int main()
{
    int countTurn = 4; 
    int size; 
    printf("Enter the board dimension: "); 
    scanf(" %d", &size);
    
    //initial board with user given size of the board 
    char board [size][size]; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == size / 2 - 1 && j == size / 2 - 1)
                board[i][j] = 'W'; 
            else if (i == size / 2 && j == size / 2)
                board[i][j] = 'W';
            else if (i == size / 2 && j == size / 2 - 1)
                board[i][j] = 'B';
            else if (i == size / 2 - 1 && j == size / 2)
                board[i][j] = 'B';
            else 
                board[i][j] = 'U'; 
        }
    }
    
    //get user input of the choice of computer's tile
    char choiceOfComputer; 
    printf("Computer plays (B/W) : "); 
    scanf(" %c", &choiceOfComputer); 
    
    printBoard(size, board); 
    
    /********************************************************************************
    -------------------------------------------------------------------------------code
    printBoard(size, board);
    -------------------------------------------------------------------------------code
    
    //board with configuration and therefore ready for user input turns 
    -------------------------------------------------------------------------------code
    char configuration [3]; 
    printf("Enter the board configuration: \n"); 
    while (1) {
        scanf("%3s", configuration);
        if (strcmp(configuration, "!!!") == 0){
            printBoard(size, board);
            break; 
        }
        else 
            addChess(configuration, size, board); 
    }
    -------------------------------------------------------------------------------code
    ********************************************************************************/
    
    //get user input, check validity, and act correspondingly
    char now = 'B'; 
    while (countTurn <= size * size) {
        if (now == choiceOfComputer){
            makeMove(size, board, now); 
            
        }
        
        else {
            if (availableYes(size, board, now) == 0)
                printf("%c player has no valid move\n", now); 
            else {
                char playerRow, playerCol; 
                printf("Enter move for player %c (RowCol): ", now); 
                scanf(" %c%c", &playerRow, &playerCol); 
                if (checkPosition(size, board, playerRow, playerCol, now) > 0) {
                    flip1(size, board, playerRow, playerCol, now); 
                    board[playerRow - 'a'][playerCol - 'a'] = now; 
                    printBoard(size, board); 
                }
                else {
                    printf("Invalid move.\n"); 
                    break; 
                }
            }
        }
        
        
        
        //detect whether the game is finished
        //1. board is full --------------->checked by while loop 
        //2. nobody have available moves
        now = (now == 'B') ? 'W' : 'B'; 
        countTurn++; 
    }
    
    //output winner
    winner(size, board); 
    
    return 0;
}

void printBoard (int size, char board [size][size]) {
    printf("  "); 
    for (int i = 0; i < size; i++) {
        printf("%c", alphabet[i]); 
    }
    printf("\n"); 
    
    for (int i = 0; i < size; i++) {
        printf("%c ", alphabet[i]); 
        for (int j = 0; j < size; j++) {
            printf("%c", board[i][j]); 
        }
        printf("\n"); 
    }
}

void addChess (char chess [3], int size, char board [size][size]) {
    char colour = chess[0]; 
    int row = chess[1] - 'a'; 
    int column = chess[2] - 'a'; 
    
    board[row][column] = colour; 
}

int checkPosition (int size, char board[size][size], char row, char col, char colour) {
    //check near by 
    int answer = 0; 
    if (board[row - 'a'][col - 'a'] == 'U'){
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
            for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                if (deltaRow == 0 && deltaCol == 0)
                    continue; 
                else {
                    //if tile is white, check is nearby tile is black
                    if (colour == 'W') {
                        if (row - 'a' + deltaRow >= 0 && row - 'a' + deltaRow < size && col - 'a' + deltaCol >= 0 && col - 'a' + deltaCol < size) {
                            if (board[row - 'a' + deltaRow][col - 'a' + deltaCol] == 'B') {
                                //keep checking this direction to see if it meets requirement 
                                if (checkInLine(size, board, row - 'a' + deltaRow, col - 'a' + deltaCol, colour, deltaRow, deltaCol) == true)
                                    answer++;  
                            }
                        }
                    }
                    else if (colour == 'B') {
                        if (row - 'a' + deltaRow >= 0 && row - 'a' + deltaRow < size && col - 'a' + deltaCol >= 0 && col - 'a' + deltaCol < size) {
                            if (board[row - 'a' + deltaRow][col - 'a' + deltaCol] == 'W') {
                                //keep checking this direction to see if it meets requirement 
                                if (checkInLine(size, board, row - 'a' + deltaRow, col - 'a' + deltaCol, colour, deltaRow, deltaCol) == true)
                                    answer++; 
                            }
                        }
                    }
                }
            }
        }
    }
    
    return answer; 
}

void flip1 (int size, char board[size][size], char row, char col, char colour) {
    //check near by 
    if (board[row - 'a'][col - 'a'] == 'U'){
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
            for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                if (deltaRow == 0 && deltaCol == 0)
                    continue; 
                else {
                    //if tile is white, check is nearby tile is black
                    if (colour == 'W') {
                        if (row - 'a' + deltaRow >= 0 && row - 'a' + deltaRow < size && col - 'a' + deltaCol >= 0 && col - 'a' + deltaCol < size) {
                            if (board[row - 'a' + deltaRow][col - 'a' + deltaCol] == 'B') {
                                //keep checking this direction to see if it meets requirement 
                                if (checkInLine(size, board, row - 'a' + deltaRow, col - 'a' + deltaCol, colour, deltaRow, deltaCol) == true)
                                    flip2(size, board, row - 'a' + deltaRow, col - 'a' + deltaCol, colour, deltaRow, deltaCol); 
                            }
                        }
                    }
                    else if (colour == 'B') {
                        if (row - 'a' + deltaRow >= 0 && row - 'a' + deltaRow < size && col - 'a' + deltaCol >= 0 && col - 'a' + deltaCol < size) {
                            if (board[row - 'a' + deltaRow][col - 'a' + deltaCol] == 'W') {
                                //keep checking this direction to see if it meets requirement 
                                if (checkInLine(size, board, row - 'a' + deltaRow, col - 'a' + deltaCol, colour, deltaRow, deltaCol) == true)
                                    flip2(size, board, row - 'a' + deltaRow, col - 'a' + deltaCol, colour, deltaRow, deltaCol); 
                            }
                        }
                    }
                }
            }
        }
    }
}

bool checkInLine (int size, char board[size][size], int row, int col, char colour, int deltaRow, int deltaCol) {
    while (row < size && col < size && row >= 0 && col >= 0) {
        if (board[row][col] == colour)
            return true;
        else if (board[row][col] == 'U')
            return false; 
        row += deltaRow; 
        col += deltaCol; 
    }
    
    return false; 
}

void flip2 (int size, char board[size][size], int row, int col, char colour, int deltaRow, int deltaCol) {
    while (board[row][col] != colour) {
        board[row][col] = colour; 
        row += deltaRow; 
        col += deltaCol; 
    }
}

void winner (int size, char board[size][size]) {
    int Bcount = 0, Wcount = 0; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 'W')
                Wcount++; 
            else if (board[i][j] == 'B') 
                Bcount++; 
        }
    }
    
    if (Bcount > Wcount)
        printf("B player wins.");  
    else if (Bcount < Wcount)
        printf("W player wins."); 
    else 
        printf("Draw"); 
}

//construct computer logic for making moves: 
//1. check all the available moves 
//2. while checking, also distinguish the "score" of the each available move 
//3. eventually use the highest score move (lowest row and column move found ----------------> change when greater than)
void makeMove (int size, char board[size][size], char colour) {
    int score = 0; 
    char moveRow, moveCol; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (checkPosition(size, board, 'a' + i, 'a' + j, colour) > score) {
                score = checkPosition(size, board, 'a' + i, 'a' + j, colour); 
                moveRow = 'a' + i; 
                moveCol = 'a' + j;
            }
        }
    }
    
    if (score == 0) {
        printf("%c player has no valid move\n", colour); 
    }
    else {
        flip1(size, board, moveRow, moveCol, colour);
        board[moveRow - 'a'][moveCol - 'a'] = colour;
        printf("Computer palces %c at %c%c.\n", colour, moveRow, moveCol);
        printBoard(size, board); 
    }
}

int availableYes (int size, char board[size][size], char colour) {
    int count = 0; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (checkPosition(size, board, 'a' + i, 'a' + j, colour) > 0) 
                count++; 
        }
    }
    
    return count; 
}