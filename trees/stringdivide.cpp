// C++ program to understand the use of getline() function

#include <bits/stdc++.h>
using namespace std;

int main()
{
	string S, T;
cout<<"enter"<<endl;
	getline(cin, S);

	stringstream X(S);

	while (getline(X, T, ' ')) {
		cout << T << endl;
	}

	return 0;
}
