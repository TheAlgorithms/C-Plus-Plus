/**
 * @file
 * @brief [Eight Queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle)
 * puzzle
 *
 * @details
 * The **eight queens puzzle** is the problem of placing eight chess queens on
 * an 8×8 chessboard so that no two queens threaten each other; thus, a solution
 * requires that no two queens share the same row, column, or diagonal. The
 * eight queens puzzle is an example of the more general **n queens problem** of
 * placing n non-attacking queens on an n×n chessboard, for which solutions
 * exist for all natural numbers n with the exception of n = 2 and n = 3.
 *
 * @author Unknown author
 * @author [David Leal](https://github.com/Panquesito7)
 *
 */
#include <array>
#include <iostream>

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
#include<iostream>
using namespace std;
bool isSafe(int** arr, int x, int y, int n){
    for(int row=0; row < x; row++){
        if(arr[row][y]==1){
            return false;
        }
    }
    int row = x;
    int col;
    while(row >= 0 && col >=0){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col--;
    }
    row = x;
    col = y;
    while(row >= 0 && col < n){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col++;
    }
    return true;
}
bool nQueen(int** arr, int x, int n){
    if(x >= n){
        return true;
    }
    for(int col=0; col < n; col++){
        if(isSafe(arr, x, col, n)){
            arr[x][col]=1;

            if(nQueen(arr, x+1, n)){
                return true;
            }
            arr[x][col] = 0;
        }
    }
    return false;
}
int main(){
    int n;
    cin>>n;
    int** arr=new int*[n];
    for(int i=0; i<n; i++){
        arr[i]=new int[n];
        for(int j=0; j<n; j++){
            arr[i][j]=0;
        }
    }
    if(nQueen(arr, 0, n)){
        for(int i=0; i<n; i++){

        for(int j=0; j<n; j++){
            cout<<arr[i][j]<<" "; 
        }cout<<endl;
        }
    }
    
    return 0;
}
