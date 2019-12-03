#include <iostream>
#include <vector>
using namespace std;

vector<int> primes(int max) {
    max++;
    vector<int> res;
    vector<bool> numbers(max, false);
    for (int i = 2; i < max; i++) {
        if (!numbers[i]) {
            for (int j = i; j < max; j += i) 
                numbers[j] = true;
            res.push_back(i);
        }
    }
    return res;
}

int main() {
    cout << "Calculate primes up to:\n>> ";
    int n;
    cin >> n;
    vector<int> ans = primes(n);
    for (int i = 0; i < ans.size(); i++) 
        cout << ans[i] << ' ';
    cout << endl;
}
