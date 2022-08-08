#include<iostream> 
using std::swap;
#include <cassert>  /// for assert
 
// Function to count the result of Dyck Paths
int countDyckPaths( int num)
{
    // Compute value of 2nCn
    int res = 1;
    for (int i = 0; i < num; ++i)
    {
        res *= (2 * num - i);
        res /= (i + 1);
    }
 
    // return 2nCn/(n+1)
    return res / (num+1);
}
 
//1st test
static void test(){
    //Assigned the number for Dyck path and the ecpected result
    int num = 4;
    int expected_result = 14;

    //get the actual result from the countDyckPaths function
    int result = countDyckPaths(num);

    // use assert function to return the test result of the function
    std::cout<<"Number for Diyck Path: " << num <<std::endl;
    std::cout<<"Expected Result of Dyck Path: " << expected_result <<std::endl;
    std::cout << "Result of Dyck Paths is " << result <<std:: endl;
    assert(result == expected_result);
    std::cout<< "Test Passed" << std::endl<<std::endl;

}

int main()
{
    test();
    return 0;
}

