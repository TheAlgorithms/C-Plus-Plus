#include <bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;

int countSetBitsOptimised(int N) {
    int ans=0;
    while(N) {
        N=N&(N-1);
        ans++;
    }
    return ans;
}
int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for(int i=1;i<=10;i++)
        cout<<"Number of set bits in "<<i<<" is: "<<countSetBitsOptimised(i)<<endl;    
}
