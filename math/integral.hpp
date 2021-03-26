#pragma once
#include <cassert>
//A function to find the integral of a function on the interval [a, b]
//Uses a Riemann sum with trapezoids rather than rectangles
//NOTE: implementation requires a <= b

template<typename R, typename I> //I is input type, R is return type. I and R must be floats or doubles
R integral(I a, I b, R (*f)(I), unsigned subdivisions) {
	assert(a <= b);
	R result = 0;
	I dx = (b - a)/subdivisions; //(width of trapezoid)
	for(; a < b; a += dx) {
		result += 0.5*dx*(f(a) + f(a + dx)); //area of trapezoid = h/2 * (side one width + side two width)
	}
	return result;
}

//uncomment the following for testing
/*
#include <cmath>
#include <iostream>
//note that the integral function in an approximation, so assert(integral(...), actual_value) doesn't really make sense.
//in order to test the integral function, the test will see if the limit of integral(a, b, f, subdivisions) = actual_value as subdivisions aproach infinity

//returns how far off the approximation was from the actual value
template<typename R, typename I>
R testAgainst(I a, I b, R (*f)(I), unsigned subdivisions, R expected_value) {
	std::cout << "integral with " << subdivisions << " subdivisions was " << integral(a, b, f, subdivisions) << " | " << "actual was " << expected_value << '\n';
	return abs(expected_value - integral(a, b, f, subdivisions));
}

bool test(); //see integral.cpp
*/

//put the following in a .cpp file for testing purposes
/*
#include "integral.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define LOG(x) std::cout << #x << " = " << x << '\n'
//note that the integral function in an approximation, so assert(integral(...), actual_value) doesn't really make sense.
//in order to test the integral function, the test will see if the limit of integral(a, b, f, subdivisions) = actual_value as subdivisions aproach infinity
//However, since we can't technically do infinite calculation, we'll test it two times and see if it's closer to the actual value when we have more
//subdivisions (or if the difference is just really small)

static float power_of_x;
static float F(float x) { return pow(x, power_of_x); }
static float f(float x) { return pow(x, power_of_x - 1) * power_of_x; } //derivitave of F

static unsigned rand_seed;

//only does tests on random functions f(x) = kx^n where k and n are negative integers within a certain range
bool test() {
	std::cout << "-----------------------------------------" << '\n';
	srand(rand_seed);
	float a = rand() % 20; //cast to float because of integral function
	
	rand_seed += 200;
	srand(rand_seed);
	float b = rand() % 20;
	if(a > b) {
		float temp = b;
		b = a;
		a = temp;
	}
	LOG(a); LOG(b);
	rand_seed += 200;
	srand(rand_seed);
	unsigned subdivisions = (rand() % 30) + 1; //subdivisions cannot = 0
	LOG(subdivisions);
	rand_seed += 200; srand(rand_seed);
	power_of_x = -((rand() % 3) + 2);

	std::cout << "f(x) = " << power_of_x << " x^" << power_of_x - 1 << '\n';
	//the integral of f on [a, b] = F(b) - F(a) where f is the derivative of F
	LOG(f(a));
	LOG(f(b));
	float exact_integral_of_f = F(b) - F(a);
	//return if the estimation is closer to the actual value when the number of subdivisions is doubled or if the difference is very small
	float test1 = testAgainst(a, b, f, subdivisions, exact_integral_of_f);
	return (test1 > testAgainst(a, b, f, 2 * subdivisions, exact_integral_of_f))
		|| test1 < 1e-10;
}

int main() {
	//test it ten times
	rand_seed = time(NULL);
	for(unsigned i = 1; i < 11; ++i) {
		rand_seed += i * 200;
		float result = test();
		std::cout << "Test " << i << " returned " << result << '\n';
	}
	return 0;
}
*/
