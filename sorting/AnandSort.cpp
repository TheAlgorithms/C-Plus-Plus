/* This Sorting Algorith is based on array index matching, if element matches with the index number then that element is assigned at that place or index of array */
/* if we will assign each element at unique index and then print array in increasing order, ofcorse element will be printed in ascending order */
#include<iostream>
using namespace std;
int main(){
int i,j,n,A[100]={0};   // Initally each index is assigned with 0
cout<<"Enter Size Of the Array: ";
cin>>n;
int B[n];
cout<<"Enter elements: ";
for(i=0;i<n;i++){
cin>>B[i]; }
for(i=0;i<n;i++){
    for(j=0;j<=100;j++){
        if(B[i]==j){
            A[j]=B[i];
            break;
        }
    }
}
for(i=0;i<100;i++){
    if(A[i]!=0){      //It will print only that index element value which is not having 0 
cout<<A[i]<<" "; }
}
return 0;
}