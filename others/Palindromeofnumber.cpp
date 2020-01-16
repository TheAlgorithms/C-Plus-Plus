#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int num;
	cout << "Enter number = ";
	cin >> num;

	string s1 = to_string(num);
	string s2 = s1;

	reverse(s1.begin(), s1.end());

	if (s1 == s2)
		cout << "true";
	else
		cout << "false";

	return 0;
}
