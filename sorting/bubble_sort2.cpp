
#include<iostream>
using namespace std;

/**
 * @file
 * @brief Simplified implementation of Bubble Sort
 *
 * @details
 * This code takes input from the user and applies the Bubble Sort algorithm
 * to sort the given array in ascending order. It is a beginner-friendly
 * version written using basic C++ without advanced templates or libraries.
 */

/**
 * @brief Main function to run the Bubble Sort
 * @return 0 on successful execution
 */

int main(){
    int n,t;
    //input array size
    cout<<"enter size";
    cin>>n;
    int arr[n];

    //input array elements
    cout<<"enter elements";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int j=0;j<n;j++){
        for(int k=0;k<n-1;k++){
            if(arr[k]>arr[k+1]){
                //swap elements
                t=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=t;
            }
        }
    }
    //output the sorted array
    for(int l=0;l<n;l++){
        cout<<arr[l]<<" ";
    }
    return 0;
}