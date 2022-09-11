/**
 * @file
 * @brief [Bloom Filter](https://en.wikipedia.org/wiki/Bloom_filter)
 * generic implementation in C++
 * @details A Bloom filter is a space-efficient probabilistic data structure,
 * a query returns either "possibly in set" or "definitely not in set".
 *
 * More generally, fewer than 10 bits per element are required for a 1% false
 * positive probability, independent of the size or number of elements in the
 * set.
 *
 * It helps us to not make an "expensive operations", like disk IO - we can
 * use bloom filter to check incoming request, and with a good probability
 * get an answer of bloom filter, that we don't need to make our "expensive
 * operation"
 *
 *
 * [Very good use case example](https://stackoverflow.com/a/30247022)
 *
 * Basic bloom filter doesn't support deleting of elements, so
 * we don't need to implement deletion in bloom filter and bitset in our case.
 * @author [DanArmor](https://github.com/DanArmor)
 */

#include <cassert>           /// for assert
#include <functional>        /// for list of hash functions for bloom filter constructor
#include <initializer_list>  /// for initializer_list for bloom filter constructor
#include <string>            /// for testing on strings
#include <vector>            /// for std::vector
#include <iostream>          /// for IO operations

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {
/**
 * @brief Simple bitset implementation for bloom filter
 */
class Bitset {
 private:
    std::vector<std::size_t> data;  ///< short info of this variable
    static const std::size_t blockSize =
        sizeof(std::size_t);  ///< size of integer type, that we are using in
                              ///< our bitset
 public:
    explicit Bitset(std::size_t);
    std::size_t size();
    void add(std::size_t);
    bool contains(std::size_t);
};

/**
 * @brief Utility function to return the size of the inner array
 * @returns the size of inner array
 */
std::size_t Bitset::size() { return data.size(); }

/**
 * @brief BitSet class constructor
 * @param initSize amount of blocks, each contain sizeof(std::size_t) bits
 */
Bitset::Bitset(std::size_t initSize) : data(initSize) {}

/**
 * @brief Turn bit on position x to 1s
 *
 * @param x position to turn bit on
 * @returns void
 */
void Bitset::add(std::size_t x) {
    std::size_t blockIndex = x / blockSize;
    if (blockIndex >= data.size()) {
        data.resize(blockIndex + 1);
    }
    data[blockIndex] |= 1 << (x % blockSize);
}

/**
 * @brief Doest bitset contains element x
 *
 * @param x position in bitset to check
 * @returns true if bit position x is 1
 * @returns false if bit position x is 0
 */
bool Bitset::contains(std::size_t x) {
    std::size_t blockIndex = x / blockSize;
    if (blockIndex >= data.size()) {
        return false;
    }
    return data[blockIndex] & (1 << (x % blockSize));
}

/**
 * @brief Bloom filter template class
 * @tparam T type of elements that we need to filter
 */
template <typename T>
class BloomFilter {
 private:
    Bitset set;  ///< inner bitset for elements
    std::vector<std::function<std::size_t(T)>>
        hashFunks;  ///< hash functions for T type

 public:
    BloomFilter(std::size_t,
                std::initializer_list<std::function<std::size_t(T)>>);
    void add(T);
    bool contains(T);
};

/**
 * @brief Constructor for Bloom filter
 *
 * @tparam T type of elements that we need to filter
 * @param size initial size of Bloom filter
 * @param funks hash functions for T type
 * @returns none
 */
template <typename T>
BloomFilter<T>::BloomFilter(
    std::size_t size,
    std::initializer_list<std::function<std::size_t(T)>> funks)
    : set(size), hashFunks(funks) {}

/**
 * @brief Add function for Bloom filter
 *
 * @tparam T type of elements that we need to filter
 * @param x element to add to filter
 * @returns void
 */
template <typename T>
void BloomFilter<T>::add(T x) {
    for (std::size_t i = 0; i < hashFunks.size(); i++) {
        set.add(hashFunks[i](x) % (sizeof(std::size_t) * set.size()));
    }
}

/**
 * @brief Check element function for Bloom filter
 *
 * @tparam T type of elements that we need to filter
 * @param x element to check in filter
 * @return true if the element probably appears in the filter
 * @return false if the element certainly does not appear in the filter
 */
template <typename T>
bool BloomFilter<T>::contains(T x) {
    for (std::size_t i = 0; i < hashFunks.size(); i++) {
        if (set.contains(hashFunks[i](x) %
                         (sizeof(std::size_t) * set.size())) == false) {
            return false;
        }
    }
    return true;
}

/**
 * @brief [Function djb2](http://www.cse.yorku.ca/~oz/hash.html)
 * to get hash for the given string.
 *
 * @param s string to get hash from
 * @returns hash for a string
 */
static std::size_t hashDJB2(std::string const& s) {
    std::size_t hash = 5381;
    for (char c : s) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/**
 * @brief [Hash
 * function](https://stackoverflow.com/questions/8317508/hash-function-for-a-string),
 * to get hash for the given string.
 *
 * @param s string to get hash from
 * @returns hash for the given string
 */
static std::size_t hashStr(std::string const& s) {
    std::size_t hash = 37;
    std::size_t primeNum1 = 54059;
    std::size_t primeNum2 = 76963;
    for (char c : s) {
        hash = (hash * primeNum1) ^ (c * primeNum2);
    }
    return hash;
}

/**
 * @brief [Hash function for
 * test](https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key)
 *
 * @param x to get hash from
 * @returns hash for the `x` parameter
 */
std::size_t hashInt_1(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

/**
 * @brief [Hash function for
 * test](https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key)
 *
 * @param x to get hash from
 * @returns hash for the `x` parameter
 */
std::size_t hashInt_2(int x) {
    auto y = static_cast<std::size_t>(x);
    y = (y ^ (y >> 30)) * static_cast<std::size_t>(0xbf58476d1ce4e5b9);
    y = (y ^ (y >> 27)) * static_cast<std::size_t>(0x94d049bb133111eb);
    y = y ^ (y >> 31);
    return y;
}
}  // namespace data_structures

/**
 * @brief Test for bloom filter with string as generic type
 * @returns void
 */
static void test_bloom_filter_string() {
    data_structures::BloomFilter<std::string> filter(
        10, {data_structures::hashDJB2, data_structures::hashStr});
    std::vector<std::string> toCheck{"hello", "world", "!"};
    std::vector<std::string> toFalse{"false", "world2", "!!!"};
    for (auto& x : toCheck) {
        filter.add(x);
    }
    for (auto& x : toFalse) {
        assert(filter.contains(x) == false);
    }
    for (auto& x : toCheck) {
        assert(filter.contains(x));
    }
}

/**
 * @brief Test for bloom filter with int as generic type
 * @returns void
 */
static void test_bloom_filter_int() {
    data_structures::BloomFilter<int> filter(
        20, {data_structures::hashInt_1, data_structures::hashInt_2});
    std::vector<int> toCheck{100, 200, 300, 50};
    std::vector<int> toFalse{1, 2, 3, 4, 5, 6, 7, 8};
    for (int x : toCheck) {
        filter.add(x);
    }
    for (int x : toFalse) {
        assert(filter.contains(x) == false);
    }
    for (int x : toCheck) {
        assert(filter.contains(x));
    }
}

/**
 * @brief Test for bitset
 *
 * @returns void
 */
static void test_bitset() {
    data_structures::Bitset set(2);
    std::vector<std::size_t> toCheck{0, 1, 5, 8, 63, 64, 67, 127};
    for (auto x : toCheck) {
        set.add(x);
        assert(set.contains(x));
    }
    assert(set.contains(128) == false);
    assert(set.contains(256) == false);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // run self-test implementations

    test_bitset();  // run test for bitset, because bloom filter is depending on it
    test_bloom_filter_string();
    test_bloom_filter_int();
    
    std::cout << "All tests have successfully passed!\n";
    return 0;
}
