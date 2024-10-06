#include <iostream>
using namespace std;



char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;




void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    } else {
        return false;
    }
}


int winner() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return current_player;
    }

    // Columns
    for (int i = 0; i < 3; i++) {
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

    if (current_player == 1) current_player = 2;
    else current_player = 1;
}




void game() {
    cout << "Player 1, choose your marker: X or O: ";
    char marker_p1;
    cin >> marker_p1;

    current_player = 1;
    current_marker = marker_p1;

    drawBoard();

    int player_won;

    for (int i = 0; i < 9; i++) {
        cout << "It's player " << current_player << "'s turn. Enter your slot: ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid move, try again.\n";
            i--;
            continue;
        }

        drawBoard();
        player_won = winner();

        if (player_won == 1) { cout << "Player 1 wins!\n"; break; }
        if (player_won == 2) { cout << "Player 2 wins!\n"; break; }

        swapPlayerAndMarker();
    }

    if (player_won == 0) cout << "It's a tie!\n";
}

int main() {
    bool yorn=true;
    while(yorn){
        cout<<"Do you want to play?"<<"\n Y/N"<<endl;
        char ch;
        cin>>ch;
        if(ch=='Y'){
            yorn==true;
        }
        else{
            yorn==false;
            break;
        }
        game();   
    }
    return 0;
}