#include <iostream>
using namespace std;
size_t strspn(char *string,char *control) {
	 char *str = string;
	 char *ctrl = control;
	 char map[32];
	int count;  // Clear out bit map
	for (count = 0; count < 32; count++)
		map[count] = 0;  // Set bits in control map
	while (*ctrl) {
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
		ctrl++;
	}  // 1st char NOT in control map stops search
	if (*str) {
		count = 0;
		while (map[*str >> 3] & (1 << (*str & 7))) {
			count++;
			str++;
		}
		return count;
	}
	return 0;
}
int main() {
	int i;
	char strtext[] = "129th";
	char cset[] = "1234567890";

	i = strspn(strtext, cset);
	cout << "The length of initial number is " << i << endl;
	return 0;
}
