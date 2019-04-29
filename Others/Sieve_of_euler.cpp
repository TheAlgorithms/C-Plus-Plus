/*
 * A better way to find prime number than sieve of eratosthenes
 *
 * Time Complexity : O(N)
 * Space Compexity : O(N)
 *
 */
#include <iostream>
using namespace std;

const int size = 1e2+5; // default size, must not less than n 

int n = 100; // the upper bound of range about prime number you want to find, default 100
bool vis[size]; // mark whether current index is a [prime number] => (false) or [composite number] => (true)
int prime[size]; // store prime number, for space optimization, use vector instead
int cnt = 0; // amount of prime number in range => [2,n]


void sieve_of_euler(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) 
            prime[cnt++] = i;
        for(int j = 0; j<cnt && i*prime[j]<=n ; ++j) {
            vis[i*prime[j]] = true;
            if(i % prime[j] == 0)
                break;
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve_of_euler(n);
    for(int i = 0; i < cnt; ++i)
        cout << prime[i] << endl;
    return 0;
}