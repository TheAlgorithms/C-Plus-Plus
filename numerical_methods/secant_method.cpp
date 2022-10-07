/**
* \file
* \brief Solve the equation \f$f(x)=0\f$ using
* [Secant Method](https://en.wikipedia.org/wiki/Secant_method)
*
* The example function \f$f(x)\f$ looks like this:
* \f[
* x^4 - 29 = 0
* \f]
*
* \author [Fatih Küçükkarakurt](https://github.com/fkkarakurt)
*/

/**
* @brief Secant Method for the root of f(x)
* Analytically the solution is
* \f[
* x^4-29 = 0
* x = 29^(1/4) = 2,3205957871060836757951626724362...
* \f]
*/

#include <cmath> /// for built-in mathematical functions
#include <iomanip> /// to identify the manipulator and setprecision
#include <iostream> /// for IO operations

/**
* @brief Definition the f(x) fuction
* @param x unknown x value
*/
double f(double x) { return x * x * x * x - 29.0; } // The Function f(x)

/**
* @brief Main function
* @returns 0 on exit
*/
int main() {
   /**
    * @brief Information required for the secant method
    * @param x0 The Initial value
    * @param x1 The Second value
    * @param tolerance Tolerance range of the situation to be analyzed
    */
   double x1 = 5, x0 = 4, tolerance = 1.0E-12;

   // You can change the setprecision(20) value and ,
   // get results with the float values you want.
   std::cout << std::setprecision(20) << std::fixed;

   /// Start Secant Method
   do {
       double error = (x1 - x0) / (f(x1) - f(x0)) * f(x1); // Estimate the error

       // Printing the error on the screen
       std::cout << "Root = " << x1 << std::setw(5) << " Error = " << error << std::endl;
       // With setw(n), a cleaner and clearer image is obtained on the console screen.
       // You can change the "n" value as you wish.

       /**
        * @brief Comparison of Error with Tolerance
        * @note The tolerance value determines the number of iterations.
        * That is, the aim is that the error does not exceed the specified tolerance.
        */
       if (abs(error) < tolerance)
           break;         // Terminate if the tolerance is satisfied
       x0 = x1;         // Improve x0
       x1 = x1 - error; // Improve x1
   } while (1);
   return 0;
}
