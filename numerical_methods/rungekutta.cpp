/**
 *  \addtogroup Runge Kutta 4th Method for solving Differential equation
 *  @{
 *  \file
 *  \brief Runge Kutta Method implementation
 *
 *  \author [Rudra Prasad Das](http://github.com/rudra697)
 *
 *  \details
 * It solves the unknown value of y 
 * for a given value of x
 * only first oreder differential equations
 *can be solved
 *  \example
 *  it solves dy/dx=(x-y)/2 at a 
 * given x for given initial 
 * conditions
 * **/
#include<iostream> 
/**
 * @brief The change() function is used 
 * to return the updated iterative value corresponding 
 * to the given function
 * @param x is the value corresponding to the x coordinate
 * @param y is the value corresponding to the y coordinate 
 * @returns the computed function value at that call
 * **/
double change(double x, double y) 
{ 
	double val=((x - y)/2.0); 
	return val;
} 
/**
 *  @brief The rungeKutta finds value of y for 
 * a given x using step size h 
 * and initial value initial x at initial y. 
 * @param init_x is the value of initial x and is updated after each call
 * @param init_y is the value of initial x and is updated after each call
 * @param x is the given value of x
 * @param h is the step value 
 * @returns the value of y at thr required value of x from the initial conditions
 **/
double rungeKutta(double init_x, double init_y, double x, double h) 
{ 
	 /**
	  * Count number of iterations 
	  * using step size or 
	  *  step height h 
	  * **/
	 /**
	  * n calucates the number of iterations
	  * k1,k2,k3,k4 are the Runge Kutta variables 
	  * used for calculation of y at each iteration
	  * **/
	 int n = static_cast<int>((x - init_x) / h); 
    
	double k1=0.0;
	double k2=0.0;
	double k3=0.0;
	double k4=0.0;
	double k5=0.0; 

	/**
	 * Iterate for number of iterations 
	 * **/
	double y = init_y; 
	for (int i=1; i<=n; i++) 
	{ 
		/**
		 * 		
		 *  Apply Runge Kutta Formulas 
		 * to find next value of y 
		 * **/

		k1 = h*change(init_x, y); 
		k2 = h*change(init_x + 0.5*h, y + 0.5*k1); 
		k3 = h*change(init_x + 0.5*h, y + 0.5*k2); 
		k4 = h*change(init_x + h, y + k3); 

		/**
		 * Update next value of y 
		 * **/

		y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

		/**
		 *  Update next value of x 
		 * **/
		init_x = init_x + h; 
	} 

	return y; 
} 

/**
 * @brief Main function
 * @returns 0 on exit 
 * **/
int main() 
{ 
	double x0 = 0;
	double y = 1;
	double x = 2;
	double h = 0.2; 
	std::cout<<"The value of y at x is :"<<rungeKutta(x0, y, x, h); 
	return 0; 
} 
