/**
 * @file
 * 
 * @brief a program to check if the given number satisfies the pythagoras theorem(h^2 = p^2 + b^2)
 * 
 * @details
 * more info on: https://en.wikipedia.org/wiki/Pythagorean_theorem
 * 
 * the pythagoras theorem states that the area of the square whose side is the hypotenuse 
 * is equal to the sum of the areas of the squares on the other two sides.
 * 
 * the pythagoras_calculation() function takes 3 inputs, h, p and b.
 * with h being hypotenuse, p being the perpendicular and b being the base of a right angle triangle
 * 
 * if the square of h is equal to the square of p and b combined the function returns true
 * else the function returns false
 *
 * @author [bubbl337](https://github.com/bubbl337)
 */

#include<cassert>   //for assert
#include<cmath>     //for mathematical operations
#include<iostream>  //for IO operations


/**
 * function to check the pythogaras theorem
 * @param h double
 * @param p double
 * @param b double
 * @returns bool whether the numbers are in accordance to the Pythagorean theorem
 */
bool pythagoras_calculation(double h,double p,double b){
    if (pow(h,2) == pow(p,2)+pow(b,2)){
        return true;
    }
    else{return false;}
}

/**
 * @brief Self-test implementations
 * @returns void
 */
/**
 * @brief Self-test implementations
 * @returns void
 */
static void test(){
    /*tests with a variety of numbers if the number given satisfies the pythagoras theorem  */
    assert(pythagoras_calculation(5,4,3) == true);
    assert(pythagoras_calculation(12,5,6) == false);
    assert(pythagoras_calculation(13,12,5) == true);
    assert(pythagoras_calculation(25,20,15) == true);
    
    std::cout << "All tests have successfully passed!\n";

}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit   
 */
int main(int argc, char *argv[]){
    test();  // run self-test implementations
    return 0;    
}
