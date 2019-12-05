#include<iostream>

using namespace std;

int ary[5][5],completed[5],n,cost=0;

void Input()
{
	int i,j;

	cout<<"Enter the number of CheckPoints: ";
	cin>>n;

	cout<<"\nEnter the Cost Matrix\n";

	for(i=0;i < n;i++)
	{
		cout<<"\nEnter Elements of Row: "<<i+1<<"\n";

		for( j=0;j < n;j++)
			cin>>ary[i][j];

		completed[i]=0;
	}

	cout<<"\n\nThe cost list is:";

	for( i=0;i < n;i++)
	{
		cout<<"\n";

		for(j=0;j < n;j++)
			cout<<"\t"<<ary[i][j];
	}
}

int least(int c)
{
	int i,nc=99;
	int min=99,kmin;

	for(i=0;i < n;i++)
	{
		if((ary[c][i]!=0)&&(completed[i]==0))
			if(ary[c][i]+ary[i][c] < min)
			{
				min=ary[i][0]+ary[c][i];
				kmin=ary[c][i];
				nc=i;
			}
	}

	if(min!=99)
		cost+=kmin;

	return nc;
}

void mincost(int city)
{
	int i,ncity;

	completed[city]=1;

	cout<<city+1<<"--->";
	ncity=least(city);

	if(ncity==99)
	{
		ncity=0;
		cout<<ncity+1;
		cost+=ary[city][ncity];

		return;
	}

	mincost(ncity);
}

int main()
{
	Input();

	cout<<"\n\nThe Path is:\n";
	mincost(0); //passing 0 because starting vertex

	cout<<"\n\nMinimum cost is "<<cost;

	return 0;
}
