#include <iostream>

// bayes' theorem > https://en.wikipedia.org/wiki/Bayes%27_theorem

// bayes' theorem allows one to find P(A|B) given P(B|A)
// or P(B|A) given P(A|B) and P(A) and P(B)

// note P(A|B) is read 'The probability of A given that the event B has occured'

// returns P(A|B)

double bayes_AgivenB(double BgivenA, double A, double B) {
    return (BgivenA * A) / B;
}

// returns P(B|A)

double bayes_BgivenA(double AgivenB, double A, double B) {
    return (AgivenB * B) / A;
}

int main() {
    double A = 0.01;
    double B = 0.1;
    double BgivenA = 0.9;
    double AgivenB = bayes_AgivenB(BgivenA, A, B);
    std::cout << "A given B = " << AgivenB << std::endl;
    std::cout << "B given A = " << bayes_BgivenA(AgivenB, A, B) << std::endl;
    return 0;
}
