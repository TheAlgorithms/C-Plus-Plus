#include <iostream>
using namespace std;
int min(int input1, int input2)
{
	if (input1 <= input2)
		return input1;
	else
		return input2;
}
int main()
{
	int input1, input2;
	cin >> input1 >> input2;

	cout << min(input1, input2) << endl;

	return 0;
}
