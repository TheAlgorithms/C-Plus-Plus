#include<iostream>
using namespace std;

struct sack
{
	int profit;
	int weight;
	int ratio;
};

void heapify(struct sack* a[],int n,int);
void swap(int *,int *);
void create_heap(struct sack a[],int n);
void heapsort(struct sack a[],int ,int ,struct sack b[]);
void sorting(struct sack a[],int ,struct sack b[]);
void knapsack(struct sack b[],int ,int ,int x[]);

int main()
{
	int n,capacity;
	cout<<"enter total capacity of knapsack";
	cin>>capacity;
	cout<<"\nenter no. of elements to be entered";
	cin>>n;
	struct sack a[n],b[n];
	int x[n];//check how can we allocate variable size to x array
	cout<<"\nenter profit of every item";

	for(int i=1;i<=n;i++)
	{
		cin>>a[i].profit;
	}
	cout<<"\nenter weight of every item";//check whtwher we can enter data in structure in one loop

	for(int i=1;i<=n;i++)
	{
		cin>>a[i].weight;
	}
	cout<<"\n calculating ratio\n";
	for(int i=1;i<=n;i++)
	{
		a[i].ratio=a[i].profit/a[i].weight;
		cout<<a[i].ratio<<"\t";
	}
	sorting(a,n,b);
	knapsack(b,capacity,n,x);
	cout<<"\n\n KNAPSACK VALUE";
	for(int i=1;i<=n;i++)
	{
		cout<<x[i]<<"\t";
	}
	
	return 0;
}
void knapsack(struct sack b[],int capacity,int n,int x[])
{
	int rem;
	int sum=0,i=0;
	float fraction;
	while(sum<capacity && i<=n)
	{
		rem=capacity-sum;
		if(b[i].weight>rem)
		{
			fraction=rem/b[i].weight;
			x[i]=fraction;
			sum=sum+fraction*b[i].weight;
		}
		else
		{
			x[i]=1;
			sum=sum+b[i].weight;
		}
		i++;
	}
}
void sorting(struct sack a[],int n,struct sack b[])
{
//	int ratio[n];
//	for(int i=0;i<=n;i++)
//	{
//	ratio[i]=a[i].profit/a[i].weight;
  //  }
  int root=1;
	create_heap(a,n);
	heapsort(a,n,root,b);
    
}
void heapify(struct sack a[],int n,int root)
{
	int left=2*root;
	int right=2*root +1;
	int large=left;
	if(left<=n && right<=n)
	{
		if(a[left].ratio>a[right].ratio)
		{
			large=left;
		}
		else
		{
			large=right;
		}
		if(a[large].ratio<a[root].ratio)
		{
			large=root;
		}
		if(large!=root)
		{
			swap(&a[root].ratio,&a[large].ratio);
			swap(&a[root].weight,&a[large].weight);
			swap(&a[root].profit,&a[large].profit);// doesn't need
			heapify(a,n,large);
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
void create_heap(struct sack a[],int n)
{
	for(int i=(n/2);i>=1;i--)
	{
	heapify(a,n,i);
    }
}
void heapsort(struct sack a[],int n,int root,struct sack b[])//we can use b array of consisting weight only
{
	for(int i=1;i<=n;i++)
	{
		b[i].profit=a[root].profit;
		b[i].weight=a[root].weight;//only this one is needed
		b[i].ratio=a[root].ratio;
		a[root].ratio=a[n-i+1].ratio;//only this one is needed
		a[root].profit=a[n-i+1].profit;
    	a[root].weight=a[n-i+1].weight;
		heapify(a,n-i,root);
	}
}
 
