#include <iostream>
#include <vector>
#include "algo.hpp"


int main(){
    std::vector<int> arr{1,5,6,2,8,10};
        auto itr = linearSearch(arr.begin(),arr.end(), 10);
        if(itr == arr.end())
                std::cout << "NOT Found" << std::endl;
        else
                std::cout << "Found" << std::endl;
}

/*Output
    g++ linearSearch_test.cpp
    ./a.out
    Found
 */