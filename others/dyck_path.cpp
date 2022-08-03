#include<iostream> 
using namespace std;
 
// Function to count the result of Dyck Paths
int countDyckPaths(unsigned int num)
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
    num = 4;
    expected_result = 14;
    result = countDyckPaths(num);

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

