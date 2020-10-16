/**
 * \addtogroup Runge Kutta 4th Method for solving Differential equation
 * @{
 * \file
 * \brief [Runge Kutta](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) method implementation
 *
 * \author [Rudra Prasad Das](http://github.com/rudra697)
 *
 * \details
 * It solves the unknown value of y 
 * for a given value of x
 * only first oreder differential equations
 * can be solved
 * \example
 * it solves dy/dx=(x-y)/2 at a 
 * given x for given initial 
 * conditions
 * There can be many such equations 
 * **/
#include<iostream> /// for io operations
#include<cassert>  /// asserting the test functions
/**
 * @namespace numerical_methods
 * @brief Numerical Methods
 */
namespace numerical_methods {
/**
 * @namespace runge_kutta
 * @brief Functions for [Runge Kutta](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) method
 */
namespace runge_kutta {
/**

 * @brief The change() function is used 
 * to return the updated iterative value corresponding 
 * to the given function
 * @param x is the value corresponding to the x coordinate
 * @param y is the value corresponding to the y coordinate 
 * @returns the computed function value at that call
 */
double change(double x, double y) 
{ 
	double val=((x - y)/2.0); 
	return val;
} 
/**
 * @brief The rungeKutta finds value of y for 
 * a given x using step size h 
 * and initial value initial x at initial y. 
 * @param init_x is the value of initial x and is updated after each call
 * @param init_y is the value of initial x and is updated after each call
 * @param x is the given value of x
 * @param h is the step value 
 * @returns the value of y at thr required value of x from the initial conditions
 */
double rungeKutta(double init_x, double init_y, double x, double h) 
{ 
	 
	  // Count number of iterations 
	  //using step size or 
	  // step height h 
	  
	 
	  // n calucates the number of iterations
	  // k1,k2,k3,k4 are the Runge Kutta variables 
	  // used for calculation of y at each iteration
	  
	 int n = static_cast<int>((x - init_x) / h); 
    
	double k1=0.0;
	double k2=0.0;
	double k3=0.0;
	double k4=0.0;
	double k5=0.0; 
	
	 // Iterate for number of iterations 
	 
	double y = init_y; 
	for (int i=1; i<=n; i++) 
	{ 
						
		 // Apply Runge Kutta Formulas 
		 // to find next value of y 
		
		k1 = h*change(init_x, y); 
		k2 = h*change(init_x + 0.5*h, y + 0.5*k1); 
		k3 = h*change(init_x + 0.5*h, y + 0.5*k2); 
		k4 = h*change(init_x + h, y + k3); 
		
		// Update next value of y 
		
		y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
		
		// Update next value of x 
		
		init_x = init_x + h; 
	} 

	return y; 
} 
/**
 * @brief the functions are for self test
 * @returns void and prints the success of rungeKutta function
 */
	void test1()
	{
		std::cout << "Test 1...." << "\n";
		double valfirst=rungeKutta(2,3,4,0.2); // Tests the function with pre calculated values
		assert(valfirst==3.10364);
		std::cout << "Passed Test 1\n";
	}
	void test2()
	{
		std::cout << "Test 2...." << "\n";
		double valsec=rungeKutta(1,2,5,0.1);  // The value of step changed
		assert(valsec==3.406);
		std::cout << "Passed Test 2\n";
	}
	void test3()
	{
		std::cout << "Test 3...." << "\n";
		double valfirst=rungeKutta(-1,3,4,0.1); // Tested with negative value
		assert(valfirst==2.49251);
		std::cout << "Passed Test 3\n";
	}
} // namespace runge_kutta
} // namespace numerical_methods

/**
 * @brief Main function
 * @returns 0 on exit 
 */
int main() 
{ 
	std::cout << "The Runge Kutta function will be tested on the basis of precomputed values\n";
	numerical_methods::runge_kutta::test1();
	numerical_methods::runge_kutta::test2();
	numerical_methods::runge_kutta::test3();
	return 0; 
} 
