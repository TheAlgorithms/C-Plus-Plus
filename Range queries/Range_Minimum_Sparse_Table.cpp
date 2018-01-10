#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAXN 1234567
int M[MAXN][30]={0};
int A[MAXN] = {0};
int main(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++) cin >> A[i];
    for(int j=0;j<n;j++){
        M[j][0] = j;
    }
    for(int j=1;(1<<j)<=n;j++){
        for(int i=0;i<n;i++){
            M[i][j] =  ((A[M[i][j-1]]<A[M[i+ (1<<(j-1))][j-1]])?M[i][j-1]:M[i+ (1<<(j-1))][j-1]);
        }
    }
    int q;
    cin>> q;
    int l,r;
    long long ans = 12345678912;
    while(q--){
        cin >> l >> r;
        int k = log2(r-l+1);
        //cout << "k val " << k << endl;
        ans = min(A[M[l][k]], A[M[r-(1<<k)+1][k]] );
        cout << ans << endl;
    }
}