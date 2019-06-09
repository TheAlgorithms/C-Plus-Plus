#include<iostream>
using namespace std;
typedef long long ll;
const ll M = 1e9+7;
const ll inf = 2e18;
#define mp make_pair
#define pb push_back
signed main(){

 ll t;
 cin>>t;
 while(t--){
    string s;
    cin>>s;
    if(s.size() == 1){
        cout << "DPS" << '\n';
        continue;
    }
    sort(s.begin(),s.end());
    ll n= s.size();
    if(s.size()%2 != 0){
         ll x=0;
       for(ll i=0;i<n;){
         if(s[i] == s[i+1]){
            x++;
            i+=2;
            continue;
         }
         if(s[i] != s[i+1]){
            i++;
            continue;
         }
       }
       if(x >= (n-3)/2){
        cout << "DPS" << '\n';
        continue;
       }
    }
    if(s.size()%2 == 0){
            ll x=0;
        for(ll i=0;i<n;){
         if(s[i] == s[i+1]){
            x++;
            i+=2;
            continue;
         }
         if(s[i] != s[i+1]){
            i++;
            continue;
         }
       }
       if( x == (n-2)/2){
        cout << "DPS" << '\n';
        continue;
       }
    }
    cout << "!DPS" << '\n';
 }
return 0;
}

