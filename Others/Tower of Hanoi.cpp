#include <iostream>
using namespace std;

struct tower
{
	int values[10];
	int top;
} F, U, T;

void show()
{
	cout << "\n\n\tF : ";
	for (int i = 0; i < F.top; i++)
	{
		cout << F.values[i] << "\t";
	}
	cout << "\n\tU : ";
	for (int i = 0; i < U.top; i++)
	{
		cout << U.values[i] << "\t";
	}
	cout << "\n\tT : ";
	for (int i = 0; i < T.top; i++)
	{
		cout << T.values[i] << "\t";
	}
}

void mov(tower &From, tower &To)
{
	--From.top;
	To.values[To.top] = From.values[From.top];
	++To.top;
}

void TH(int n, tower &From, tower &Using, tower &To)
{

	if (n == 1)
	{
		mov(From, To);
		show();
	}
	else
	{
		TH(n - 1, From, To, Using);
		mov(From, To);
		show();
		TH(n - 1, Using, From, To);
	}
}

int main()
{
	F.top = 0;
	U.top = 0;
	T.top = 0;

	int no;

	cout << "\nEnter number of discs : ";
	cin >> no;

	for (int i = no; i > 0; i--)
	{
		F.values[F.top++] = i;
	};

	show();
	TH(no, F, U, T);

	return 0;
}
