/*An algorithm to input a sequence of sorted integers and output the index(1-based) of a given integer.
If that integer is not found then output the index of the smallest integer just greater than the given integer*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
long long int n,q,index;
long long int value;
vector<long long int> v;
vector<long long int>::iterator it;

int main() {
    /* Read input from STDIN. Print output to STDOUT */

      cin>>n;                //number of integers
      for(long long int i=0;i<n;++i)       //storing the integers in a vector
    {
        cin>>value;
        v.push_back(value);
    }
    cin>>q;            // Integer to search

            it=lower_bound(v.begin(),v.end(),q);      //searching for lower bound of q
        if(q==*it){                                   //if the lower bound is equal to the integer itself, then it is present
            cout<<"Yes "<<(it-v.begin()+1)<<endl;

        }
        else{
            cout<<"No "<<(it-v.begin()+1)<<endl;
        }

    return 0;
}
