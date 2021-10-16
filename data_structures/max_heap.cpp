#include <bits/stdc++.h>
#include <algorithm>
#include <set>
#include <math.h>
#include <vector>
#define int long long 
#define mode 998244353
using namespace std;
class Solution
{
    public:
    void heapify(int a[], int n, int x)  {
        int l=x;
        int left = (2*x)+1;
        int right = (2*x)+2;
        if(left<n && a[left]>a[l]){
            l=left;
        }
        if(right<n && a[right]>a[l]){
            l=right;
        }
        if(l!=x){
            swap(a[x] , a[l]);
            heapify(a , n , l);
        }
    }

    public:
    void buildHeap(int arr[], int n)  { 
        int x;
        x = (n/2)-1;
        for(int i=x;i>=0;i--){
            heapify(arr , n , i);
        }
    }
};
int32_t main(){
    int n = 5;
    int arr[] = {4,1,3,9,7};
    Solution ob;
    ob.buildHeap(arr , n);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}
