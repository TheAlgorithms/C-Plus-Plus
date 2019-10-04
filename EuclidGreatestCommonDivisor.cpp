/*Euclid's Algorithim  for the greatest common divisor of two numbers*/

#include <iostream>
using namespace std;

int main() {

	int x;
	int y;
	
	cout << "Introduce the first number" << endl;
	cin >> x;
	cout << "Introduce the second number" << endl;
	cin >> y;

	while (y != 0) {
		if (x <= y) {
			y = y - x;
		}
		else
			x = x - y;
	}

	cout << "gcd " << "( " << x << "," << y << " )" << ": " << x;

	return 0;
}

