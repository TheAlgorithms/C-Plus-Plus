#include<iostream>
using namespace std;
int bino(int n,int r){
    int a[n+1][r+1],i,j;
    for(i=1;i<=n;i++){
        for(j=0;j<=r;j++){
            if(i<j){
                a[i][j]=0;
            }
            else if(j==0 || i==j){
                a[i][j]=1;
            }
            else{
                a[i][j]=a[i-1][j]+a[i-1][j-1];
            }
        }
    }
    return a[n][r];
}
int main(){
    int n,r;
    cin>>n>>r;
    cout<<n<<"C"<<r<<" = "<<bino(n,r)<<endl;
    return 0;
}
