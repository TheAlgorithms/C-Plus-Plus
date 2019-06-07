#include <iostream>
using namespace std;
char *strcat(char *dst, const char *src) {
	char *cp = dst;
	while (*cp) cp++;
	while (*cp++ = *src++)
		;
	return dst;
}

int main() {
	char str[80];
	cin >> str;
	strcat(str, "strings ");
	strcat(str, "are ");
	strcat(str, "concatenated.");
	cout << str << endl;
	return 0;
}
