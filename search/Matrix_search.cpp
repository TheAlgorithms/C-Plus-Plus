#include <iostream>
#include<algorithm>
using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    
    // input array
    int  arr[n][m];
    for(int i=0;i<n;i++)
     {
         for(int j=0;j<m;j++)
         cin>>arr[i][j];

     }
    // input key to be searched
      int key;
      cin>>key;

  int a,b;
  //for matching rows
  a=0;
  //for columns
  b=m-1;
  while (a<n)
  {
      if(arr[a][b]==key)
      {cout<<"1"; break;
}
      else if (arr[a][b]>key)
      b--;  
      else  a++,b=m-1; 
  }
  if(a==n)
    cout<<"0"<<endl;

}
