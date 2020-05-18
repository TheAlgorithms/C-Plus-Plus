#include <iostream>
using namespace std;

// Finding coefficients of a and b ie x and y in gcd(a, b) = a * x + b * y 

int d, x, y;

void extendedEuclid(int A, int B) {
    if(B == 0) {
        d = A;
        x = 1;
        y = 0;
    }// d is gcd(a, b)
    else {
        extendedEuclid(B, A%B);
        int temp = x;
        x = y;
        y = temp - (A/B)*y;
    }
}


int main(){
    int a, b;
    cin >> a >> b;
    extendedEuclid(a, b);
    cout << x << " " << y << endl;
    //gcd(a, b) = a * x + b * y
    return 0;
}
