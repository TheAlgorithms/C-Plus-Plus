#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;
int main()
{
       int n = 9;
       vector<int> vi[1000];
       for(int i=1;i<=sqrt(n);i++)
       {
              if(n%i==0)
              {
                  if(i!=sqrt(n))
                  {
                      vi[n].push_back(i);
                      vi[n].push_back(n/i);
                  }
                  else
                  {
                       vi[n].push_back(i);
                  }
                  
              }
       }
       cout<<n<<" -- ";
       for(auto i=vi[n].begin();i!=vi[n].end();i++)
            cout<<*i<<" ";
}

/*
9 -- 1 9 3 
*/
