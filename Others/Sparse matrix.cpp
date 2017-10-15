/*A sparse matrix is a matrix which has number of zeroes greater than (m*n)/2,
where m and n are the dimensions of the matrix.*/
#include <iostream>
int main()
{
  int m,n,i,j,c=0;
  cout << "Enter dimensions of matrix:";
  cin >> m >> n;
  int a[m][n];
  cout << "Enter matrix elements:";
  for(i=0;<m;i++)
  {
    for(j=0;j<n;j++)
     cin >> a[i][j];
  }
  for(i=0;i<m;i++)
  {
    for(j=0;j<n;j++)
    {
      if(a[i][j]==0)
       c++; //Counting number of zeroes
    }
  }
  if(c>((m*n)/2)) //Checking for sparse matrix
   cout << "Sparse matrix";
  else
   cout << "Not a sparse matrix";
}
