#include<iostream>
using namespace std;
//Naive Solution.
int MaxSum(int arr[] , int n)
{
    int res = 0 ;
    for(int i = 0 ; i<n ; i++ )
    {
        int count = 0; 
        for(int j = i ; j<n ; j++)
        {
            count += arr[j];
            res = max(res , count);
        }
    }
    return res;
}
//Efficient Solution.
int MaximumSum(int arr[] , int n)
{
    int res = 0;
    int maxend = arr[0];
    for(int i = 0 ; i<n ; i++)
    {
        maxend = max(maxend + arr[i] , arr[i]);
        res = max(maxend , res);
    }
    return res;
}
int main()
{
    int n = 6; 
    int arr[n] = {-3, 8, -2, 4, -5, 6};
    cout<<MaximumSum(arr , n);
}
