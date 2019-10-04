#include<bits/stdc++.h>
typedef long long int ll;
//#define for(i,a,b) for(ll i=a;i<b;i++)
//#define Rfor(i,a,x)  for(ll i=a/2;i>=1;i=i/x)
using namespace std;
int main()
{
ios::sync_with_stdio(0);
//cin.tie(0);
ll no=0,k=0;
cout<<"ENTER NUMBER OF ELEMENTS IN AN ARRAY:"<<"\n";
cin>>no;
ll arr[no];
cout<<"ENTER NUMBERS IN ASCENDING ORDER:"<<"\n";
for(ll i=0;i<no;i++)
cin>>arr[i];
cout<<"ENTER NUMBER to be search"<<"\n";
cin>>k;
ll l=0,u=no,mid,flag=0;
ll b=0;
ll z=2;
for(ll a=no/2;a>=1;a/=2)
{

    while(((b+a)<no)&&(arr[b+a]<k))
	{
	b=b+a;}
}
if(arr[b]==k)
cout<<"FOUND AT INDEX:"<<" "<<b<<"\n";
else
cout<<"NOT FOUND\n";
}

