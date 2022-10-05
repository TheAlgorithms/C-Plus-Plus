/**
* @file
* @brief Implementation of Warshall's Algorithm in C++
* [Warshall's Transitive Closure Algorithm](https://www.javatpoint.com/warshalls-algorithm)
* 
* @details
* Warshall's Algorithm is used to determine
* the transitive closure of a directed graph 
* or all paths in a directed graph by using the adjacency matrix. 
* For this, it generates a sequence of n matrices.
* Where, n is used to describe the number of vertices. 
*
* i.e.,
* R(0), ..., R(k-1), R(k), ... , R(n) 
*
* In this program, maximum value of nodes 
* that can be taken under consideration is 10
* (which is changeable)
*
* Reason: In Warshall's algo, Θ(n^3) is the worst-case cost.
* Even Brute Force method seems a viable option when compared
* to this. Therefore static 2D array is used with fixed
* input size of 10 inputs in this program in order to demonstrate
* the implementation and maintain responsiveness. 
*
* The time complexity of this algorithm is O(n^3)
*
* In order to generate R(k) from R(k-1),
* the following rules will be implemented:
*
* Rule 1: In row i and column j, 
* if the element is 1 in R(k-1), 
* then in R(k), it will also remain 1.
*
* Rule 2: In row i and column j,
* if the element is 0 in R(k-1), 
* then the element in R(k) will be changed to 1 
* iff the element in its column j and row k,
* and the element in row i and column k are both 1's in R(k-1). 
*
* The resulting matrix after following the steps n times and obtaining
* n number of matrices, the nth matrix is the transitive closure for
* the given adjacency matrix.
*
* @author [Abhilipsa Sahoo](https://github.com/abhilipsasahoo03)
*/


#include<iostream> //For IO Operations
#include<cassert> //For using assert()


/* Automating tests to check if the algorithm runs perfectly */
static void test()
{
  //Test 1
  int Arr1[10][10] = {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}};
  assert(Transitive_Closure(Arr1, 4) == 263);
  cout<<"\nTest 1 completed";

  //Test 2
  int Arr2[10][10] = {{0, 0, 1, 0}, {1, 0, 0, 1}, {0, 0, 0, 0}, {0, 1, 0, 0}};
  assert(Transitive_Closure(Arr2, 4) == 11565);
  cout<<"\nTest 2 completed";
  cout<<"\nAll tests completed successfully";

}

/* Finds Transitive Closure */
int Transitive_Closure(int Arr[10][10], int node)
{
  int row, col, k, sum=0, mul, prod=1;
  int val;
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
  
  /** Generating unique value that can be returned 
  * and mapped to unique transitive closure matrix
  */
  for(row=0; row<node; row++)
  {
    for(col=0; col<node; col++)
    {
      if(Res[row][col]==1)
      {
        mul = (row+1) * (col+1);
        sum = sum + mul;
        prod = prod * mul;
      }
    }
  }
  val = prod/sum;
  cout<<"\nTransitive Closure: \n";
  Print_Matrix(Res, node);
  cout<<"\nValue: "<<val;
  return val;  
}

/* Prints Matrix */
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

/* Main function */
int main()
{
    cout<<"\nInitializing tests...";
    test();
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

/** Example Output:
*
* Enter number of nodes (at most 10): 4
*
* Type 1 if yes and 0 if no to the following questions. Is there a path from 1 to 1: 1
* Is there a path from 1 to 2: 0
* Is there a path from 1 to 3: 0
* Is there a path from 1 to 4: 1
* Is there a path from 2 to 1: 0
* Is there a path from 2 to 2: 1
* Is there a path from 2 to 3: 1
* Is there a path from 2 to 4: 0
* Is there a path from 3 to 1: 0
* Is there a path from 3 to 2: 0
* Is there a path from 3 to 3: 0
* Is there a path from 3 to 4: 1
* Is there a path from 4 to 1: 0
* Is there a path from 4 to 2: 0
* Is there a path from 4 to 3: 0
* Is there a path from 4 to 4: 0
*
* Adjacency matrix is:
*
* 1 0 0 1
* 0 1 1 0
* 0 0 0 1
* 0 0 0 0
*
* Transitive Closure:
*
* 1 0 0 1
* 0 1 1 1
* 0 0 0 1
* 0 0 0 0
*
*/
