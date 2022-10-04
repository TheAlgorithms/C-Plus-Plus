// backtracking basic code to print numbers from 1 to N
// basic backtracking code

#include <bits/stdc++.h>
using namespace std;
 
#define int long long

void print(int n){
    if (n <= 0) {
        return;
    }
    else {
        print(n - 1);
        // now we backtrack the control flow statement using non-tail recursion
        cout << n << " ";
    }
}
 
signed main() {
    int n;
    cin>>n;
    print(n);
    return 0;
}
