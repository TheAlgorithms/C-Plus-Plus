//code for subset sum problem
/* In this problem we're given an array and a sum here we've to find that is it 'possible to have the given sum using some or all 
   elements of that array.
   if possible
          print YES
   else 
          NO
*/

/*
  arr = {1,2,3,4}
  sum = 3
  output => YES  (3) or (1+2)
*/

#include<iostream.h>
#define M 1001
using namespace std;

int t[M][M];   //for the size of the array look at constraints

bool Subset_Sum(vector<int> &arr, int sum, int n)
{
	//initialization
	for(int i=0; i<M; i++)
		t[0][i] = 0;
	for(int i=0; i<n; i++)
		t[i][0] = 1;
	//choice diagram
	for(int i=1; i<n+1; i++)
	{
		for(int j=1; j<sum+1; j++)
		{
			if(j>=arr[i-1])
			{
				t[i][j] = (t[i-1][j]||t[i-1][j-arr[i-1]]);
			}
			else
				t[i][j] = t[i-1][j];
		}
	}
	return t[n][sum];
}

int main()
{
	int n,sum;
	cin>>n>>sum;
	vector<int> arr(n);
	for(int i=0; i<n; i++)
		cin>>arr[i];
	memset(t,0,sizeof(t));
	if(Subset_Sum(arr,sum,n))
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl;
	return 0;
}
