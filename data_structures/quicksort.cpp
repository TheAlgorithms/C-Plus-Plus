#include<iostream>
using namespace std;


int partition(int [],int,int);
void quicksort(int a[],int p,int r)
{
if(p<r)
{
int q=partition(a,p,r);
quicksort(a,p,q-1);
quicksort(a,q+1,r);
}
}
int partition(int a[],int p,int r)
{
int j;
j=p-1;
int x=a[r];
for(int k=p;k<=r-1;k++)
{
if(a[k]<=x)
{
j+=1;
int c=a[k];
a[k]=a[j];
a[j]=c;
}
}
int d=a[j+1];
a[j+1]=a[r];
a[r]=d;
return(j+1);
}

int main()
{
int a[1000],n,i;


cout<<"enter number of elements";


cin>>n;

for(i=0;i<=n-1;i++)
{
cin>>a[i];
}
cout<<"before sorting";
for(i=0;i<=n-1;i++)
{
cout<<a[i]<<endl;
}
quicksort(a,0,n-1);
cout<<"after sorting";
for(i=0;i<=n-1;i++)
{
cout<<a[i]<<endl;
}
return 0;
}
