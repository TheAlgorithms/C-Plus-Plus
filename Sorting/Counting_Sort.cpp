#include <iostream>
#include<stdlib.h>  // for malloc
using namespace std;

void Print(int Arr[], int N)
{
	for (int i = 0; i < N; i++)
	{
		
	    if(i!=(N-1))   // not to print last comma
		cout << *(Arr+i) << ", ";
		else
		cout << *(Arr+i) ;
	}
}

int *Counting_Sort(int Arr[], int N)
{

	for(int i=0;i<N;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(*(Arr+i)>*(Arr+j))
            { 
                int temp;
                temp=*(Arr+i);
                *(Arr+i)=*(Arr+j);
                *(Arr+j)=temp;
            }
        }
    }
    int *Sorted_Arr=Arr;

	return Sorted_Arr;
}

int main()
{

	int  n ;
	cout<<"\tEnter Number Of Array Elements\t ";
	cin>>n;
	
	int *Arr=(int*)malloc(sizeof(int)*n);
	cout<<"\tEnter The Array :  \n";
	for(int i=0;i<n;i++)
	{
	 cout<<"\t\t\t ";	
	 cin>>*(Arr+i);
    }
	
	int *Sorted_Arr=(int*)malloc(sizeof(int)*n);

	cout << "\n\tOrignal Array = ";
	Print(Arr, n);
	
	Sorted_Arr = Counting_Sort(Arr, n);
	cout << "\n\t Sorted Array(In Dcreasing Order) = ";
	Print(Sorted_Arr, n);
	
	cout << "\n\t Sorted Array(In Inceasing Order) = ";
	for (int i = n-1; i >= 0; i--)
	{
		
	    if(i!=0)   // not to print last comma
		cout << *(Arr+i) << ", ";
		else
		cout << *(Arr+i) ;
	}
	
	free(Arr);
	free(Sorted_Arr);
	
	cout << endl;

	return 0;
}
