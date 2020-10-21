#include<iostream>
using namespace std;

void bin_search(int a[],int s,int k)
{
	int low=0,high=s-1,i,mid;
	bool flag=false;
	while(low<high)
	{
		mid=(low+high)/2;
		if(a[mid]==k)	
		{
		flag=true;
		break;
		}
		if(k>a[mid])
			low=mid+1;
		if(k<a[mid])
			high=mid-1;
	}
	if(flag)
		cout<<"element found at "<<mid+1<<" position "<<endl;
	else
		cout<<" element not found ";
}

int main()
{
	int a[10],n=10,i,key;
	cout<<"please enter elements in sorted order";
	for(i=0;i<n;i++)
		cin>>a[i];
	cout<<"enter key value";
	cin>>key;
	bin_search(a,n,key);//call by reference
	return 0;
}

