#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int sum=0;
    char arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=0;i<n;i++){
        if(arr[i]==arr[i+1])
        sum++;
    }
    cout<<sum;
}