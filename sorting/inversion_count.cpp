/*
 *this program is use to count the number in inversions in an array
 *In an array two elements .i.e. a[i], a[j] are said to be in inverison if a[i] > a[j] and i < j. 
 *The count of inversion indicates how close the array is from being sorted
 *For example for integer array named arr
 *int arr[] = {2,1,3,4}
 *In the array arr (2,1) form an inversion pair because 2 > 1 and 2 comes before 1 in the array.
 *The sort this array we need to swap 1,2, so the count of inversions here is 1.
 *The efficient way to solve is to take some inspiration from the merge sort algorithm
 *This algorithm takes O(NlogN) time.Idea behind the algorithm :
 *Suppose we have an array of integers of size n.
 *Suppose the indices, low = 0, high = n-1, mid = (low + high)/2.
 *The array indices can be visualized as low .............. mid mid+1 .............. high
 *The array is divided into 2 halves, these two halves are sorted recursively, the difference from 
 *the merge sort here is that, while sorting the array recursively, inversion pairs are also counted.
 *We are counting the numbers of inverison while we are sorting left half recursively
 *We are counting the number of inversion while we are sorting right half recursively
 *Then we count number of inverisons while merging both halves together
 *Main code snippet of this alogorithm is 
 *if(start >= end) {
        return 0;
    }
    ll inv_count = 0; // initialize the inverision count.
    ll int mid = start + (end- start) /2;
    inv_count += inversion_count(arr ,start, mid); // count number of inverisons while sorting left half recursively
    inv_count += inversion_count(arr , mid+1, end); // count number of inverisons while sorting right half recursively
    inv_count += merge(arr,start,end); // merge both halves together and add inversion count
    return inv_count;
*/


#include <iostream>
#include <vector>
using namespace std;
#define ll long long

ll int merge(vector<ll> arr, ll int start, ll int end) {
    ll int mid  = start+ (end-start)/2;
    ll int i=start;
    ll j = mid +1;
    ll k=start;
    vector<ll> temp(1000000);
    ll int cnt = 0;
    
    while(i <= mid and j <=end) {
        if(arr[i] <= arr[j]) {
            temp[k] = arr[i];
            k++;
            i++;
        }
        else { // inversion 
            temp[k++] = arr[j++];
            cnt += mid -i +1;
        }
    }
    while(i<=mid) {
        temp[k++] = arr[i++];
    }
    
    while(j<=end) {
        temp[k++] = arr[j++];
    }
    for(ll i=start;i<=end;i++) {
        arr[i] = temp[i];
    }
    return cnt;
}

ll int inversion_count( vector<ll> arr, ll int start,ll int end) {
    if(start >= end) {
        return 0;
    }
    ll inv_count = 0; // initialize the inverision count.
    ll int mid = start + (end- start) /2; 
    inv_count += inversion_count(arr ,start, mid); // count number of inverisons while sorting left half recursively
    inv_count += inversion_count(arr , mid+1, end); // count number of inverisons while sorting right half recursively
    inv_count += merge(arr,start,end); // merge both halves together and add inversion count
    return inv_count;
}


int main() {
      
	    ll int n = 0;
	    cin>>n;
	    vector<ll> arr(n,0);
	    for(ll int i=0;i<n;i++) {
	        cin>>arr[i];
	    }
	    cout<<inversion_count(arr, 0, n-1)<<endl;
	return 0;
}
