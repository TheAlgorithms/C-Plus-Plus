/**
 * @file
 * @brief Addition rule of probabilities
 */
#include <iostream>

/**
 * calculates the probability of the independent events A or B for independent
 * events
 * \parama [in] A probability of event A
 * \parama [in] B probability of event B
 * \returns probability of A and B
 */
double addition_rule_independent(double A, double B) {
    return (A + B) - (A * B);
}

/** Calculates the probability of the events A or B for dependent events
 * note that if value of B_given_A is unknown, use chainrule to find it
 * \parama [in] A probability of event A
 * \parama [in] B probability of event B
 * \parama [in] B_given_A probability of event B condition A
 * \returns probability of A and B
 */
double addition_rule_dependent(double A, double B, double B_given_A) {
    return (A + B) - (A * B_given_A);
}

/** Main function */
int main() {
    double A = 0.5;
    double B = 0.25;
    double B_given_A = 0.05;

    std::cout << "independent P(A or B) = " << addition_rule_independent(A, B)
              << std::endl;

    std::cout << "dependent P(A or B) = "
              << addition_rule_dependent(A, B, B_given_A) << std::endl;

    return 0;
}
