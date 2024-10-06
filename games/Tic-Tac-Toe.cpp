#include <iostream>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];
char currentPlayer = 'X';

// Function to initialize the board
void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '1' + i * SIZE + j; // Assign numbers 1-9 to the board
        }
    }
}

// Function to display the board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Function to check if a move is valid
bool isValidMove(int row, int col) {
    return board[row][col] != 'X' && board[row][col] != 'O';
}

// Function to check for a win
bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}

// Function to check for a draw
bool checkDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return false;
        }
    }
    return true;
}

// Function to toggle the current player
void togglePlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Function to play the game
void playGame() {
    int row, col, move;
    bool gameWon = false, gameDraw = false;

    initializeBoard();

    while (!gameWon && !gameDraw) {
        displayBoard();
        cout << "Player " << currentPlayer << "'s turn. Enter the number of your move: ";
        cin >> move;

        // Calculate the row and column from the move
        row = (move - 1) / SIZE;
        col = (move - 1) % SIZE;

        // Validate move
        if (move < 1 || move > 9 || !isValidMove(row, col)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        // Make the move
        board[row][col] = currentPlayer;

        // Check for win or draw
        gameWon = checkWin();
        gameDraw = checkDraw();

        if (!gameWon && !gameDraw) {
            togglePlayer();
        }
    }

    displayBoard();

    if (gameWon) {
        cout << "Player " << currentPlayer << " wins!\n";
    } else {
        cout << "It's a draw!\n";
    }
}

// Main function to handle restarting or exiting the game
int main() {
    char choice;
    do {
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
