#include <iostream>
#include <vector>
#include <set>
using namespace std;

class NQueen{
    vector<vector<int> > board;
    set<int> column,main_diagonal,opposite_diagonal;
    void printSolution() {
        int N = board.size();
        cout << "\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << board[i][j]<<" ";
            cout << "\n";
        }
    }
    bool addParameters(int row,int col){
        if(column.find(col)!=column.end() 
            || main_diagonal.find(row-col)!=main_diagonal.end() 
            || opposite_diagonal.find(row+col)!=opposite_diagonal.end()){
            return false;
        }
        column.insert(col);
        main_diagonal.insert(row-col);
        opposite_diagonal.insert(row+col);
        return true;
    }
    void removeParameters(int row,int col){
        column.erase(col);
        main_diagonal.erase(row-col);
        opposite_diagonal.erase(row+col);
    }
    void _solveNQ(int row){
        if(row==board.size()){
            printSolution();
            return;
        }
        for(int i=0;i<board.size();i++){
            board[row][i] = 1;
            if(addParameters(row,i)){
                _solveNQ(row+1);
                removeParameters(row,i);
            }
            board[row][i] = 0;
        }
    }
public:
    void solveNQ(int size=8){
        board = vector<vector<int> >(size,vector<int>(size,0));
        column.clear();
        main_diagonal.clear();
        opposite_diagonal.clear();
        _solveNQ(0);
    }
};

int main()
{
    NQueen nqueen;
    nqueen.solveNQ(8);
    return 0;
}
