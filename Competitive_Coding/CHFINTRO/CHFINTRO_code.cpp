#include<iostream>

using namespace std;

int main(void){
    unsigned int n,r,a;
    cin>>n>>r;
    for(int i=0;i<n;i++){
        cin>>a;
        if(a<r)
            cout<<"Bad boi"<<"\n";
        else
            cout<<"Good boi"<<"\n";
    }
}
