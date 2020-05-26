/*A sparse matrix is a matrix which has number of zeroes greater than (m*n)/2,
where m and n are the dimensions of the matrix.*/
#include <iostream>
using namespace std;

int main()
{
  int m, n;
  int counterZeros = 0;
  cout << "Enter dimensions of matrix (seperated with space): ";
  cin >> m >> n;
  int a[m][n];
  cout << "Enter matrix elements:";
  cout << "\n";

  // reads the matrix from stdin
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << "element? ";
      cin >> a[i][j];
    }
  }

  // counts the zero's
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (a[i][j] == 0)
        counterZeros++; //Counting number of zeroes
    }
  }

  // makes sure the matrix is a sparse matrix
  if (counterZeros > ((m * n) / 2)) //Checking for sparse matrix
    cout << "Sparse matrix";
  else
    cout << "Not a sparse matrix";
}
