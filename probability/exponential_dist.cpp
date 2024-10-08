/**
 * @file
 * @brief [Exponential Distribution](https://en.wikipedia.org/wiki/Exponential_distribution)
 * 
 * The exponential distribution is used to model
 * events occuring between a Poisson process like radioactive decay.
 * 
 * P(x,⋋) = ⋋e^(-⋋x)
 * 
 * Summary of variables used:
 * ⋋: rate parameter
 */
#include<cmath>
#include<cassert>
#include<iostream>

/** Find the expected value of the exponential distribution
 * \param [in] lambda
 * \returns \f$\mu=1/lambda\f$
 */
double exponential_expected(double lambda){
    if (lambda<=0){
        std::cout << "Error: Lambda must be greater than 0." << std::endl;
        assert(lambda>0);
    }
    return 1/lambda;
}

/** Find the variance of the exponential distribution
 * \param [in] lambda
 * \returns \f$\sigma^2=1/(lambda^2)\f$
 */
double exponential_var(double lambda){
    if (lambda<=0){
        std::cout << "Error: Lambda must be greater than 0." << std::endl;
        assert(lambda>0);
    }
    return 1/pow(lambda,2);
}

/** Find the standard deviation of the exponential distribution
 * \param [in] lambda
 * \returns \f$\sigma=1/lambda\f$
 */
double exponential_std(double lambda){
    if (lambda<=0){
        std::cout << "Error: Lambda must be greater than 0." << std::endl;
        assert(lambda>0);
    }
    return 1/lambda;
}

static void test(){
    double lambda = 2;
    double expected = 0.5;
    double var = 0.25;
    double std = 0.5;

    //Test 1
    std::cout << "Expected Value" << std::endl;
    std::cout << "Lambda : " << lambda << std::endl;
    std::cout << "Expected Output : " << expected <<std::endl;
    std::cout << "Output : " << exponential_expected(lambda) << std::endl;
    assert(exponential_expected(lambda)==expected);
    std::cout << "TEST PASSED" << std::endl;
    std::cout<<std::endl;

    //Test 2
    std::cout << "Variance" << std::endl;
    std::cout << "Lambda : " << lambda << std::endl;
    std::cout << "Expected Output : " << var <<std::endl;
    std::cout << "Output : " << exponential_var(lambda) << std::endl;
    assert(exponential_var(lambda)==var);
    std::cout << "TEST PASSED" << std::endl;
    std::cout<<std::endl;

    //Test 3
    std::cout << "Standard Deviation" << std::endl;
    std::cout << "Lambda : " << lambda << std::endl;
    std::cout << "Expected Output : " << std <<std::endl;
    std::cout << "Output : " << exponential_std(lambda) << std::endl;
    assert(exponential_std(lambda)==std);
    std::cout << "TEST PASSED" << std::endl;
    std::cout<<std::endl;
}

int main(){
    test(); //Self-implemented test
    return 0;
}
