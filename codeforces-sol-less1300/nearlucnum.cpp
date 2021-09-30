#include<iostream>
#include<string.h>
using namespace std;
int main(){
    long long int s;
    cin>>s;
    int a;
    int sum=0;
    while(s>0){
        a=s%10;
        s=s/10;
        
        if(a==4){
            sum++;
        }
        if(a==7){
            sum++;
        }
    }
    if(sum==7||sum==4){
        cout<<"YES";
    }else
    cout<<"NO";
}