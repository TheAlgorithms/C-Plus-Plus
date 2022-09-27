/**************************************************************************************
    CollatzSequence(unsigned int64 N, vector<unsigned int64> ResultSequence)
Collatz conjecture: start with any positive integer N. The next term is
obtained as follows:
	If N term is even, the next term is: N / 2 .
	If N is odd, the next term is: 3 * N + 1.
The conjecture states the sequence will always reach 1 for any starting value N.
***************************************************************************************/
#include <vector>
#include <iostream>
#include <cassert>

bool CollatzSequence(uint64_t N, vector<uint64_t> &Result); // declare func for recursive using

bool CollatzSequence(uint64_t N, vector<uint64_t> &Result) {    // define func body
    std::cout << N << std::endl;                                //print N
    Result.push_back(N);                                        //Add N in vector
    while (Result.back() != 1) {                                // while 1 not reach
        Result.back()%2!=0 ? CollatzSequence(Result.back()*3+1, Result) : CollatzSequence(Result.back()/2, Result); // call recursivly with N/2 if even or N*3+1 if odd
    }
    return true; //return true
}


static void test(){                                                //test calculate Collatz Sequence
    vector<uint64_t> TestSequence;
    vector<uint64_t> TestResult = {5,16,8,4,2,1};                   // 5 *3+1=16/2=8/2=4/2=1*3+1=(4/2=2/2=1) 4, 2 and 1 in cicle end vi stopped when reach 1
    CollatzSequence(5, TestSequence);
    assert(TestSequence == TestResult);
    std::cout << "PASSED" << std::endl << std::endl;
}

int main()
{
    test();    
    return 0;
}
