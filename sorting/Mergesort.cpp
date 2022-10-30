#include <bits/stdc++.h>
using namespace std;


void merge(int arr[],int l,int r,int mid){

    int ls = mid - l +1;
    int rs = r-mid ;

    int a[ls];
    int b[rs];

    for(int i = 0;i<ls;i++)
    {
        a[i]= arr[l+i];
    }
    for(int i = 0;i<rs;i++)
    {
        b[i]= arr[mid+1+i];
    }

    int i=0,j=0,k=l;

    while(i<ls&&j<rs)
    {
        if(a[i]<=b[j])
        {
            arr[k]=a[i];
            i++,k++;
        }
        else
        {
             arr[k]=b[j];
            j++,k++;
        }

    }

    while(i<ls)
    {
        arr[k] = a[i];
        i++,k++;
    }
    while(j<rs)
    {
        arr[k] = b[j];
        j++,k++;
    }   
}    

void mergesort(int arr[],int l,int r)
{   
    if(l==r)
    return;
    int mid = (l+r)/2;

    mergesort(arr,l,mid);
    mergesort(arr,mid+1,r);

    merge(arr,l,r,mid);
}

int main()
{
    int n;
    cout<<"Enter no. of elements : "<<endl;
    cin>>n;
    int arr[n];
    cout<<endl<<"enter elements : ";
    for(int i = 0;i<n;i++)
    {
        int x;
        cin>>x;
        arr[i]=x;
    }

    mergesort(arr,1,n-1);

    for( auto i :arr)
    {
        cout<<i<<" ";
    }
}
