#include <iostream>

/* Calculate the the Value on
Fibonnaci's sequence given an
integer as input
Fibonacci =  0, 1, 1, 2, 3, 5,
             8, 13, 21, 34, 55,
             89, 144, ...       */

int fibonacci(uint n){
    int retval =0;
    /*If the input is 0 or 1 just return the same
     This will set the first 2 values of the sequence*/
    if(n <= 1){
        return n;
    }
    else{
        /*Add the last 2 values of the sequence to get next*/
        retval = fibonacci(n-1) + fibonacci(n-2);
    }
    return retval;
}

int main() {
    int n;
    std::cin >> n;
    assert(n >= 0);
    std::cout <<"F("<<n<<")= " << fibonacci(n) << std::endl;
}
