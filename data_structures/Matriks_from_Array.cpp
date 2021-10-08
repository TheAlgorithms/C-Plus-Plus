#include <iostream>
using namespace std;

int main()
{
	int A[5], B[5], C[5], D[3][5];
	
	for (int i=1; i<=5; i++)
	{
		cout << "Enter Number A[" << i << "] : ";
		cin >> A[i];
	}
	cout << endl;
	
	for (int i=1; i<=5; i++)
	{
		cout << "Enter Number B[" << i << "] : ";
		cin >> B[i];
	}
	cout << endl;
	
	for (int i=1; i<=5; i++)
	{
		cout << "Enter Number C[" << i << "] : ";
		cin >> C[i];
	}
	cout << endl;
	
	
	for (int i=1; i<=3; i++)
	{
		for (int j=1; j<=5; j++)
		{
			if (i == 1)
			{
				D[i][j] = A[j];
			} else
			if (i == 2)
			{
				D[i][j] = B[j];
			} else
			if (i == 3)
			{
				D[i][j] = C[j];
			}
		}
	}
	
	cout << "List Array A : ";
	for (int i=1; i<=5; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	
	cout << "List Array B : ";
	for (int i=1; i<=5; i++)
	{
		cout << B[i] << " ";
	}
	cout << endl;
	
	cout << "List Array C : ";
	for (int i=1; i<=5; i++)
	{
		cout << C[i] << " ";
	}
	cout << endl << endl;
	
	cout << "Matriks D : " << endl;
	for (int i=1; i<=3; i++)
	{
		for (int j=1; j<=5; j++)
		{
			cout << D[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
