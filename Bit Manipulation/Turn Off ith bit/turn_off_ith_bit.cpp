#include <iostream>
using namespace std;
int turnOffIthBit(int n, int i){
    if(n & (1<<i)){
        return n-(1<<i);
    }
    return n;
}
int main() {
	int n, i;
	cin >> n >> i;
	cout<< turnOffIthBit(n, i) <<endl;
	return 0;
}

