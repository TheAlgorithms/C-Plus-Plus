#include<iostream>
using namespace std;
int main(){
    int k,l,m,n,d;
    cin>>k>>l>>m>>n>>d;
    int sum=0;
    int arr[d]={};
    for(int i=1;i<=d;i++){
        if(i%k==0)
        arr[i]=1;
        if(i%l==0)
        arr[i]=1;
        if(i%m==0)
        arr[i]=1;
        if(i%n==0)
        arr[i]=1;
        if(arr[i]==1)
        sum++;

    }
    
    cout<<sum;
}