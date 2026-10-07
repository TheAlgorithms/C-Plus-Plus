/**
 * @file
 * @brief Provides utilities to compute Catalan numbers using dynamic
 programming.
 * A Catalan numbers satisfy these recurrence relations:
 * C(0) = C(1) = 1; C(n) = sum(C(i).C(n-i-1)), for i = 0 to n-1
 * Read more about Catalan numbers here:
    https://en.wikipedia.org/wiki/Catalan_number
    https://oeis.org/A000108/
 */

#include <cassert>     /// for assert
#include <cstdint>     /// for std::uint64_t
#include <cstdlib>     /// for std::size_t
#include <functional>  /// for std::plus & std::multiplies
#include <numeric>     /// for std::transform_reduce
#include <vector>      /// for std::vector

/**
 * @brief computes and caches Catalan numbers
 */
class catalan_numbers {
    using value_type = std::uint64_t;
    std::vector<value_type> known{1, 1};

    value_type compute_next() {
        return std::transform_reduce(known.begin(), known.end(), known.rbegin(),
                                     static_cast<value_type>(0), std::plus<>(),
                                     std::multiplies<>());
    }

    void add() { known.push_back(this->compute_next()); }

 public:
    /**
     * @brief computes the n-th Catalan number and updates the cache.
     * @return the n-th Catalan number
     */
    value_type get(std::size_t n) {
        while (known.size() <= n) {
            this->add();
        }
        return known[n];
    }
};

void test_catalan_numbers_up_to_20() {
    // data verified with https://oeis.org/A000108/
    catalan_numbers cn;
    assert(cn.get(0) == 1ULL);
    assert(cn.get(1) == 1ULL);
    assert(cn.get(2) == 2ULL);
    assert(cn.get(3) == 5ULL);
    assert(cn.get(4) == 14ULL);
    assert(cn.get(5) == 42ULL);
    assert(cn.get(6) == 132ULL);
    assert(cn.get(7) == 429ULL);
    assert(cn.get(8) == 1430ULL);
    assert(cn.get(9) == 4862ULL);
    assert(cn.get(10) == 16796ULL);
    assert(cn.get(11) == 58786ULL);
    assert(cn.get(12) == 208012ULL);
    assert(cn.get(13) == 742900ULL);
    assert(cn.get(14) == 2674440ULL);
    assert(cn.get(15) == 9694845ULL);
    assert(cn.get(16) == 35357670ULL);
    assert(cn.get(17) == 129644790ULL);
    assert(cn.get(18) == 477638700ULL);
    assert(cn.get(19) == 1767263190ULL);
    assert(cn.get(20) == 6564120420ULL);
}

void test_catalan_numbers_25() {
    // data verified with https://oeis.org/A000108/
    catalan_numbers cn;
    assert(cn.get(25) == 4861946401452ULL);
}

int main() {
    test_catalan_numbers_up_to_20();
    test_catalan_numbers_25();
}
