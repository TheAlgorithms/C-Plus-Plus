#include<iostream>
#include<string>
using namespace std;

int factorial(int x){
    if(x==0){
        return 1;
    }
    return x*factorial(x-1);
}
int binomial(int n,int k){  
    return factorial(n)/(factorial(n-k)*factorial(k));
}
int main(){
    int height=0;
    cout<<"Enter the height of the triangle:";    
    cin>>height;
    for(int i=0;i<height;i++){
        for(int j=0;j<height-i-1;j++){
            cout<<" ";
        }
        for(int j=0;j<=i;j++){
            cout<<binomial(i,j)<<" ";
        }
        cout<<endl;
    }
    return 0;
}