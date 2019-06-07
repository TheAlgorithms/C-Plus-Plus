#include <iostream>
using namespace std;
int max(int input1, int input2)
{
	if (input1 >= input2)
		return input1;
	else
		return input2;
}
int main()
{
	int input1, input2;
	cin >> input1 >> input2;

	cout << max(input1, input2) << endl;

	return 0;
}
