#include <iostream>
#include <math.h>
using namespace std;

double f(double x) {//can add your own function
    return cos(x) - x*exp(x);
}

void bisection(double x, double y, double error = 0.00001) {
    static bool flag = false;//to make sure the 'invalid interval' message is printed correctly
    if(f(x)*f(y) >= 0) {
        if(flag == false) cout << "The interval [a,b] provided is not valid" << endl;
        return;
    }

    flag = true;
    double z = (x+y)/2;
    if(abs(x-y) <= error) {
        cout << "The approximate root is : " << z << endl;
        return;
    }

    if(f(z) == 0.0) {
        cout << "The root is : " << z << endl;
        return;
    }
    else {
        if(f(x)*f(z) < 0) bisection(x, z, error);
        else if(f(z)*f(y) < 0) bisection(y, z, error);
        else {
            cout << "The given function does not follow the required assumtions" << endl;
            return;
        }
    }
}

int main(void) {
    double a, b;
    cout << "Enter the two guesses : " << endl;
    cin >> a;
    cin >> b;
    bisection(a, b);
}