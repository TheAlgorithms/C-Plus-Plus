/*
 *  Copyright : 2020 , MIT
 *  Author : Amit Kumar (offamitkumar)
 *  Created: May 23, 2020
 *  Last Modified: May 23, 2020
 *
 */
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::bitset;

class Solution {
    int ans;
    vector <string> board;
    int N;
    bitset <100> diagonalOne , diagonalTwo , column;
    bool isValid(int row , int col) {
        if (diagonalTwo.test(row-col+N-1) || diagonalOne.test(row+col)
                || column[col]) {
            return false;
        } else {
            return true;
        }
    }
    void checkArrangement(int row) {
        if (row == N) {
            ++ans;
            for (auto&itr : board) {
                cout << itr << '\n';
            }
            cout << '\n';
            return;
        }
        for (int i=0; i < N; ++i) {
            if (isValid(row , i)) {
                board[row][i] = 'Q';
                column.set(i);
                diagonalOne.set(row+i);
                diagonalTwo.set(row-i+N-1);
                checkArrangement(row+1);
                board[row][i] = '.';
                column.reset(i);
                diagonalOne.reset(row+i);
                diagonalTwo.reset(row-i+N-1);
            }
        }
    }

 public:
    int solveNQueens(int n) {
        ans = 0;
        N = n;
        diagonalTwo.reset();
        diagonalOne.reset();
        column.reset();
        board.resize(n , string(n , '.'));
        int row = 0 ; int col = 0;
        for (int i = 0; i < n; ++i) {
            board[0][i] = 'Q';
            column.set(i);
            diagonalOne.set(i);
            diagonalTwo.set(0-i+N-1);
            checkArrangement(1);
            board[0][i] = '.';
            column.reset(i);
            diagonalOne.reset(i);
            diagonalTwo.reset(0-i+N-1);
        }
        return ans;
    }
};

int main(void) {
    int n;
    cout << "Enter number of Queen: ";
    cin >> n;
    Solution s1;
    cout << "\nTotal Number of Ways: ";
    cout << s1.solveNQueens(n) << '\n';
    return 0;
}
