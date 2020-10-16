#include<bits/stdc++.h>
using namespace std;

int majority_element(int arr[], int n)
{
    int cnt = 1, index = 0;
    for(int i=1;i<n;i++) {
        if(arr[i] == arr[index]) {
            cnt++;
        }
        else {
            cnt--;
        }
        if(cnt == 0) {
            index = i;
            cnt = 1;
        }
    }
    return arr[index];
}


int main()
{
    int arr[] = {1,3,3,1,2};
    int n = sizeof(arr)/sizeof(arr[0]);
    int candid = majority_element(arr,n);
    int cnt = 0;
    for(int i=0;i<n;i++) {
        if(arr[i] == arr[candid]) {
            cnt++;
        }
    }
    if(cnt > n/2) {
        cout<<"Majority Element is "<<arr[candid];
    }
    else {
        cout<<"No majority element found";
    }
}
