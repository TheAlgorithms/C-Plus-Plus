#include <iostream>
#include <vector>
#include "single.hpp"
#include "algo.hpp"

int main(){

    std::vector<Single<int> > myInts;
    for(int i = 0; i < 6; i++){
        Single<int> pushVal(i);
        myInts.push_back(pushVal);
    }
    std::cout << "Values in my vector myInts" << std::endl;
    for(auto itr = myInts.begin(); itr != myInts.end(); itr++)
        print(*itr);
    
    Single<int> findVal(5);
    auto itr= linearSearch(myInts.begin(),myInts.end(), findVal);        
    if(itr == myInts.end())
        std::cout << "Not Found" << std::endl;
    else
        std::cout << "Found" << std::endl;

    return 0;

}

/*Output
    g++ linearSearchWithSingle_test.cpp
    ./a.out
    0
    1
    2
    3
    5
    6
    Found
 */