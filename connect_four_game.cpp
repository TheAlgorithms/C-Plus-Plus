/**
* @file
* @brief [Connect Four](https://en.wikipedia.org/wiki/Connect_Four) 
* 
* @details 
* This is a user interactive Connect-Four game for two players.
* A board with 6 rows and 8 columns is displayed.
* Two players are assigned the symbols "x" and "o".
* They take turns to choose the column where their respective symbol can be inserted.
* A player wins when 4 spaces are connected continously: Horizontally, Vertically, Diagonally Forward, or Diagonally Backward.
* The program declares the winner.
*
* @Connect Four trademark Milton Bradley, 1974
* @author [Arunabh Bhattacharya](https://github.com/arunabh-cloud)
*
*/
#include <iostream>
using namespace std;

// Global constants COLS and ROWS for the standard (row * column) 2D game board 
const int COLS = 8;
const int ROWS = 6;

// Function prototypes 
void printBoard(char [][COLS], int);
void initializeBoard(char [][COLS], int);
int insertChip(char [][COLS], int, int &, char);
bool checkIfWinner(char [][COLS], int, int, char);

/**
 * @brief Main function 
 * @returns 0 on exit 
 */
int main() {

    /**
     * Set up the 2D array for the game board 
     * @param array of dimension ROWS * COLS
     * @param ROWS is the vertical dimension of the board 
     * @param COLS is the horizontal dimension of the board 
     * initialize the board with "-" 
     * print the board 
     */
    
    char array[ROWS][COLS];
    initializeBoard(array, ROWS);
    printBoard(array, ROWS);
    cout << endl;

    // Tell the players about the tokens 'x' and 'o'  
    cout << "Player 1: x\n";
    cout << "Player 2: o\n";
    cout << endl;

    // Initializing game variables
    int count = 1;     // Counts each turn played till the board is full    
    bool win = false;     // Checks if there is a winner 
    int num;     // Stores the player numbers 1 and 2   
    char token;    // Assigns 'x' or 'o' to the players 1 and 2 respectively  

    // Setting the game in the while loop till there is a winner or a draw
    // Asking for column option from players
    
    while (!win && count <= (ROWS * COLS)) {
        int col;
        num = (count % 2 == 1) ? 1 : 2;
        token = (count % 2 == 1) ? 'x' : 'o';
        cout << "Player " << num << ": Which column would you like to choose?  ";
        cin >> col;
        col -= 1;
        cout << endl;
        
        // Checking if the player inputs an invalid column number 
        while (col <= -1 || col >= COLS) {
            cout << "Please enter a valid index. ";
            cin >> col;
            col -= 1;
            cout << endl;
        }
        
         /**
          * insertChip function finds the next available row for the player    
          * @param array of dimension ROWS * COLS
          * @param ROWS is the vertical dimension of the board
          * @param col is the chosen column by the player 
          * @returns 'row', the row number that is available for the token to be placed 
          * Replace the '-' with the token in the 2D array / board
          * print the board 
          */
        
        int row = insertChip(array, ROWS, col, token);
        printBoard(array, ROWS);
        cout << endl;
        
        /**
          * checkIfWinner function checks after every turn if a player is the winner     
          * @param array of dimension ROWS * COLS
          * @param col is the chosen column by the player 
          * @param row is the row returned from the insertChip function 
          * @param token is the symbol 'x' or 'o' to match the neighbors 
          * @returns 'win' = true, if a player has won
          * @returns 'win' = false, if no player has won
          */
        win = checkIfWinner(array, col, row, token);
        
        count++;
    }

    // Declaring the winner or if there is a draw
    if (count > ROWS * COLS && !win)
        cout << "Draw. Nobody wins.\n";
    else
        cout << "Player " << num << " won the game!\n";

    return 0;
}

// Method for printing the board with tokens or '-' if a space is yet to be chosen 
void printBoard(char array[][COLS], int rows) {
    for (int i = rows - 1; i > -1; i--) {
        for (int j = 0; j < COLS; j++)
            cout << array[i][j] << " ";
        cout << endl;
    }
}


// Method for initializing the board with "-"
 void initializeBoard(char array[][COLS], int rows) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < COLS; j++)
            array[i][j] = '-';

}

 /**
   * insertChip function finds the next available row for the player    
   * @param array of dimension ROWS * COLS
   * @param COLS is the horizontal dimension of the board 
   * @param rows is total the number of rows in the board
   * @param col is the chosen column by the player 
   * @param chipType is the token inserted in the selected column and row 
   * @returns 'row', the row number that is available for the token
   */

int insertChip(char array[][COLS], int rows, int &col, char chipType) {
    int row = 0;
    while (array[row][col] != '-' )
        row++;
    while (row == rows) {
        // If the column is already full then the player is asked to choose another column 
        cout << "Column already filled. Enter another column. ";
        cin >> col;
        col = col - 1;
        cout << endl;
        while (col <= -1 || col >= COLS) {
            cout << "Please enter a valid index. ";
            cin >> col;
            cout << endl;
        }
        row = 0;
        while (array[row][col] != '-' )
            row++;
    }
    array[row][col] = chipType;
    return row;
}

 /**
   * checkIfWinner function checks after every turn if a player is the winner     
   * @param array of dimension ROWS * COLS
   * @param col is the chosen column by the player 
   * @param row is the row returned from the insertChip function 
   * @param chipType is the token with the symbol 'x' or 'o' to match the neighbors 
   * @returns 'win' = true, if a player has won
   * @returns 'win' = false, if no player has won
   */

bool checkIfWinner(char array[][COLS], int col, int row, char chipType) {
    
    bool win = false;
    
    // After a token is added, checks if the specified token / chip type creates four in a row
    // Horizontally, Vertically, Diagonally Right, Diagonally Left
    
    if(row >= 3)
        if(array[row - 1][col] == chipType && array[row - 2][col] == chipType && array[row - 3][col] == chipType)
            win = true;   // Connects the current token with 3 vertically below 
   
    if(col <= COLS - 4)
        if(array[row][col + 1] == chipType && array[row][col + 2] == chipType && array[row][col + 3] == chipType)
            win = true;   // Connects the current token with 3 horizontally to its right 
   
    if(col <= COLS - 3  && col >= 1)
        if(array[row][col - 1] == chipType && array[row][col + 1] == chipType && array[row][col + 2] == chipType)
            win = true;   // Connects the current token with 1 horizontally to its left and 2 horizontally to its right 
    
    if(col <= COLS - 2  && col >= 2)
        if(array[row][col - 2] == chipType && array[row][col - 1] == chipType && array[row][col + 1] == chipType)
            win = true;   // Connects the current token with 2 horizontally to its left and 1 horizontally to its right 
   
    if(col <= COLS - 1  && col >= 3)
        if(array[row][col - 3] == chipType && array[row][col - 2] == chipType && array[row][col - 1] == chipType)
            win = true;   // Connects the current token with 3 horizontally to its left 
   
    if(row >= 3 && col <= COLS - 4)
        if(array[row - 1][col + 1] == chipType && array[row - 2][col + 2] == chipType && array[row - 3][col + 3] == chipType)
            win = true;   // Connects the current token with 3 diagonally downward to its right  
   
    if(row >= 3 && col <= COLS - 1  && col >= 3)
        if(array[row - 1][col - 1] == chipType && array[row - 2][col - 2] == chipType && array[row - 3][col - 3] == chipType)
            win = true;   // Connects the current token with 3 diagonally downward to its left 
   
    return win;
}

