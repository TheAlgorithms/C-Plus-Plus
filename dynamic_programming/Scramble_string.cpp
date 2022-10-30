#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> ump;

bool Solve(string X, string Y) {
	string key = X + " " + Y;
	if (ump.find(key) != ump.end()) // if we did not found the and travesed upto end of the map 
		return ump[key];

	if (X.compare(Y) == 0) {
		ump[key] = true;
		return true;
	}
	if (X.length() <= 1) {
		ump[key] = false;
		return false;
	}

	int n = X.length();
	int flag = false;
	for (int i = 1; i <= n - 1; i++) {
		if ((Solve(X.substr(0, i), Y.substr(n - i, i)) && Solve(X.substr(i), Y.substr(0, n - i))) ||
		        (Solve(X.substr(0, i), Y.substr(0, i)) && Solve(X.substr(i), Y.substr(i)))) {
			flag = true;
			break;
		}
	}

	return ump[key] = flag; // store in table for further reference 
}

int main() {
	string X, Y; cin >> X >> Y;

	ump.clear();

	if (X.length() != Y.length())
		cout << "No\n";
	else
		Solve(X, Y) ? cout << "Yes\n" : cout << "No\n";
	return 0;
