#include <iostream>
using namespace std;

int main() {
    int arr[] = {1,3,4,2,7,8};
    int n = sizeof(arr)/sizeof(int);

    for(int i=0; i<n; i+=2){
        //previous element
        if(i != 0 and arr[i]<arr[i-1]){
            swap(arr[i], arr[i-1]);
        }

        //next element
        if((i != n-1) and arr[i]<arr[i+1]){
            swap(arr[i], arr[i+1]);
        }
    }
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }

    return 0;
}
/*
Output
3 1 4 2 8 7
*/
