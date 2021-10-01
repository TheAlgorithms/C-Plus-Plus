/**
 * @author [Satyam Koshta](https://github.com/satyamkoshta340)
 * @file 
 * @brief calculate set bits in a number
 * @details this algorithm calculates the number of set bits in the binary
 * form of a number, It implemented by using the method of  bitwise AND(&) 
 * operator to check the bits
 * @see get_set_bits.cpp.
 */

#include<iostream> // for IO operation
#include<cassert> // for assert


// function to count set bits in a number
uint64_t count_set_bits(uint64_t num){
    // initializing count to 0    
    uint64_t count =0;

    //iterate over the number
    while(num){
        if((num&1)){
            count++;
        }
        num >>= 1;
    }
    // return the count of set bits in number
    return count;
}


static void test() {
    assert(count_set_bits(10)==2);
    assert(count_set_bits(150)==4);
    assert(count_set_bits(10080)==6);
    assert(count_set_bits(1099)==5);
    assert(count_set_bits(20000)==5);
    assert(count_set_bits(64)==1);
    assert(count_set_bits(12453652)==11);
    assert(count_set_bits(254156255)==18);

    std::cout<< "All tests have passed successfully!\n";
}
/*
@brief Main function
@returns 0 on exit
*/

int main(){
    test(); // running self-test implementations
    return 0;
}
