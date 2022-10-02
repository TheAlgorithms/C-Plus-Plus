/* Warshall's Algorithm is used to determine the transitive closure of a directed graph or all paths in a directed graph by using the adjacency matrix. For this, it generates a sequence of n matrices. Where, n is used to describe the number of vertices. */
/* In this program, maximum value of nodes that can be taken under consideration is 10 (which is changeable) */
/* The time complexity of this algorithm is O(n^3) */

#include<iostream> //For IO Operations
using namespace std;

void Transitive_Closure(int Arr[10][10], int node);
void Print_Matrix(int A[10][10], int n);
int main()
{
    int n, i, j, ans;
    int Arr[10][10];
    cout << "\nEnter number of nodes (at most 10): ";
    cin >> n;
    cout << "\nType 1 if yes and 0 if no to the following questions. ";
    for(i=1; i<=n; i++) 
    {
      for(j=1; j<=n; j++)
      {
        cout<<"Is there a path from "<<i<<" to "<<j<<": ";
        cin>>ans;
        if(ans == 0)
        {
          Arr[i-1][j-1] = 0;
        }
        else if(ans == 1)
        {
          Arr[i-1][j-1] = 1;
        }
      }
    }
    cout<<"\nAdjacency matrix is: \n";
    Print_Matrix(Arr, n);
    Transitive_Closure(Arr, n);
    return 0;
}

//Finds Transitive Closure
void Transitive_Closure(int Arr[10][10], int node)
{
  int row, col, k;
  int Res[10][10];

  //Initializes matrix to zero
  for(row=0; row<node; row++)
  {
    for(col=0; col<node; col++) 
    {
      Res[row][col] = 0;
    }
  }
  for(k=0; k<node; k++)
  {
    for(row=0; row<node; row++) 
    {
      for(col=0; col<node; col++) 
      {
        if((Arr[row][col]==1)||(Arr[row][k]==1 && Arr[k][col]==1))
          {
            Res[row][col] = 1;
          }
      }
    }
  }
    cout<<"\nTransitive Closure: \n";
    Print_Matrix(Res, node);
    
    
}

//Prints Matrix
void Print_Matrix(int A[10][10], int n)
{
  int i, j;
  for(i=0; i<n; i++)
  {
    for(j=0; j<n; j++)
    {
      cout<<A[i][j]<<" ";
    }
    cout<<"\n";
  }
}
