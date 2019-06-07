#include<iostream>
using namespace std;
int abs(int input)
{
	if (input >= 0)
		return input;
	else
		return -input;
}
int main()
{
	int input;
	cin >> input;
	cout << abs(input) << endl;
	return 0;
}
