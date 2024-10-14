#include <iostream>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];  // 3x3 Tic-Tac-Toe board

// Function to initialize the board
void initialize_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';  // Empty spaces on the board
        }
    }
}

// Function to display the current state of the board
void display_board() {
    cout << "Current Board:" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " |";
        }
        cout << endl;
        if (i < SIZE - 1) cout << "---|---|---" << endl;
    }
}

// Function to check if the given move is valid (i.e., the cell is empty)
bool is_valid_move(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ';
}

// Function to check for a win condition
bool check_win(char player) {
    // Check rows, columns, and diagonals for three matching symbols
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;  // Row check
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;  // Column check
    }
    // Diagonal checks
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

    return false;
}

// Function to check if the board is full (for a draw)
bool is_board_full() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Main game logic
void play_game() {
    initialize_board();
    char player = 'X';  // Player 1 starts with 'X'
    int row, col;

    while (true) {
        display_board();

        // Ask the current player to make a move
        cout << "Player " << player << "'s turn. Enter row (1-3) and column (1-3): ";
        cin >> row >> col;

        // Adjust for 0-indexed array
        row -= 1;
        col -= 1;

        if (!is_valid_move(row, col)) {
            cout << "Invalid move! Please try again." << endl;
            continue;
        }

        // Place the player's symbol on the board
        board[row][col] = player;

        // Check if the current player has won
        if (check_win(player)) {
            display_board();
            cout << "Congratulations! Player " << player << " wins!" << endl;
            break;
        }

        // Check if the board is full (draw)
        if (is_board_full()) {
            display_board();
            cout << "It's a draw!" << endl;
            break;
        }

        // Switch player for the next turn
        player = (player == 'X') ? 'O' : 'X';
    }
}

int main() {
    char choice;
    do {
        play_game();

        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing!" << endl;
    return 0;
}