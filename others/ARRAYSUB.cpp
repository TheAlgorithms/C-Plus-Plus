// Given an array and an integer k, find the maximum for each and every contiguous subarray of size k.
// https://www.spoj.com/problems/ARRAYSUB/

#include<iostream>
#include <deque>
using namespace std;
int main(){
    //Taking Input From The User.
    int n;
    cout<<"Enter The value of N:\n";
    cin>>n; //Size of Array
    int ar[n];
    cout<<"Enter the elements of array:\n";
    for (int i = 0; i < n; ++i) {
        cin>>ar[i];
    }
    int k;
    cout<<"Enter the value of k:\n";
    cin>>k; //Size Of The Sliding Window

    deque<int> d(k);//Created data Structure Deque Of Size k
    cout<<"Maximum Numbers in sliding window of size "<<k<<" are:\n";
    for(int i=0;i<n;i++){
        if(i>=k){
            cout << ar[d.front()] << " ";
 	    //Checking whether a given number is in sliding window or not.
	    //If it is not then pop the front element.
            while(!d.empty() && d.front() <= i - k){
                d.pop_front();
            }
        }
	//If the given number is greater than number at last then we pop it.
        while(!d.empty() && ar[i] >= ar[d.back()]){
            d.pop_back();
        }
        d.push_back(i);
    }
    cout<<ar[d.front()];
}

/*
Time Complexity : O(N*Log2(N))
Sample I/O:
INPUT : 
Enter The value of N:
9
Enter the elements of array:
1 2 3 1 4 5 2 3 6
Enter the value of k:
3

OUTPUT:
Maximum Numbers in sliding window of size 3 are:
3 3 4 5 5 5 6
*/