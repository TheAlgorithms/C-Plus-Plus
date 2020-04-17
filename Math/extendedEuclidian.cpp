#include <iostream>
#include <algorithm>

using namespace std;

/*
    for numbers a, b returns x, y such as x * a + y * b = gcd(a,b)
*/

pair<int,int> extendedEuclidian(int a, int b) {
	int a_old = a, b_old = b;
	if(a < b) swap(a,b);

	int x = 0, y = 1, old_x = 1, old_y = 0;

	int quotient, residue;
	while (b) {
		quotient = a / b;
		residue = a % b;

		a = b;
		b = residue;

		int temp;

		temp = x;
		x = old_x - quotient * x;
		old_x = temp;
		

		temp = y;
		y = old_y - quotient * y;
		old_y = temp;
	}

	if(b_old > a_old) swap(old_x, old_y);

	return make_pair(old_x, old_y); 

}

int main() {

	int a, b;
	cin >> a >> b;
	pair<int,int> result = extendedEuclidian(a, b);

	cout<< result.first << " " << result.second;


}