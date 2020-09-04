// sort an array of 0s, 1s and 2s
// time complexity O(n)

#include<iostream>

using namespace std;

void dnf_sort(int a[],int n)
{
    int in=0;                        //variable which used to point starting position
    int f=n-1;                       //variable which used to point last poistion
    int mid=0;                       //it is used to traverse

    while(mid<=f){
        if(a[mid]==0)                //if we find '0' and place it in begining
        {
            swap(a[mid],a[in]);
            mid++;
            in++;
        }
        else if(a[mid]==1)
            mid++;
        else if(a[mid]==2)           //if we find '2' and place it in end
        {
            swap(a[mid],a[f]);
            f--;
        }

    }
}

int main()
{
    int arr[]={2,1,1,0,2,0,1,1,1,2};
    int n=sizeof(arr)/sizeof(int);

    //calling sorting function
    dnf_sort(arr,n);

    for(int i=0;i<n;++i)
        cout<<arr[i]<<" ";

    return 0;
}

