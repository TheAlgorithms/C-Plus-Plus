#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std; 
void countSort(int arr[],const int &n,const int &exp) {
    int count[10] = {0};
    for(int i = 0; i < n; i++) count[(arr[i]/exp) % 10]++;  
    for(int i = 1; i < 10; i++) count[i] += count[i - 1];
    int output[n];
    for(int i = n - 1; i >= 0; i--) {
        output[count[(arr[i]/exp) % 10] - 1] = arr[i];
        count[(arr[i]/exp) % 10]--;
    }
    for(int i = 0; i < n; i++) arr[i] = output[i];
}

void radixsort(int arr[], int n) { 
   int maxElement = arr[0];
   for(int i = 0; i < n; i++) maxElement = max(arr[i], maxElement); // Finding maximum element
   for(int exp = 1; maxElement/exp > 0; exp *= 10)
        countSort(arr, n, exp);    // Counting sort for every i-th digit 
}
void print(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main(int argc, char const* argv[]) {
    int a[] = {9358,133,943,235,3140,22,1,4,92,22,10};
    int n = sizeof(a) / sizeof(a[0]);
    radixsort(a,n);
    print(a, n);
    return 0;
}
