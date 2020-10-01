/*
 * \brief Solve the equation \f$f(x)=0\f$ using [Secant
 * method](https://en.wikipedia.org/wiki/Secant_method)
 *
 * Given an equation f(x).
 * Primary condition for secant method convergence is a and b should be closer to the root. 
 * It implies that smaller the interval precision is higher.
 * We first find an interval (a,b) such that f(a)*f(b) < 0.
 * It ensures that there is a one root between a and b.
 * We find multiple roots in multiple interval by separate function calls.
 * equation used for iterations is :
   x_(n) = x_(n-2) - (x_(n-2)-x_(n-1))*(f(x_(n-2)))/(f(x_(n-2))-f(x_(n-1)))
 * The Process is continued till a close enough approximation is achieved.
 */
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;

#define RANGE 100000  ///< Range in which we have to find the root. (-Range,Range)
#define GAP 0.5 /// interval gap. lesser the gap more the accuracy

/** define equation to find root for
 */
static double eq(double x) {
    return (x*x-x);  // original equation
}
//function for finding root in an interval
static double secant(double x1,double x2,double y1,double y2){
    double diff = x1-x2;
    if(diff<0){
        diff= (-1)*diff;
    }
    if(diff<0.000001){  // 0.000001 is the precision constant.
        if(y1<0){
            y1=-y1;
        }
        if(y2<0){
            y2=-y2;
        }
        if(y1<y2){
            return x1;
        }
        else{
            return x2;
        }
    }
    double x3=0,y3=0;
    x3 = x1 - (x1-x2)*(y1)/(y1-y2);
    y3 = eq(x3);
    return secant(x2,x3,y2,y3);   //recursive call for next iteration.
}
//function for printing roots
void printRoot(double root,int COUNT){
    if(COUNT==1){
        cout << "Your 1st root is : " << root << endl;
    }
    else if(COUNT==2){
        cout << "Your 2nd root is : " << root << endl;
    }
    else if(COUNT==3){
        cout << "Your 3rd root is : " << root << endl;
    }
    else{
        cout << "Your "<<COUNT<<"th root is : " << root << endl;
    }
}


/** main function */
int main() {
    double a, b, i,root=0;
    int COUNT=0;
    a = eq((-1)*RANGE);
    i=((-1)*RANGE + GAP);
    //taking an interval with appropriate gap and finding roots in that interval
    while(i<=RANGE){
        b = eq(i);
        if(b==0){
            COUNT++;
            printRoot(i,COUNT);
        }
        if(a*b<0){
            root = secant(i-GAP,i,a,b);
            COUNT++;
            printRoot(root,COUNT);
        }
        a=b;
        i = i + GAP;
    }
    return 0;
}
