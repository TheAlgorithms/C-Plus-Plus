#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
const int N = 1e5+5;
const int MOD = 1e9+7;
 
using namespace std;
ll bitwiseor(ll a, ll b){
    if (a==b)
        return a;
    ll final = 0;
    ll rev = 0;
    while(b){
        final*=2;
        if (a%2==1 || a != b)
            final++;
        a/=2;
        b/=2;
    }
    while(final){
        rev *= 2;
        rev += final % 2;
        final/=2;
    }
    return rev;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll a;
    cin>>a;
    for(ll itr{0};itr<a;itr++){
  		ll n,m;
  		cin>>n>>m;
  		ll x = n;
  		ll l = max(0ll,(x-m));
  		ll r = x+m;
  		x = bitwiseor(l,r);
  		cout<<x<<"\n";
    }
    return 0;
}
