#include <iostream>
using namespace std;
int strlen(char *input)
{
	int i;
	for (i = 0; input[i] != NULL; i++);
	return i;

}
int main()
{
	char input[100];
	cin >> input;

	cout << strlen(input) << endl;

	return 0;
}
