/**
 * @file
 * 
 * @brief Calculates the [Dot Product](https://en.wikipedia.org/wiki/Dot_product) of two 3D mathematical vectors.
 * 
 * 
 * @details The dot product (also known as the scalar product) takes two coordinate vectors 
 * and returns a single scalar value. It is calculated by multiplying matching components 
 * and taking the sum of those products.
 * * For two vectors $A = [a_1, a_2, a_3]$ and $B = [b_1, b_2, b_3]$, the calculation is:
 * $$A \cdot B = (a_1 \cdot b_1) + (a_2 \cdot b_2) + (a_3 \cdot b_3)$$
 * 
 * @author [Manraj Singh Sandhu](https://github.com/manraj-singh-sandhu)
 */

 #include<array>
 #include<cassert>

/**
 * @namespace math
 * @brief Math algorithms
 */

namespace math{
    /**
     * @namespace vector_dot
     * @brief Functions for Vector Dot Product algorithms
     */
namespace vector_dot{
    /**
     * @brief Computes the dot product of two 3D arrays containing component coordinates.
     * @param A contains the components of the first mathematical vector.
     * @param B contains the components of the second mathematical vector.
     * @returns The scalar dot product value as a double.
     */

    double dot(const std::array<double, 3> &A, const std::array<double, 3> &B){
        return (A[0] * B[0] ) + (A[1] * B[1]) + (A[2] * B[2]);
    }
} //namespace vector_dot
} //namespace math

/**
 * @brief Self-test function to validate calculations.
 */

 static void test(){
    //Test Case 1: Standard positive vectors
    //[1, 3, -5] . [4, -2, -1] -> (1*4) + (3*-2) + (-5*-1) = 4 - 6 + 5 = 3
    std::array<double, 3> v1 = {1,3,-5};
    std::array<double, 3> v2 = {4, -2, -1};
    assert(math::vector_dot::dot(v1, v2) == 3);

    // Test Case 2: Perpendicular vectors (Dot product must be 0)
    // [1, 0, 0] . [0, 1, 0] -> 0
    std::array<double, 3> v3 = {1, 0, 0};
    std::array<double, 3> v4 = {0, 1, 0};
    assert(math::vector_dot::dot(v3, v4) == 0);
 }
 
 /**
  * @brief Main funtion running verification tests.
  * @returns 0 on successful validation execution.
  */

  int main(){
    test(); // Executes assertions
    return 0;
  }
