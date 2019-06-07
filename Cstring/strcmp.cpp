#include <iostream>
using namespace std;
int strcmp(const char *s1, const char *s2) {
	int ret = 0;
	while (!(ret = *(unsigned char *)s1 - *(unsigned char *)s2) && *s2)
		++s1, ++s2;

	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;

	return ret;
}
int main() {
	char szKey[] = "apple";
	char szInput[80];
	do {
		cout <<"Guess my favourite fruit? ";
		cin >>szInput;
	} while (strcmp(szKey, szInput) != 0);

	cout << "Correct answer!" << endl;
	return 0;
}
