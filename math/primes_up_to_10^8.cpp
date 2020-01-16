#include<iostream>
#include <cstring>

char prime[100000000];

void Sieve(int64_t n) {
    memset(prime, '1', sizeof(prime));  // intitize '1' to every index
    prime[0] = '0';  // 0 is not prime
    prime[1] = '0';  // 1 is not prime
    for (int p = 2; p * p <= n; p++) {
        if (prime[p] == '1') {
            for (int i = p * p; i <= n; i += p)
                prime[i] = '0';  // set all multiples of p to false
        }
    }
}


int main() {
    Sieve(100000000);
    int64_t n;
    std::cin >> n;  // 10006187
    if (prime[n] == '1')
        std::cout << "YES\n";
    else
        std::cout << "NO\n";
}
