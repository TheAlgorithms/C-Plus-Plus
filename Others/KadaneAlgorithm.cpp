#include<iostream>
using namespace std;

//returns the maximum subarray sum in O(n)

int kadane(int a[], int n)
{
    int current_sum, global_sum;
    current_sum = global_sum = a[0];                        //initially taking the first element as global sum and temporary cuurent sum
    for(int i=1; i<n; i++)
    {
        current_sum = max(a[i], current_sum+a[i]);          //choosing the maximum value between the current element and addition of previous sum with next contigous element
        global_sum = max(current_sum,global_sum);           //updating the global sum only if the current sum is greater than the global sum
    }
    return global_sum;
}

int main()
{
    int arr[] = {-1,-3,2,1,-4,5,6,-3,0,1,1,1,1,3};          //input array
    int size = sizeof(arr)/sizeof(arr[0]);

    int max_sum = kadane(arr,size);                         //calling the algorithm
    cout<<max_sum<<endl;
    return 0;
}
//Contributed by Sathvik S
