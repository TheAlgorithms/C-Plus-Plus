#include <iostream>
#define n 4

void PrintSol(int Board[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << Board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool CanIMove(int Board[n][n], int row, int col) {
    /// check in the row
    for (int i = 0; i < col; i++) {
        if (Board[row][i] == 1)
            return false;
    }
    /// check the first diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (Board[i][j] == 1)
            return false;
    }
    /// check the second diagonal
    for (int i = row, j = col; i <= n - 1 && j >= 0; i++, j--) {
        if (Board[i][j] == 1)
            return false;
    }
    return true;
}

void NQueenSol(int Board[n][n], int col) {
    if (col >= n) {
        PrintSol(Board);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (CanIMove(Board, i, col)) {
            Board[i][col] = 1;
            NQueenSol(Board, col + 1);
            Board[i][col] = 0;
        }
    }
}

int main() {
    int Board[n][n] = {0};
    NQueenSol(Board, 0);
}
