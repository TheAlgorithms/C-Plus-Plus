#include <iostream>

using namespace std;

int gcd(int a, int b) {
  while(a != 0 && b != 0) {
    if(a<b) {
      b %= a;
    }
    else {
      a %= b;
    }
  }

  int gcd = (a==0)? b : a;

  return gcd;
}

long long int lcm(int a, int b) {

	long long int lcm = ((long long int)(a*b))/gcd(a, b);

	return lcm;
}


int main() {
  int a, b;
  cin >> a >> b;
  cout << lcm(a, b) << endl;
  return 0;
}
