/**
* @file
* @brief [Connect Four](https://en.wikipedia.org/wiki/Connect_Four)
*
* @details
* This is a user interactive Connect-Four game for two players.
* A board with 6 rows and 8 columns is displayed.
* Two players are assigned the symbols "x" and "o".
* They take turns to choose the column where their respective symbol can be inserted.
* A player wins when 4 spaces are connected continuously: Horizontally, Vertically, Diagonally Right, or Diagonally Left.
* The program declares the winner.
*
* @author [Arunabh Bhattacharya](https://github.com/arunabh-cloud)
*/
#include <iostream>   /// for IO operations
#include <array>     /// for std::array
using std::cout;
using std::cin;

const int COLS = 8;  /// The number of board columns is 8
const int ROWS = 6;  /// The number of the board rows is 6

/**
  * @details 
  * Method for printing the board with tokens or '-' if a space is yet to be chosen
  * @param board of dimension ROWS * COLS
  * @param ROWS is the vertical dimension of the board
  * @param COLS is the horizontal dimension of the board
  */
void printBoard(std::array<std::array<char, COLS>, ROWS>&board) {
    for (int i = ROWS - 1; i > -1; i--) {
        for (int j = 0; j < COLS; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
  * @details
  * Method for initializing and printing the board with "-"
  * @param board of dimension ROWS * COLS
  * @param ROWS is the vertical dimension of the board
  * @param COLS is the horizontal dimension of the board
  */
void initializeBoard(std::array<std::array<char, COLS>, ROWS>&board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '-';
        }
    }
    printBoard(board);
    std::cout << std::endl;
    std::cout << "Player 1: x\n";  ///  Assign the token 'x' to the Player 1 
    std::cout << "Player 2: o\n";  /// Assign the token 'o' to the Player 2 
    std::cout << std::endl;
}

/**
  * Play the game till there is a winner or till the game draws
  * @param board of dimension ROWS * COLS
  * @param ROWS is the vertical dimension of the board
  * @param COLS is the horizontal dimension of the board
  */
void playGame(std::array<std::array<char, COLS>, ROWS>&board){
    /// Initializing game variables
    int count = 1;     /// Counts each turn played till the board is full
    bool win = false;   /// Checks if there is a winner
    int num = 0;  /// Stores the player's number 1 or 2
    char token; /// Assigns 'x' or 'o' to the players 1 and 2 respectively
    while (!win && count <= ROWS * COLS) {
        int col = 0;  /// for column number chosen by the player
        int row = 0;  /// for row number selected by the program
        num = (count % 2 == 1) ? 1 : 2;
        token = (count % 2 == 1) ? 'x' : 'o';
        /// Asking for column option from players
        std::cout << "Player " << num << ": Enter a valid column number :  ";
        std::cin >> col;
        col -= 1;
        std::cout << std::endl;
        /// Checking if the player inputs an invalid column number
        while (col <= -1 || col >= COLS) {
            std::cout << "Please enter a valid index. ";
            std::cin >> col;
            col -= 1;
            std::cout << std::endl;
        }
        /// Checking for the highest available row
        while (board[row][col] != '-' && row < ROWS) {
            row++;
        }
        /// if a valid row is available replace and print the '-' with the token in the 2D array / board
        if (row != ROWS) {
            board[row][col] = token;
            printBoard(board);
            std::cout << std::endl;
            win = checkIfWinner(board, col, row, token);
            count++;
        }
    }
    /// Declaring the winner or if there is a draw
    if (count > ROWS * COLS && !win) {
        std::cout << "Draw. Nobody wins.\n";
    }
    else {
        std::cout << "Player " << num << " won the game!\n";
    }
}

/**
  * checkIfWinner function checks after every turn if a player is the winner
  * After a token is added, checks if the specified token / chip type creates four in a row
  * Horizontally, Vertically, Diagonally Right, Diagonally Left
  * @param board of dimension ROWS * COLS
  * @param ROWS is the vertical dimension of the board
  * @param COLS is the horizontal dimension of the board
  * @param col is the chosen column by the player
  * @param row is the valid row available in the chosen column
  * @param chipType is the token with the symbol 'x' or 'o' to match the neighbors
  * @returns 'win' = true, if a player has won
  * @returns 'win' = false, if no player has won
  */
bool checkIfWinner(std::array<std::array<char, COLS>, ROWS>&board, int col, int row, char chipType) {
    bool win = false;
    if(row >= 3) {
        if (board[row - 1][col] == chipType && board[row - 2][col] == chipType && board[row - 3][col] == chipType) {
            win = true;   // Connects the current token with 3 vertically below
        }
    }
    if(col <= COLS - 4) {
        if (board[row][col + 1] == chipType && board[row][col + 2] == chipType && board[row][col + 3] == chipType) {
            win = true;   // Connects the current token with 3 horizontally to its right
        }
    }
    if(col <= COLS - 3  && col >= 1) {
        if (board[row][col - 1] == chipType && board[row][col + 1] == chipType && board[row][col + 2] == chipType) {
            win = true;   // Connects the current token with 1 horizontally to its left and 2 horizontally to its right
        }
    }
    if(col <= COLS - 2  && col >= 2) {
        if (board[row][col - 2] == chipType && board[row][col - 1] == chipType && board[row][col + 1] == chipType) {
            win = true;   // Connects the current token with 2 horizontally to its left and 1 horizontally to its right
        }
    }
    if(col <= COLS - 1  && col >= 3) {
        if (board[row][col - 3] == chipType && board[row][col - 2] == chipType && board[row][col - 1] == chipType) {
            win = true;   // Connects the current token with 3 horizontally to its left
        }
    }
    if(row >= 3 && col <= COLS - 4) {
        if (board[row - 1][col + 1] == chipType && board[row - 2][col + 2] == chipType &&
            board[row - 3][col + 3] == chipType) {
            win = true;   // Connects the current token with 3 diagonally downward to its right
        }
    }
    if(row >= 3 && col <= COLS - 1  && col >= 3) {
        if (board[row - 1][col - 1] == chipType && board[row - 2][col - 2] == chipType &&
            board[row - 3][col - 3] == chipType) {
            win = true;   // Connects the current token with 3 diagonally downward to its left
        }
    }
    return win;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    using std::array;
    std::array<std::array<char, COLS>, ROWS> board{};
    initializeBoard(board);
    playGame(board);
    return 0;
}
