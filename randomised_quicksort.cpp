#include<iostream>
#include <bits/stdc++.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
int partition(int *a,int start,int end)
{
    int pindex=0;
    int pivot=a[end];
    for(int i=0;i<=end-1;i++)
    {
        if(a[i]<=pivot)
        {
            swap(a[i],a[pindex]);
            pindex=pindex+1;
        }
    }
    swap(a[pindex],a[end]);
    return pindex;
}
int random_partition(int *a,int start,int end)  #it will choose the random element as pivot element
{
    int r;
    srand(time(NULL));
    r=start+rand()%(end - start);
    swap(a[end],a[r]);
    return partition(a,start,end);
}

void quicksort(int *a,int start,int end)
{
    if(start<end)
    {
        int pindex=random_partition(a,start,end);
        quicksort(a,start,pindex-1);
        quicksort(a,pindex+1,end);
    }
}

int main()
{
    int i;
    int a[50000];
    int n;
    cout<<"ENTER THE SIZE OF LIST YOU WANT TO SORT : "<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<""<<endl;
    quicksort(a,0,n-1);
    cout<<"THE SORTED LIST IS: "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<" "<<a[i];
    }
    return 0;
}
