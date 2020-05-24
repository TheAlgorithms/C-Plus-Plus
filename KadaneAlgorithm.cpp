#include<iostream>
#include<vector>
using namespace std;

int main()
{
  int n;
  int currentsum = 0, maxsum = 0;  // Stores current sum and maximum sum
  cin >> n;
  vector <int> a;
  for( int i = 0; i < n ; ++i )
  {
      int x;
      cin >> x;
      a.push_back(x);
  }
  for( int i = 0; i < n ; ++i )
  {
     currentsum = currentsum + a[i];
     //  If current sum becomes negative make it zero
     if ( currentsum < 0 ) 
      currentsum = 0;
     
     maxsum = max( currentsum , maxsum );
  }
  cout<< maxsum << endl;
  return 0;
}
