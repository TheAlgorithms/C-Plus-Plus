#include <iostream>
using namespace std;
double floor(double input)
{
	return (int)input;
}
int main()
{
	double input;
	cin >> input;
	cout << floor(input) << endl;


	return 0;
}
