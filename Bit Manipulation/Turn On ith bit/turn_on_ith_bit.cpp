#include <iostream>
using namespace std;
int turnOnIthBit(int n, int i){
    if(n & (1<<i))
        return n;
    else
        return n+(1<<i);
}
int main() {
	int n, i;
	cin >> n >> i;
	cout<< turnOnIthBit(n, i) <<endl;
	return 0;
}

