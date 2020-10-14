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
float change(float x, float y) 
{ 
	return((x - y)/2.0); 
} 
/**
 * 
 *  Finds value of y for 
 * a given x using step size h 
 * and initial value initial x at initial y. 

 **/
float rungeKutta(float init_x, float init_y, float x, float h) 
{ 
	 /**
	  * Count number of iterations 
	  * using step size or 
	  *  step height h 
	  * **/
	 
	 int n = static_cast<int>((x - init_x) / h); 

	float k1=0.0;
	float k2=0.0;
	float k3=0.0;
	float k4=0.0;
	float k5=0.0; 

	/**
	 * Iterate for number of iterations 
	 * **/
	float y = init_y; 
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
	float x0 = 0;
	float y = 1;
	float x = 2;
	float h = 0.2; 
	std::cout<<"The value of y at x is :"<<rungeKutta(x0, y, x, h); 
	return 0; 
} 
