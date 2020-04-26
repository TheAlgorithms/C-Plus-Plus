#include <iostream>

//calculates the probability of the events A or B for independent events
double addition_rule_independent(double A, double B)
{
	return (A + B) - (A * B);
}
//calculates the probability of the events A or B for dependent events
//note that if value of B_given_A is unknown, use chainrule to find it
double addition_rule_dependent(double A, double B, double B_given_A)
{
	return (A + B) - (A * B_given_A);
}

// A = 0.5 B = 0.25  A|B = 0.1 B|A = 0.05

int main() {
	double A = 0.5;
	double B = 0.25;
	double B_given_A = 0.05;

	std::cout << "if A and B are independent, P(A or B) = " << addition_rule_independent(A, B) << std::endl;
	std::cout << "if A and B are dependent, P(A or B) = " << addition_rule_dependent(A, B, B_given_A) << std::endl;

	return 0;
}