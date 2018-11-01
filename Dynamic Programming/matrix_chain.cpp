#include<iostream>
using namespace std;
int main()
{
	int p[7]={5,4,3,6,4,2,7};//76
	int s[7][7];
	int m[7][7];
	for(int u=0;u<7;u++)
	{
	m[0][u]=0;
	m[u][0]=0;
	m[u][u]=0;
	s[0][u]=0;
	s[u][0]=0;
	s[u][u]=0;
     }
     m[2][1]=0;
     m[3][1]=0;
     m[3][2]=0;
     m[4][1]=0;
     m[4][1]=0;
     m[4][2]=0;
     m[4][3]=0;
     m[5][1]=0;
     m[5][2]=0;
     m[5][3]=0;
     m[5][4]=0;
     m[6][1]=0;
     m[6][2]=0;
	m[6][3]=0;
	m[6][4]=0;
	m[6][5]=0;
      s[2][1]=0;
     s[3][1]=0;
     s[3][2]=0;
     s[4][1]=0;
     s[4][1]=0;
     s[4][2]=0;
     s[4][3]=0;
      s[5][1]=0;
     s[5][2]=0;
     s[5][3]=0;
     s[5][4]=0;
     s[6][1]=0;
     s[6][2]=0;
	s[6][3]=0;
	s[6][4]=0;
	s[6][5]=0;
	int j,q;
	for(int d=1;d<6;d++)//6(n-1)

	{
		for(int i=1;i<7-d;i++)//7-d
		{
	     j=i+d;
	     int min=3000;
		  for(int k=i;k<j;k++)
		  {
		    q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
		    if(q<min)
		    {
		    	min=q;
		    	s[i][j]=k;
			}
		  }
		  m[i][j]=min;
      	}
	}
	cout<<"\n\nFINAL MATRIX";
	cout<<"\n M matrix";
//	for(int d=1;d<6;d++)//6(n-1)
//	{
//		cout<<"\n";
//		for(int i=1;i<7-d;i++)//7-d
//		{
//	     j=i+d;
//	     cout<<m[i][j]<<"\t";
  //    	}
//	}
	for(int i=0;i<7;i++)
	{
		cout<<"\n";
		for(j=0;j<7;j++)
		{
			cout<<m[i][j]<<"\t";
		}
    }
	cout<<"\n S matrix";
	for(int i=0;i<7;i++)
	{
		cout<<"\n";
		for(j=0;j<7;j++)
		{
			cout<<s[i][j]<<"\t";
		}
	}
	return 0;
}
