/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

//lack of available moves for black tile with size of 6 !!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printBoard (int size, char board [size][size]); 
void addChess (char configuration [3], int size, char board[size][size]); 
void checkPosition (int size, char board[size][size], char row, char col, char colour); 
bool checkInLine (int size, char board[size][size], int row, int col, char colour, int deltaRow, int deltaCol); 

char alphabet [26] = "abcdefghijklmnopqrstuvwxyz"; 

int main()
{
    int size; 
    printf("Enter the board dimension: "); 
    scanf("%d", &size);
    
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
    printBoard(size, board); 
    
    //board with configuration and therefore ready for user input turns 
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
    
    char colour; 
    //output all possible moves for both black and white tile players 
    printf("Available moves for W: \n"); 
    colour = 'W'; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            checkPosition(size, board, 'a' + i, 'a' + j, colour); 
        }
    }
    printf("Available moves for B: \n"); 
    colour = 'B'; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            checkPosition(size, board, 'a' + i, 'a' + j, colour); 
        }
    }
    
    //get user input, check validity, and act correspondingly
    printf("Enter a move: \n"); 
    char turns [3]; 
    scanf("%3s", turns); 
    
    
    
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

void checkPosition (int size, char board[size][size], char row, char col, char colour) {
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
                                    printf("%c%c\n", row, col); 
                            }
                        }
                    }
                    else if (colour == 'B') {
                        if (row - 'a' + deltaRow >= 0 && row - 'a' + deltaRow < size && col - 'a' + deltaCol >= 0 && col - 'a' + deltaCol < size) {
                            if (board[row - 'a' + deltaRow][col - 'a' + deltaCol] == 'W') {
                                //keep checking this direction to see if it meets requirement 
                                if (checkInLine(size, board, row - 'a' + deltaRow, col - 'a' + deltaCol, colour, deltaRow, deltaCol) == true)
                                    printf("%c%c\n", row, col); 
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