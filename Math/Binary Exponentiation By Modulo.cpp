#include<iostream>

long long MOD = 1000*1000*1000 + 7;

long long sqr(long long x){
    return (x * x) % MOD;
}

long long binpow(long long x, unsigned long long pw){ // returns x ^ pw
    x %= MOD;
    if(pw == 0)
        return 1; // if(x^pw == 0);
    if(pw % 2 == 1)
        return (x * sqr(binpow(x, pw / 2))) % MOD;
    return sqr(binpow(x, pw / 2));
}

long long binpow_without_recursion(long long x, unsigned long long pw){
    x %= MOD;
    long long res = 1, mul = x;
    while(pw > 0){
        if(pw & 1)
            res *= mul,
            res %= MOD;
        mul = sqr(mul);
        pw >>= 1;
    } 
    return res;
}

int main(){
    //must output 1 because of Fermat's little theorem
    std::cout << binpow(123123, MOD - 1) << std::endl;
    std::cout << binpow_without_recursion(123123, MOD - 1) << std::endl;
    // just random numbers 
    std::cout << binpow(2LL, 23456789098765432LL) << std::endl;
    std::cout << binpow_without_recursion(2LL, 23456789098765432LL) << std::endl;
    std::cout << binpow(23456789876543LL, 2345789875412367123LL) << std::endl;
    std::cout << binpow_without_recursion(23456789876543LL, 2345789875412367123LL) << std::endl;
    
    return 0;
}