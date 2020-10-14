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
 *  A sample differential equation "dy/dx = (x - y)/2" 
 * Can be any transcendental equation 

**/
float change(double x, double y) 
{ 
	return((x - y)/2); 
} 
/**
 * 
 *  Finds value of y for 
 * a given x using step size h 
 * and initial value initial x at initial y. 

 **/
float rungeKutta(double init_x, double init_y, double x, double h) 
{ 
	 /**
	  * Count number of iterations 
	  * using step size or 
	  *  step height h 
	  * **/
	 
	 int n = static_cast<int>((x - init_x) / h); 

	double k1;
	double k2;
	double k3;
	double k4;
	double k5; 

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
 *  Driver method 
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
