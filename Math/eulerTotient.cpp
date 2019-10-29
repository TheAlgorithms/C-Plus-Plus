#include<iostream>
#include<cmath>
using namespace std;

/*
this function calculate euler totien function
*/

long long eulerTotient(long long n){
    
    if(n == 1) return 1;
    long long result = 1LL;
    long long temp = n;
    for(int i = 2; i <= floor(sqrt(n)) + 10; i++) {
        if( temp % i == 0) {
            int j = 0;
            while(temp % i == 0){
                j ++;
                temp /= i;
            }
            result = result * pow(i,j-1) * (i-1);
        }
    }

    if(temp == n){
        return n-1;
    }

    return result;
}

int main(){
    long long n;
    cin >> n;
    cout << eulerTotient(n);

}