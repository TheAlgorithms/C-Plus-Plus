#include <bits/stdc++.h>
using namespace std;
#define ll long long int

ll n;
ll arr[100010];

int main() {
    cin>>n;
    for(ll i=0;i<n;i++){
        cin>>arr[i];
    }
    ll curr_sum=0;
    ll max_so_far=INT_MIN;
    for(ll i=0;i<n;i++){
        curr_sum+=arr[i];
        
        if(max_so_far<curr_sum){
            max_so_far=curr_sum;
        }
        if(curr_sum<0){
            curr_sum=0;
        }
    }
    cout<<max_so_far<<endl;
	return 0;
}
© 2019 GitHub, Inc.
