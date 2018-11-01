#include<iostream>
using namespace std;
struct edge
{
	int src;
	int dest;
	int cost;
};
struct graph
{
	int v;
	int parent;
    struct edge e; 
};
void heapify(struct graph* g[],int n,int);
void swap(int *,int *);
void create_heap(struct graph g[],int n);
void heapsort(struct graph g[],int ,int ,struct graph b[]);
void sorting(struct graph g[],int ,struct graph b[]);
int main()
{int n,nv;
	cout<<"enter no. of edges";
	cin>>n;
	cout<<"enter no. of vertices";
	cin>>nv;
	struct graph g[n],b[n];
	cout<<"enter names of vertices";
	for(int i=1;i<=nv;i++)
	{
		cin>>g[i].v;
	}
	cout<<"\nenter src of edges";
	for(int i=1;i<=n;i++)
	{
		cin>>g[i].e.src;
	}
	cout<<"\n enter dest of edges";
	for(int i=1;i<=n;i++)
	{
		cin>>g[i].e.dest;
	}
	cout<<"\n enter cost of each edge";
	for(int i=1;i<=n;i++)
	{
		cin>>g[i].e.cost;
	}
	int total_cost;
	int t[n][2];
	
	//CALLING FUNCTION
	sorting(g,n,b);
   
    //PRINTING RESULT
	cout<<"\n graph looks like this";
	cout<<"\nsrc\tdest\tcost";
	for(int i=1;i<=n;i++)
	{
	cout<<"\n"<<b[i].e.src<<"\t"<<b[i].e.dest<<"\t"<<b[i].e.cost;//don't show vertex here
    }
	
	return 0;
}
void sorting(struct graph g[],int n,struct graph b[])
{

  int root=1;
	create_heap(g,n);
	heapsort(g,n,root,b);
    
}
void heapify(struct graph g[],int n,int root)
{
	int left=2*root;
	int right=2*root +1;
	int large=left;
	if(left<=n && right<=n)
	{
		if(g[left].e.cost<g[right].e.cost)
		{
			large=left;
		}
		else
		{
			large=right;
		}
		if(g[large].e.cost>g[root].e.cost)
		{
			large=root;
		}
		if(large!=root)
		{
			swap(&g[root].e.cost,&g[large].e.cost);
			swap(&g[root].e.src,&g[large].e.src);
			swap(&g[root].e.dest,&g[large].e.dest);
		//	swap(&g[root].e,&g[large].e);

			heapify(g,n,large);
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


void create_heap(struct graph g[],int n)
{
	for(int i=(n/2);i>=1;i--)
	{
	heapify(g,n,i);
    }
}


void heapsort(struct graph g[],int n,int root,struct graph b[])
{
	for(int i=1;i<=n;i++)
	{
		b[i].e.cost=g[root].e.cost;
		b[i].e.src=g[root].e.src;
		b[i].e.dest=g[root].e.dest;
		g[root].e.cost=g[n-i+1].e.cost;
		g[root].e.src=g[n-i+1].e.src;
		g[root].e.dest=g[n-i+1].e.dest;

		heapify(g,n-i,root);
	}
}
 void prim()
 {
 	mincost=b[1].e.cost;
 	t[1][1]=b[1].e.src;
 	t[1][2]=b[1].e.dest;
 	int k=b[1].e.src;
 	int l=b[1].e.dest;
 	for(int i=1;i<=n;i++)
 	{
 		if(b[i].e.cost<b[])
	 }
  } 
