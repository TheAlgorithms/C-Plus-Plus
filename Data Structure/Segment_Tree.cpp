//
// SEGMENT TREE : A Segment Tree is a data structure that allows 
// answering range queries over an array effectively,
// while still being flexible enough to allow modifying the array. 

// A C++ program to demonstrate common Binary Heap Operations namely
// update , query on range (where the query is minimum in range) 


#include <iostream>
#include <climits>
using namespace std;


int st[400005],a[100005],y,l,r,x;

void build(int in,int s,int e)
{
	if(s==e)
	{
		st[in]=a[s];
		return;
	}
	int m=(s+e)/2;
	build(2*in,s,m);
	build(2*in+1,m+1,e);
	st[in]= min(st[2*in],st[2*in+1]);
}

void update(int in,int s,int e)
{
	if(s==e)
	{
		st[in]=y;
		return;
	}
	int m=(s+e)/2;
	if(s<=x && x<=m)
		update(2*in,s,m);
	else
		update(2*in+1,m+1,e);
	st[in]=min(st[2*in],st[2*in+1]);
}

int query(int in,int s,int e)
{
	if(r<s || e<l)
		return INT_MAX;
	if(l<=s && e<=r)
		return st[in];
	int m=(s+e)/2;
	return min(query(2*in,s,m),query(2*in+1,m+1,e));
}


int main()
{
	int n,k,m,i,j,c=0,cs=0,t;
	t=1;

	cin>>n;
	for(i=0;i<n;i++)
		cin>>a[i];
	cin>>t;
	char ch;
	build(1,0,n-1);
	while(t--)
	{
		cout<<"Enter choice : \nu : for update\nq : for query\n";
		cin>>ch;
		
		if(ch=='u')
		{
			cout<<"Enter values of index(1 based) and updated value\n";
			cin>>x>>y;
			x--;
			update(1,0,n-1);
		}
		else
		{
			cout<<"Enter values(1 based) of upper and lower index\n";
			cin>>l>>r;
			l--;
			r--;
			cout<<"\nMINIMUM : "<<query(1,0,n-1);
			cout<<"\n";
		}
		if(t!=0)
	   		cout<<"\n";
		
	}
	return 0;
}