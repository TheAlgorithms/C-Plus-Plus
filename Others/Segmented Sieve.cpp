/*
Programmed By Shawon

This algorithm will generate prime
numbers in a given range with less time
complexity. In input,at first take the
number of test-cases,then give the input.

*/

#include <bits/stdc++.h>
using namespace std;
#define n 10000000
vector<long long int>s,sg,segment;
long long int p[n],k=1,size;
bool a[n];
long long int prime()
{
    long long i,j;
    a[0]=a[1]=1;
    for(i=4;i<=n;i=i+2)
    {
        a[i]=1;
    }
    for(i=3;i<=sqrt(n);i=i+2)
    {
        for(j=i*i;j<=n;j=j+2*i)
        {
            a[j]=1;
        }
    }
    p[0]=2;
    for(i=3;i<=n;i=i+2)
    {
        if(a[i]==0)
        {
            p[k]=i;
            //cout<<p[k]<<endl;
            k++;
        }
    }


}

void segmented_sieve(long long int l,long long int u)
{
    long long int root,start,i,j,si;
    sg.clear();
    root=sqrt(u)+1;



    for(i=l;i<=u;i++)
    {
        sg.push_back(i);
    }


    if(l==0)
    {
        sg[1]=0;
    }
    else if(l==1)
    {
        sg[0]=0;
    }



    for(i=0;p[i]<=root;i++)
    {
        si=p[i];

        start=si*si;

        if(start<l)
        {
            start=((l+si-1)/si)*si;
        }


        for(j=start;j<=u;j=j+si)
        {
            sg[j-l]=0;

        }
    }

}

int main()
{
     long long int m,g,c,r,t,l,h,u,w,tc,tx,i,j;

     prime();
     cin>>tc;

     for(tx=1;tx<=tc;tx++)
     {

        cin>>l>>u;
        segmented_sieve(l,u);

        for(i=l;i<=u;i++)
        {


            if(sg[i-l]!=0)
            {
                segment.push_back(sg[i-l]);
            }
        }

        for(i=0;i<segment.size();i++)
        {
            cout<<segment[i]<<endl;
        }
        segment.clear();
        sg.clear();
        cout<<endl;



     }



    return 0;
}




