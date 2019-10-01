#include <iostream>
using namespace std;
int convert(int n){
    int res = 0;
    unsigned int mask = 1<<15;
    while(mask > 0){
        res *= 10;
        if(n & mask) res += 1;
        else res += 0;
        mask = mask >> 1;
    }
    return res;
}
int main(){
    int n;
    cin >> n;
    cout << convert(n);
    return 0;
}