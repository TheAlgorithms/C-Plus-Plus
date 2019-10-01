#include <iostream>
using namespace std;
int clearAllBits(int n, int i){
    int mask = (1<<i) - 1;
    return n&mask;
}
int main() {
	int n, i;
	cin >> n >> i;
	cout<< clearAllBits(n, i) <<endl;
	return 0;
}

