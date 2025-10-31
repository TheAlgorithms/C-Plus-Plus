#include <iostream>
using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n-----------\n";
    }
    cout << "\n\n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    }
    return false;
}

int winner() {
    // Rows and Columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return current_player;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return current_player;
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return current_player;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return current_player;

    return 0;
}

void swapPlayerAndMarker() {
    if (current_marker == 'X') current_marker = 'O';
    else current_marker = 'X';

    current_player = (current_player == 1) ? 2 : 1;
}

void game() {
    cout << "Player 1, choose your marker (X or O): ";
    cin >> current_marker;
    current_player = 1;

    drawBoard();

    for (int i = 0; i < 9; i++) {
        cout << "Player " << current_player << ", enter your slot (1-9): ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid move. Try again.\n";
            i--;
            continue;
        }

        drawBoard();

        if (winner() != 0) {
            cout << "Player " << current_player << " wins!\n";
            return;
        }

        swapPlayerAndMarker();
    }

    cout << "It's a draw!\n";
}

int main() {
    game();
    return 0;
}
