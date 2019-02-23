#include<iostream>
#include<cmath>
using namespace std;
int buildseg(int seg[],int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        seg[n-1+i]=arr[i];
    }
    for(int i=n-2;i>=0;i--)
    {
        seg[i]=seg[2*i+1]+seg[2*i+2];
    }

}
int main()
{
    int arr[]={1,2,3,4,5,6,7,8,9,10};//sum of all must be equal to 55
    int n=sizeof(arr)/sizeof(int);
    int size=int(2*pow(2,ceil(log2(n))))-1;//Maximum number of nodes in a segment tree
    int seg[size]={0};

    buildseg(seg,arr,n);
    for(int i=0;i<size;i++)
    {
        cout<<seg[i]<<" ";
    }
}
