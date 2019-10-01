// Program to demonstrate default behaviour of sort() in STL. 

#include <bits/stdc++.h> 
using namespace std; 
  
int main() 
{ 
    int size;
    cin>>size;
    int arr[size];
    
    for(int i=0; i<size;++i)
        cin>>arr[i];
        
    int n = sizeof(arr)/sizeof(arr[0]); 
  
    sort(arr, arr+n); 
  
    cout << "\nArray after sorting using "
         "default sort is : \n"; 
    for (int i = 0; i < n; ++i) 
        cout << arr[i] << " "; 
  
    return 0; 
} 