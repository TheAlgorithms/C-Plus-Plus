#include<bits/stdc++.h>
using namespace std;
void countsort(int a[],int n)
{
    int b[n];int max=a[0],min=a[0];
    for(int i=0;i<n;i++)
    {
        if(max<a[i])
        max=a[i];
        if(min>a[i])
        min=a[i];
    }
    int range=max-min+1;
    int f[range];
    for(int i=0;i<range;i++)
    {
        f[i]=0;
    }
    for(int i=0;i<n;i++)
    {
        f[a[i]-min]++;
    }
    for(int i=1;i<range;i++)
    {
        f[i]=f[i]+f[i-1];
    }
    for(int i=n-1;i>=0;i--)
    {
        int pos=f[a[i]-min]-1;
        b[pos]=a[i];
        f[a[i]-min]--;
    }
    for(int i=0;i<n;i++)
    {
        a[i]=b[i];
    }
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<"  ";
    }

}
int main()
{
    int n;
    cout<<"ENETR NUMBER OF VALUES : ";
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    countsort(a,n);
    
 return 0;
}