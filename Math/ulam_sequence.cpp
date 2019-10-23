/*
 * Ulam Sequence generator Algorithm
 *
*/
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;

//generate the ulam numbers
vector<uint32_t> ulam_sequence(const uint64_t sequence_long) {
        vector<uint32_t> ulam_numbers = { 1,2 };
        vector<uint32_t> possible_next_ulam_numbers;
        uint64_t counter(0);
        while (++counter <= sequence_long)
        {
                for (signed index = ulam_numbers.size() - 1; index >= 0 && (ulam_numbers.at(index) > ((ulam_numbers.back() - ulam_numbers.at(index)) + 1)); index--) {
                        for (signed inside_index = (index - 1),min = (ulam_numbers.back() - ulam_numbers.at(index)) + 1; inside_index >= 0 && ulam_numbers.at(inside_index) >= min; inside_index--) {
                                possible_next_ulam_numbers.push_back(ulam_numbers.at(index) + ulam_numbers.at(inside_index));
                        }
                }
                qsort(&possible_next_ulam_numbers.front(), possible_next_ulam_numbers.size(),sizeof(unsigned),[](const void*a,const void*b) -> int {return (*(int*)a - *(int*)b);});
                vector<uint32_t>::iterator iter = possible_next_ulam_numbers.begin();
                while(true)
                {
                        if (iter == possible_next_ulam_numbers.end() - 1 || *iter != *(iter + 1)) {
                                ulam_numbers.push_back(*iter);
                                break;
                        }
                        unsigned nummber = *iter;
                        while (*(++iter) == nummber);
                }
                possible_next_ulam_numbers.clear();
        }
        return ulam_numbers;
}
int main()
{
        vector<uint32_t> ulam_numbers  = ulam_sequence(5); //first five ulam number test
        assert(ulam_numbers.at(0) == 1);
        assert(ulam_numbers.at(1) == 2);
        assert(ulam_numbers.at(2) == 3);
        assert(ulam_numbers.at(3) == 4);
        assert(ulam_numbers.at(4) == 6);
        system("pause");
        return 0;
}
