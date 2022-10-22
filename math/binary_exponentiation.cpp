#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define rep(i,a,b) for(int i=a;i<b;i++)
#define sq(a) (a)*(a)
#define vi vector<int>
#define mp make_pair
#define ii pair<int,int>
#define vii vector<ii>

// the concept is to do exponentiation by converting the power to a sum of powers of 2.
// example: 3^13  we can convert 13 to 8+4+1. which can be represented by 1101. so to do 3^13 we can do instead
// 3^8 x 3^4 x 3^1. and so we get 3^13 and since every exponent is square of the old exponent eg: 3^8=(3^4)^2.

ll binary_exponentiation(ll a,ll b){
  ll res=1;   //
  while(b>0){
    if(b&1){
      res=res*a;
    }
    a=a*a;
    b>>=1;  //reducing the power by a power of 2. example 13->6->3->1->0;
  }
  return res;
}

int main(){
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ll a,b;
  cin>>a>>b;
  cout<<binary_exponentiation(a,b);
}