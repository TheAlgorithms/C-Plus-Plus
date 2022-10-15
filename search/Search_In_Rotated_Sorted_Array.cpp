#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int getpivot(int arr[],int n){
    int s = 0;
    int e = n-1;
    int mid = s + (e-s)/2;
    while(s<e){
        if(arr[mid]>=arr[0]){
            s = mid + 1;
        }
        else{
            e = mid;
        }
        mid = s + (e-s)/2;
    }
    return s;
}

int binary_search(int arr[],int s,int e,int key){
    int start = s;
    int end = e;
    
    while(start<=end){
        int mid = start + ((end - start)/2);
        if(arr[mid] == key){
            return mid;
        }
        if(key > arr[mid]){
            start = mid + 1;
        }
        else{
            end = mid - 1;
        } 
        
        
    }
    return -1;
}


int main(){
   int arr[5]={4,5,1,2,3};
   int k;
   cin>>k;
   int pivot = getpivot(arr,5);
   if(k>=arr[pivot] && k<=arr[4]){
    cout<< binary_search(arr,pivot,5,k);
   }
   else{
    cout<< binary_search(arr,0,pivot,k);
   }
    

}