#include <vector>
#include <iostream>
#include <cassert>

bool CollatzSequence(uint64_t N, vector<uint64_t> &Result);

bool CollatzSequence(uint64_t N, vector<uint64_t> &Result) {
    std::cout << N << std::endl;
    Result.push_back(N);
    while (Result.back() != 1) {
        Result.back()%2!=0 ? CollatzSequence(Result.back()*3+1, Result) : CollatzSequence(Result.back()/2, Result);
    }
    return true;
}


static void test(){
    vector<uint64_t> TestSequence;
    vector<uint64_t> TestResult = {5,16,8,4,2,1};
    CollatzSequence(5, TestSequence);
    assert(TestSequence == TestResult);
    std::cout << "PASSED" << std::endl << std::endl;
}

int main()
{
    test();    
    return 0;
}
