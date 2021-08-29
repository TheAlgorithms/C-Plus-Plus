#include<iostream>
#include<bits/stdc++.h>

using namespace std;

//Function to swap to values
void swap(int *x, int *y)    
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

//Function to perform insertion sort 
void InsertSort(int a[],int *beg, int *end)
{
    int left = beg - a;
    int right = end - a;
    for(int i=left+1;i<=right;i++)
    {
        int k = a[i];
        int j;
        for(j=i-1;j>=0;j--)
        {
            if(a[j]>k)
                a[j+1] = a[j];
            else
                break;
        }
        a[j+1] = k;
    }
}

//Function performing quicksort
int* Partition(int a[],int low, int high)
{
    int pivot  = a[high];
    int i = low - 1;
    for(int j=low;j<high;j++)
    {
        if(a[j]<=pivot)
        {
            i++;
            swap(a[i],a[j]);
        }
    }
    swap(a[i+1],a[high]);
    return (a+i+1);
}

//Function that returns the median of three numbers
int* Median(int *a,int *b,int *c)
{
    if ((*a < *b && *b < *c) || (*c < *b && *b < *a)) 
       return b; 
  
    else if ((*b < *a && *a < *c) || (*c < *a && *a < *b)) 
       return a; 
  
    else
       return c; 
}

//Function that selects which algorithm is to be used
void SelectAlgo(int a[], int *begin, int *end, int depth)
{
    int size = end - begin;
    if(size < 16)      //case for insertion sort
    {
        InsertSort(a,begin,end);
        return;
    }
    if(depth == 0)      //case for heapsort
    {
        make_heap(begin,end+1);
        sort_heap(begin,end+1);
        return;
    }
    //performing quicksort
    int *pivot = Median(begin, begin+size/2, end);    //choosing the pivot
    swap(pivot,end);
    int* q = Partition(a,begin-a,end-a);
    SelectAlgo(a,begin,q-1,depth-1);
    SelectAlgo(a,q+1,end,depth-1);
}
//Introsort's function
void IntroSort(int a[],int *begin, int *end)
{
    int depth = 2 * log(end-begin);    //calculating depth
    SelectAlgo(a,begin,end,depth);
}

int main()
{
    int a[10000];
    int n;
    cout<<"Enter size:";
    cin>>n;
    cout<<"Enter elements: ";
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    IntroSort(a,a,a+(n-1));
    cout<<"Sorted Array: ";
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
    return 0;
}
