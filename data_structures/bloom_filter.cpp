/**
 * @file bloom_filter.cpp
 * @brief [Bloom Filter](https://en.wikipedia.org/wiki/Bloom_filter)
 * generic implementation in C++
 * @details Basic bloom filter doesn't support deleting of elements, so
 * we don't need to implement deletion in bloom filter and bitset.
 *
 * [Very good use case example](https://stackoverflow.com/a/30247022)
 * @author [DanArmor](https://github.com/DanArmor)
 */

#include <cassert>     ///< for assert
#include <functional>  ///< for list of hash functions for bloom filter constructor
#include <initializer_list>  ///< for initializer_list for bloom filter constructor
#include <string>            ///< for testing on strings
#include <vector>            ///< for vector

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
    Bitset(std::size_t initSize);
    void add(std::size_t x);
    bool contains(std::size_t x);
};

/**
 * @brief Constructor for Bitset
 *
 * @param initSize amount of blocks, each contain sizeof(std::size_t) bits
 */
Bitset::Bitset(std::size_t initSize) : data(initSize) {}

/**
 * @brief Turn bit on position x to 1s
 *
 * @param x position to turn bit on
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
 * @return true if: bit on position x is 1
 * @return false if: bit on position x is 0
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
 *
 * @tparam T type, that we need to hash
 */
template <typename T>
class BloomFilter {
 private:
    Bitset set;  ///< inner bitset for elements
    std::vector<std::function<std::size_t(T)>>
        hashFunks;  ///< hash functions for T type

 public:
    BloomFilter(std::size_t size,
                std::initializer_list<std::function<std::size_t(T)>> funks);
    void add(T x);
    bool contains(T x);
};

/**
 * @brief Constructor for Bloom filter
 *
 * @tparam T type, that we need to hash
 * @param size initial size of Bloom filter
 * @param funks hash functions for T type
 */
template <typename T>
BloomFilter<T>::BloomFilter(
    std::size_t size,
    std::initializer_list<std::function<std::size_t(T)>> funks)
    : set(size), hashFunks(funks) {}

/**
 * @brief Add function for Bloom filter
 *
 * @tparam T type, that we need to hash
 * @param x element to add to filter
 */
template <typename T>
void BloomFilter<T>::add(T x) {
    for (std::size_t i = 0; i < hashFunks.size(); i++) {
        set.add(hashFunks[i](x));
    }
}

/**
 * @brief Check element function for Bloom filter
 *
 * @tparam T type, that we need to hash
 * @param x element to check in filter
 * @return true if: element probably appears in filter
 * @return false if: element certainly does not appear in filter
 */
template <typename T>
bool BloomFilter<T>::contains(T x) {
    for (std::size_t i = 0; i < hashFunks.size(); i++) {
        if (set.contains(hashFunks[i](x)) == false) {
            return false;
        }
    }
    return true;
}

// [Function djb2](http://www.cse.yorku.ca/~oz/hash.html), to get hash for
// string
std::size_t hashDJB2(std::string s) {
    std::size_t hash = 5381;
    for (std::size_t i = 0; i < s.size(); i++) {
        hash = ((hash << 5) + hash) + s[i];
    }
    return hash;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(void) {
    // test();  // run self-test implementations
    //  code here
    return 0;
}