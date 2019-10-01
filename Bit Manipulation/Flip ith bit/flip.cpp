#include <iostream>
using namespace std;
int main(){
    int n, i;
    cin >> n >> i;
    n = n ^ (1<<i);
    cout << n;
    return 0;
}