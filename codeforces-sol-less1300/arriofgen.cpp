#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int ima=0,imi=n-1;
    int arr[n];
    int temp;
    
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int min=arr[0],max=arr[0];
    for(int k=0;k<n;k++){
        if(max<arr[k]){
        max=arr[k];
        ima=k;
        }
        if(min>=arr[k]){
        min=arr[k];
        imi=k;
        }
    }
    // cout<<ima<<" "<<imi;
    if(arr[ima]==arr[0]&&arr[imi]==arr[n-1]){
        cout<<0;
    }
    else if(ima>imi){
        cout<<ima+n-1-imi-1;
    }
    else{
        cout<<ima+n-1-imi;
    }
    

}