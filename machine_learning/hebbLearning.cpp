#include<iostream>
using namespace std;

int main()
{
	int  m,n;
	cout<<"enter no.of features and no.of training datasets: \n";
	cin>> m>>n;

	int wt1[m], wt2[m];
	
	int input[n][m];
	cout<<"enter the input matrix row wise "<<endl;

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>input[i][j];
		}
	}

	int target1[n], target2[n];

	cout<<" Enter the target in binary : "<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>target1[i];
	}

	cout<<"Enter the target in bipolar: "<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>target2[i];
	}

	for(int i=0;i<m;i++)
	{
		wt1[i]=0; //step 1: initialise all wts to 0
		wt2[i]=0;
	}

	for(int j=0;j<n;j++) //step 2: for each training vector on target pair do steps 3 to 5
	{//step 3: x_0 = 1 and xi = si
		cout<<"###########j="<<j<<endl;
		for(int i=0; i<m;i++)
		{
			//step 4: y_out = T_i 
			//step 5: adjust the weights as WT_new= WT_old + (x_i*y_out)
			wt1[i]+= (input[j][i]*target1[j]);
			cout<<"weight1 at i="<<i<<" is "<<wt1[i]<<endl;
			wt2[i]+= (input[j][i]*target2[j]);
			cout<<"wt2 at i="<<i<<" is "<<wt2[i]<<endl;

		}
	
	}
	cout<<"************OUTPUT**************\nafter 1 epoch: binary weights: "<<endl;

	for (int i = 0; i < m; ++i)
	{
		/* code */
		cout<<wt1[i]<<" ";
	}
	cout<<"\nafter 1 epoch: bipolar weights: "<<endl;

	for (int i = 0; i < m; ++i)
	{
		/* code */
		cout<<wt2[i]<<" ";
	}



	return 0;
}