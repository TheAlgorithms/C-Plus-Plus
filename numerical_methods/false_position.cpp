/**
 * \file
 * \brief Solve the equation \f$f(x)=0\f$ using [false position
 * method](https://en.wikipedia.org/wiki/Regula_falsi), also known as the Secant
 * method
 *
 * First, multiple intervals are selected with the interval gap provided. 
 * Separate recursive function called for every root.
 * Roots are printed Separatelt.
 *
 * For an interval [a,b] \f$a\f$ and \f$b\f$ such that \f$f(a)<0\f$ and
 * \f$f(b)>0\f$, then the \f$(i+1)^\text{th}\f$ approximation is given by: \f[
 * x_{i+1} = \frac{a_i\cdot f(b_i) - b_i\cdot f(a_i)}{f(b_i) - f(a_i)}
 * \f]
 * For the next iteration, the interval is selected
 * as: \f$[a,x]\f$ if \f$x>0\f$ or \f$[x,b]\f$ if \f$x<0\f$. The Process is
 * continued till a close enough approximation is achieved.
 *
 * \see newton_raphson_method.cpp, bisection_method.cpp
 */
#include <cmath>      // For math operations
#include <iostream>   // For io operations

/** define \f$f(x)\f$ to find root for
 */
static double eq(double x) {
    return (x*x-x);  // original equation
}

/**
* @brief This function finds root of the equation in given interval i.e. (x1,x2).
* @param x1,x2 values for an interval in which root is present.
  @param y1,y2 values of function at x1, x2 espectively.
* @return root of the equation in the given interval.
*/  
static double regula_falsi(double x1,double x2,double y1,double y2){
    double diff = x1-x2;
    if(diff<0){
        diff= (-1)*diff;
    }
    if(diff<0.00001){          
        if(y1<0)
        y1=-y1;
        if(y2<0)
        y2=-y2;
        if(y1<y2)
        return x1;
        else
        return x2;
    }
    double x3=0,y3=0;
    x3 = x1 - (x1-x2)*(y1)/(y1-y2);
    y3 = eq(x3);
    return regula_falsi(x2,x3,y2,y3);
}

/**
* @brief This function prints roots of the equation.
* @param root which we have to print. 
* @param count which is count of the root in an interval [-range,range].
*/  
void printRoot(double root,int count){
    if(count==1){
        std::cout << "Your 1st root is : " << root << std::endl;
    }
    else if(count==2){
        std::cout << "Your 2nd root is : " << root << std::endl;
    }
    else if(count==3){
        std::cout << "Your 3rd root is : " << root << std::endl;
    }
    else{
        std::cout << "Your "<<count<<"th root is : " << root << std::endl;
    }
}


/**
* @brief Main function
* @returns 0 on exit
*/
int main() {
    double a=0, b=0,i=0,root=0;
    int count=0;
    int range = 100000;        //Range in which we have to find the root. (-range,range)
    double gap = 0.5;          //interval gap. lesser the gap more the accuracy
    a = eq((-1)*range);
    i=((-1)*range + gap);
    //while loop for selecting proper interval in provided range and with provided interval gap.
    while(i<=range){
        b = eq(i);
        if(b==0){
            count++;
            printRoot(i,count);
        }
        if(a*b<0){
            root = regula_falsi(i-gap,i,a,b);
            count++;
            printRoot(root,count);
        }
        a=b;
        i+=gap;
    }
    return 0;
}

