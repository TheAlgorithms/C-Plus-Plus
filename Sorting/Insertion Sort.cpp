#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
    int n,i,j,mini,temp;
    int * arr;
    cout<<"Enter the size of array you want to create: ";
    cin>>n;
    arr=new int(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        cout<<"Enter element "<<i+1<<": ";
        cin>>*(arr+i);
    }
    cout<<"\nThe array before insertion sort is: ";
    for(i=0;i<n;i++)
    {
        cout<<*(arr+i)<<"   ";
    }
    for(i=0;i<n;i++)
    {
        mini=i;
        for(j=i+1;j<n;j++)
        {
            if((*(arr+j))<(*(arr+mini)))
                mini=j;
        }
        temp=(*(arr+mini));
        *(arr+mini)=*(arr+i);
        *(arr+i)=temp;
    }
    cout<<"\nThe array after insertion sort is: ";
    for(i=0;i<n;i++)
    {
        cout<<*(arr+i)<<"   ";
    }
    return 0;
}
