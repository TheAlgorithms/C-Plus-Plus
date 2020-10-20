/**
 * @file
 * @brief An algorithm to calculate the sum of Fibonacci Sequence: \f$\mathrm{F}(n) + \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$
 * @details An algorithm to calculate the sum of Fibonacci Sequence: \f$\mathrm{F}(n) + \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$ where \f$\mathrm{F}(i)\f$
 * denotes the i-th Fibonacci Number . Note that F(0) = 0 and F(1) = 1. 
 * The value of the sum is calculated using matrix exponentiation.
 *
 * @author [Sarthak Sahu](https://github.com/SarthakSahu1009)
 */

#include <iostream> /// for std::cin and std::cout
#include <cassert>  /// for assert
#include <vector>   /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace fibonacci_sum
 * @brief Functions for the sum of the Fibonacci Sequence: \f$\mathrm{F}(n) + \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$
 */
namespace fibonacci_sum {
    
    /**
     * Function to multiply two matrices
     * @param T matrix 1
     * @param A martix 2
     * @returns resultant matrix
     */
    std::vector<std::vector<int> > multiply(std::vector<std::vector<int> > T, std::vector<std::vector<int> > A) {
    
        std::vector<std::vector<int> > result(2,std::vector<int>(2));
        
        // multiplying matrices
        for(int i=0;i<2;i++) {
            for(int j=0;j<2;j++) {
                result[i][j]=0;
                for(int k=0;k<2;k++) {
                    result[i][j]=(result[i][j]+(T[i][k]*A[k][j]));
                }
            }
        }
        
        return result;
    }
 
    /**
     * Function to compute A^n where A is a matrix.
     * @param T matrix
     * @param ex power
     * @returns resultant matrix
     */
    std::vector<std::vector<int> > power(std::vector<std::vector<int> > T, int ex) {
        
        std::vector<std::vector<int> > A{{1,1},{1,0}};
        if(ex == 0 || ex == 1) {
            return T;
        }
        
        T = power(T,ex/2);
        T = multiply(T,T);
        if(ex&1) {
            T = multiply(T,A);
        }
        return T;
    }
    
    /**
     * Function to compute sum of fibonacci sequence from 0 to n.
     * @param n number
     * @returns int ans, the sum of sequence
     */
    int result(int n) {
        std::vector<std::vector<int> > T{{1,1},{1,0}};
        T = power(T,n);
        int ans=T[0][1];
        ans = (ans - 1);
        return ans;
    }
    
    /**
     * Function to compute sum of fibonacci sequence from n to m.
     * @param n start of sequence
     * @param m end of sequence
     * @returns int the sum of sequence
     */
    int fiboSum(int n,int m){
        return (result(m+2) - result(n+1));
    }
}//namespace math
 
/**
 * Function for testing fiboSum function.
 * test cases and assert statement.
 * @returns `void`
*/
static void test() {
    int n = 0, m = 3;
    int test_1 = math::fiboSum(n,m);
    assert(test_1 == 4);
    std::cout << "Passed Test 1!" << std::endl;

    n = 3; m = 5;
    int test_2 = math::fiboSum(n,m);
    assert(test_2 == 10);
    std::cout << "Passed Test 2!" << std::endl;

    n = 5; m = 7;
    int test_3 = math::fiboSum(n,m);
    assert(test_3 == 26);
    std::cout << "Passed Test 3!" << std::endl;

    n = 7; m = 10;
    int test_4 = math::fiboSum(n,m);
    assert(test_4 == 123);
    std::cout << "Passed Test 4!" << std::endl;

    n = 9; m = 12;
    int test_5 = math::fiboSum(n,m);
    assert(test_5 == 322);
    std::cout << "Passed Test 5!" << std::endl;
} 

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test();
    return 0;
}
