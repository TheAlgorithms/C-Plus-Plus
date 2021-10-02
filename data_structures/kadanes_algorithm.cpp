//kadane's algorithm for maxim sum of continous sub-array

#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the size of array:";
    cin>>n;
    int arr[n];
    cout<<"Enter the array elements:";
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int sum=0,max=arr[0];
    for(int i=0;i<n;i++)
    {
        sum+=arr[i];
        if(sum > max)
        {
            max=sum;
        }
        if(sum < 0)
        {
            sum=0;
        }
    }
    cout<<"maximum sum of continous sub-array is "<<max<<endl;
    return 0;
}
