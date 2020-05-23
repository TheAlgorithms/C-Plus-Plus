#include <iostream>
#define n 4
#define inc_loop(var, start, stop) for (int var=start; var <= stop; var++)
#define dec_loop(var, start, stop) for (int var=start; var >= stop; var--)
void PrintSol(int Board[n][n]) {
    inc_loop(i, 0, n-1) {
        inc_loop(j, 0, n-1)
            std::cout << Board[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    if (n%2 == 0 || (n%2 == 1 && Board[n/2+1][0] != 1)) {
        inc_loop(i, 0, n-1) {
            dec_loop(j, n-1, 0)
                std::cout << Board[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

bool CanIMove(int Board[n][n], int row, int col) {
    /// check in the row
    inc_loop(i, 0, col-1) {
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
    inc_loop(i, 0, n-1) {
        if (CanIMove(Board, i, col)) {
            Board[i][col] = 1;
            NQueenSol(Board, col + 1);
            Board[i][col] = 0;
        }
    }
}

int main() {
    int Board[n][n] = {0};
    if (n%2 == 0) {
        inc_loop(i, 0, n/2-1) {
            if (CanIMove(Board, i, 0)) {
                Board[i][0] = 1;
                NQueenSol(Board, 1);
                Board[i][0] = 0;
            }
        }
    } else {
        inc_loop(i, 0, n/2) {
            if (CanIMove(Board, i, 0)) {
                Board[i][0] = 1;
                NQueenSol(Board, 1);
                Board[i][0] = 0;
            }
        }
    }
    return 0;
}
