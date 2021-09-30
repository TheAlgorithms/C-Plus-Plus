#include<iostream>
using namespace std;
int prime(int n){
    int i, status=5;
    for(i=2;i<n;i++){
        if(n%i==0){
            status= 0;
            break;
        }
    }
    if(status!=0){
        status= 1;
    }
    return status;
}
int main(){
    int n;
    cin>>n;
    int m;
    cin>>m;
    while(true){
        n=n+1;
        if(prime(n)==1){
            if(n==m){
            cout<<"YES";
            break;}
            else{
            cout<<"NO";
            break;
              }      
        }

        
    }
   
}