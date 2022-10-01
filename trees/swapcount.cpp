// C++ program to Count
// Inversions in an array
// using Merge Sort
#include <bits/stdc++.h>
#include<vector>
using namespace std;

// Function to count inversions in the array.
long long int merge(long long arr[], long long temp[],long long left,long long mid,long long right) 
{
   long long i=left;
   long long j=mid;
   long long k=left;
long long int count;
   while((i<=mid-1) && (j<=right))
   {
       if(arr[i]<=arr[j])
       {
         temp[k++]=arr[i++];          
       }
       else
       {
           temp[k++]=arr[j++];
           count=count+(mid-i);
       }
   }
   while(i<=mid-1)
   {
      temp[k++]=arr[i++];  
   }
    while(j<=right)
   {
    temp[k++]=arr[j++];
   } 
   for(i=left;i<=right;i++)
   arr[i]=temp[i];
   
   return count;
}
long long int mergesort(long long arr[], long long temp[],long long left,long long right)
{
    long long mid;
    long long int count=0;
    if(right>left)
    {
        mid=right+left/2;
        count+=mergesort(arr,temp,left,mid);
        count+=mergesort(arr,temp,mid+1,right);
        
        count+=merge(arr,temp,left,mid+1,right);
    }
    return count;
}

long long int inversionCount(long long arr[], long long N)
{
    long long temp[N];
    long long a=0;
    return mergesort(arr,temp ,a, N-1);

    }
    // Your Code Here


// Driver code
int main()
{
    long long arr[] = { 1, 20, 6, 4, 5 };
    long long n = sizeof(arr) / sizeof(arr[0]);
    long long int ans = inversionCount(arr, n);
    cout << " Number of inversions are " << ans;
    return 0;
}

