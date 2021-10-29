#include<iostream>
using namespace std;


void Leader(int arr[], int n){

int max= arr[n-1];
cout<<"here's the leaders "<<max<<" ";
for( int i=n-1;i>=0;i-- ){
    if(max<arr[i] ) {
        max=arr[i];
        cout<<max<<" "; 
        }
//  cout<<arr[i]<<" ";
 } 


}



int main(){
    int n;
int arr[10],i;
cout<<"size of array  ";
cin>>n;
cout<<"  enter array value  ";
for(i=0;i<n;i++){
    cin>>arr[i];
}
Leader(arr , n);
// int max= arr[n-1];
// cout<<"here's the leaders "<<max<<" ";
// for( i=n-1;i>=0;i-- ){
//     if(max<arr[i] ) {
//         max=arr[i];
//         cout<<max<<" "; 
//         }
// //  cout<<arr[i]<<" ";
//  } 
return 0;
}