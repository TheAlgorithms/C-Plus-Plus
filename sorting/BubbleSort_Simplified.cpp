// bubble sort is based on keeping the maximum element at the last position

#include<iostream>
using namespace std;
int main(){
    int n,t;
    cout<<"enter size";
    cin>>n;
    int arr[n];
    cout<<"enter elements";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int j=0;j<n;j++){
        for(int k=0;k<n-1;k++){
            if(arr[k]>arr[k+1]){
                t=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=t;
            }
        }
    }
    for(int l=0;l<n;l++){
        cout<<arr[l]<<" ";
    }
    return 0;
}