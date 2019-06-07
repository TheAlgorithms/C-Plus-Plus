#include <iostream>
using namespace std;
char *strcpy(char *dest, char *source)
{
	int i;
	for ( i = 0; source[i]; i++)
		dest[i] = source[i];
	dest[i] = NULL;
	return dest;
}
int main()
{
	char input[100];
	cin >> input;

	char dest[100];
	strcpy(dest, input);
	cout << dest << endl;

	return 0;
}
