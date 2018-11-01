#include<iostream>
using namespace std;
void heapify();
void swap(int*,int*);
int a[5];
int root;
int main()
{
	cout<<"enter 5 elements";
	for(int i=0;i<5;i++)
	{
		cin>>a[i];
	}
	// sort edges
	int k=0,last,root,new1[5];
	last=4;
	root=0;
	while(last>1)
	{
	new1[k]=a[root];
	k++;
	a[root]=a[last];
	last--;
	heapify();
    }
    cout<<"\n sorted elements are";
    for(int i=0;i<5;i++)
    {
    	cout<<new1[i]<<"\n";
    }
	//pick one edge
	// check if it makes cycle 
	return 0;
}
void heapify()
{
	
	int left,right;
	left=2*root+1;
	right=2*root+2;
	while(root>1)
	{
	if(a[left]<a[right])
	{
		if(a[left]<a[root])
		{
		swap(&a[left],&a[root]);
		root=left;
	    }
		
	}
	if(a[right]<a[left])
	{
		if(a[right]<a[root])
		{
			swap(&a[right],&a[root]);
			root=right;
		}
	}
    }
	
}
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

