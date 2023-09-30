#include<bits/stdc++.h>
using namespace std;
int palin(string s){  
    int n=s.length();

    int a[n][n];
    for(int i=n-1;i>=0;i--){
        for(int j=i;j<n;j++){
            if(i==j){ 
                a[i][j]=1;
            }
            else if(j==i+1){
                if(s[i]==s[j]) a[i][j]=1;
                else a[i][j]=0;
            }
            else{
                if(s[i]==s[j]) a[i][j]=a[i+1][j-1];
                else a[i][j]=0;
            }
        }
    }
    int res=0;
    for(int i=n-1;i>=0;i--){
        for(int j=i;j<n;j++){
            if(a[i][j]==1) res++;
        }
    }
    return res;
}
int main(){
    string s;
    cin>>s;
    cout<<palin(s);
    return 0;
}