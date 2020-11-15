/**
 * @file
 * @brief Combinations n choose r function implementation
 * @details
 * A very basic and efficient method of calculating
 * choosing r from n different choices.
 * $ \binom{n}{r} = \frac{n!}{r! (n-r)!} $
 *
 * @author [Taj](https://github.com/tjgurwara99)
 */

#include <iostream>
#include <cassert>

/**
 * This is the function implementation of $\binom{n}{r}$
 * We are calculating the ans with iterations
 * instead of calculating three different factorials.
 * Also, we are using the fact that 
 * $ \frac{n!}{r! (n-r)!} = \frac{(n - r + 1) \cdot \cdots \cdot n}{1 \cdot \cdots \cdot r} $
 * @tparam T Only for integer types such as long, int_64 etc
 * @param n $n$ in $ \binom{n}{r} $
 * @param r $r$ in $ \binom{n}{r} $
 * @returns ans $\binom{n}{r} $
 */
template <class T>
T n_choose_r(T n, T r) {
    if(r > n / 2)
        r = n - r; // Because of the fact that  nCr(n, r) == nCr(n, n - r)
    T ans = 1;
    for(int i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}


/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // First test on 5 choose 2
     long t = (long) n_choose_r(5, 2);
     assert(((void)"10 is the answer but function says otherwise.\n",
             t == 10));
     std::cout << "First test passes." << std::endl;
     // Second test on 5 choose 3
     t = (long) n_choose_r(5, 3);
     assert(((void)"10 is the answer but the function says otherwise.\n",
             t == 10));
     std::cout << "Second test passes." << std::endl;
     // Third test on 3 choose 2
     t = (long)  n_choose_r(3, 2);
     assert(((void)"3 is the answer but the function says otherwise.\n",
             t == 3));
     std::cout << "Third test passes." << std::endl;
     // Fourth test on 10 choose 4
     t = (long) n_choose_r(10, 4);
     assert(((void)"210 is the answer but the function says otherwise.\n",
             t == 210));
     std::cout << "Fourth test passes." << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();
    return 0;
}

