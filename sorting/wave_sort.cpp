//Given an unsorted array of integers, sort the array into a wave form in linear time

#include<iostream>
#include<algorithm>
using namespace std;

void wave_sort(int a[],int n)
{

    for(int i=0;i<n;i=i+2)
    {
        if(i>0 && a[i]<a[i-1])         //check for left value w.r.t to current even position value
            swap(a[i],a[i-1]);

        if(i<n-1 && a[i]<a[i+1])       //check for right value w.r.t to current even position value
            swap(a[i],a[i+1]);

    }
    cout<<"wave sort \n";
    for(int i=0;i<n;++i)
        cout<<a[i]<<" ";
}
int main()
{
    int a[]={0,1,8,3,19,10,100,12,34,7};
    int n=sizeof(a)/sizeof(a[0]);

    wave_sort(a,n);
}
