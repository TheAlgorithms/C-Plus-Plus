#include <bits/stdc++.h>
#include<iostream>
using namespace std;
//function definations
void swap(int* ,int*);
void bubbleSort(int[],int);

//the driver code
int main()  
{  
    int arr[] = {35,9,246,5,79,12,0,125,1,68,42,6};  
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<"Original Array:- \n";
    int i;  
    for (i = 0; i <n; i++)  
        cout << arr[i] << " ";  
    cout << endl;  
    bubbleSort(arr, n);  
    cout<<"Sorted array: \n";
    for (i = 0; i < n; i++)  
        cout << arr[i] << " ";   
    return 0;  
}

//Function to swap the values of two given pointers 
void swap(int *a, int *b)  
{  
    int temp = *a;  
    *a = *b;  
    *b = temp;  
}  
  
// the solo function to implement bubble sort  
void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)
    {
    	for (j = 0; j < n-i-1; j++)  
            if (arr[j] > arr[j+1])  
            	swap(&arr[j], &arr[j+1]); 
    }
}  
//-------------------------THANK YOU-------------------------------
