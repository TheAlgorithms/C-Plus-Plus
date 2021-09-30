#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    float sum1=0,sum2=0,sum3;
    float arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
        sum1=sum1+arr[i]/100;
        sum2=sum2+(100-arr[i])/100;
    }
    sum3=sum1+sum2;
    cout<<sum1/sum3*100;



}