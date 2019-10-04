#include <vector>
#include <iostream>
#include <string>

using namespace std;



vector<int> z_function(string s) {
	int n = (int) s.size();
	
	vector<int> z(n);
	
	int l = 0;
	int r = 0;
	
	for (int i = 1; i < n; ++i) {
		if (i <= r) {
			z[i] = min(r - i + 1, z[i - l]);
		}
		
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			++z[i];
		}
		
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	
	return z;
}



int main() {
	
	
	string s = "wwwwwaawwww";
	
	vector<int> z = z_function(s);
	
	for (int el : z) {
		cout << el << ' ';
	}
	
	cout << endl;
	
	
	return 0;
}
