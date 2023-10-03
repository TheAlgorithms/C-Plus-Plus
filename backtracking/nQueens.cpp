#include<iostream>
using namespace std;

bool isSafe(int arr[][4],int x,int y,int n){

    // in column
    for(int i=0;i<n;i++){
        if(arr[i][y]==1){
            return false;
        }
    }
    // in row
    for(int j=0;j<n;j++){
        if(arr[x][j]==1){
            return false;
        }
    }

    int row = x;
    int col = y;
    
    //left diagonal
    while(row>=0 && col>=0){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col--;
    }
    
    row = x;
    col = y;
    
    
    // right diagonal
    while(row>=0 && col<n){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col++;
    }

    return true;
}

void printMatrix(int arr[][4],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[i][j] == 0)
                cout<<"_"<<" ";
            else
                cout<<"Q"<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

// row = starting row
bool nQueen(int arr[][4],int n,int row){

    // base case = if row > n ==> done
    if(row>=n){
        return true;
    }
    
    // columns - elements in a particular row
    for(int j=0;j<n;j++){
        for(int k=0;k<n;k++){
            arr[row][k]=0;
        }
        if(isSafe(arr,row,j,n)){
            arr[row][j]=1;
            
            printMatrix(arr,n);

            if(nQueen(arr,n,row+1)){
                return true;
            }

            arr[n][j]=0;   // backtracking
        }
    }

    return false;
}



int main(){

    int n = 4;

    int arr[4][4];

    // initializing all to 0
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            arr[i][j]=0;
        }
    }
    cout<<"\nSTEPS : \n";
    printMatrix(arr,n);

    for(int i=0;i<n;i++){
        // giving starting row i
        bool ans = nQueen(arr,n,i);

        if(ans){
            cout<<"\nSolution : \n\n";
            printMatrix(arr,n);
            break;
        }
        else{
            cout<<"Solution doesn't exist\n";
            printMatrix(arr,n);
            cout<<endl<<endl;
            break;
        }

    }
    return 0;
}
