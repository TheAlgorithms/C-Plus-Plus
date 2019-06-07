#include<iostream>
using namespace std;
long atoi(char *input)
{
	long result = 0;
	for (int i = 0; input[i]; i++)
	{
		result *= 10;
		result += input[i] - '0';
	}
	return result;
}
int main()
{
	char input[10000];
	cin >> input;
	cout << atoi(input) << endl;
	return 0;
}
