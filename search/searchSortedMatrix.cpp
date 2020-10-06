/*
Program to search for a given number in a sorted 2D Array.A matrix is said to be sorted when it all the rows and columns are sorted
Time complexity- O(n+m) | Space Complexity- O(1)
*/
#include<bits/stdc++.h>
using namespace std;
void searchmatrix(int a[5][6],int check)
{
    int i=0;
    int j=6-1;
    while(i<5 && j>=0)
    {
        if(a[i][j]> check)
            j-=1;
        else if(a[i][j] < check)
            i+=1;
        else
        {
            cout<<"Position"<<endl;    
            cout<<"Row-"<<i<<" "<<"Column-"<<j<<endl;
            return;  
        }
              
    }
    cout<<"Number not found"<<endl; 
}
    
int main()
{
    int matrix[5][6]={{1,4,7,12,15,1000},{2,5,19,31,32,1001},{3,8,24,33,35,1002},{40,41,42,44,45,1003},{99,100,103,106,128,1004}};
    searchmatrix(matrix,44);
}
