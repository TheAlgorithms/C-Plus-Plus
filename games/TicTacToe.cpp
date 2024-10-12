#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

char current_marker;
int current_player;
vector<char> board(9);

/**
 * @brief Draws the current state of the board.
 * @returns void
 */
void drawBoard() {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " \n";
}

/**
 * @brief Places the current marker on the board.
 * @param slot The position where the marker should be placed.
 * @returns bool True if the marker is placed successfully, false otherwise.
 */
bool placeMarker(int slot) {
    if(board[slot] != 'X' && board[slot] != 'O') {
        board[slot] = current_marker;
        return true;
    }
    return false;
}

/**
 * @brief Determines the winner of the game.
 * @returns int The current player if they are the winner, 0 otherwise.
 */
int winner() {
    // Check rows, columns, and diagonals
    for(int i = 0; i < 3; i++) {
        if(board[i*3] == board[i*3 + 1] && board[i*3 + 1] == board[i*3 + 2])
            return current_player;
        if(board[i] == board[i+3] && board[i+3] == board[i+6])
            return current_player;
    }
    if(board[0] == board[4] && board[4] == board[8])
        return current_player;
    if(board[2] == board[4] && board[4] == board[6])
        return current_player;
    return 0;
}

/**
 * @brief Swaps the current player and their marker.
 * @returns void
 */
void swapPlayerAndMarker() {
    current_marker = (current_marker == 'X') ? 'O' : 'X';
    current_player = (current_player == 1) ? 2 : 1;
}

/**
 * @brief Checks if the input is a number.
 * @param input The input string to check.
 * @returns bool True if the input is a number, false otherwise.
 */
bool is_number(const string& input) {
    return !input.empty() && all_of(input.begin(), input.end(), ::isdigit);
}

/**
 * @brief Asks the player for their slot input and validates it.
 * @param slot Reference to the slot variable to store the player's input.
 * @returns void
 */
void askData(int& slot) {
    string input;
    while(true) {
        cout << "It's player " << current_player << "'s turn. Enter your slot: ";
        cin >> input;
        if(is_number(input)) {
            slot = stoi(input);
            if(slot >= 1 && slot <= 9 && board[slot-1] != 'X' && board[slot-1] != 'O') {
                slot--;
                break;
            }
        }
        cout << "Invalid input! Try again.\n";
    }
}

/**
 * @brief Initializes the game board with default values.
 * @returns void
 */
void initBoard() {
    for(int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
}

int main() {
    initBoard();

    cout << "Player 1, choose your marker: ";
    char marker_p1;
    cin >> marker_p1;

    current_player = 1;
    current_marker = marker_p1;

    drawBoard();

    for(int i = 0; i < 9; i++) {
        int slot;
        askData(slot);

        placeMarker(slot);

        drawBoard();

        int player_won = winner();
        if(player_won == 1) {
            cout << "Player 1 won! Congrats!\n";
            break;
        }
        if(player_won == 2) {
            cout << "Player 2 won! Congrats!\n";
            break;
        }

        swapPlayerAndMarker();
    }

    cout << "It's a draw!\n";

    return 0;
}
