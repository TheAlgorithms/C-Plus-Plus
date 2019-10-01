// Binary Search in STL

#include <algorithm> 
#include <iostream> 
  
using namespace std; 
  
void show(int a[], int arraysize) 
{ 
    for (int i = 0; i < arraysize; ++i) 
        cout << a[i] << " "; 
} 
  
int main() 
{ 
    int size;
    cin>>size;
    int a[size];
    
    for(int i=0; i<size;++i)
        cin>>a[i];
    int asize = sizeof(a) / sizeof(a[0]); 
    
    cout << "\n The array is : "; 
    show(a, asize); 
  
    cout << "\n\nLet's say we want to search for 2 in the array"; 
    cout << "\n So, we first sort the array"; 
    sort(a, a + asize); 
    
    cout << "\n\n The array after sorting is : "; 
    show(a, asize); 
    
    cout << "\n\nNow, we do the binary search"; 
    
    if (binary_search(a, a + 10, 2)) 
        cout << "\nElement found in the array"; 
    else
        cout << "\nElement not found in the array"; 
  
    cout << "\n\nNow, say we want to search for 10"; 
    
    if (binary_search(a, a + 10, 10)) 
        cout << "\nElement found in the array"; 
    else
        cout << "\nElement not found in the array"; 
  
    return 0; 
} 