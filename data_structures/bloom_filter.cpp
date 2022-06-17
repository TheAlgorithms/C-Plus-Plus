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
    std::size_t size(void);
    void add(std::size_t x);
    bool contains(std::size_t x);
};

/**
 * @brief Returns size of inner array
 *
 * @return size of inner array
 */
std::size_t Bitset::size(void) { return data.size(); }
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
 * @return void
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
 * @return void
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
 * @tparam T type, that we need to hash
 * @param x element to check in filter
 * @return true if: element probably appears in filter
 * @return false if: element certainly does not appear in filter
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
 * @brief Test for bitset
 *
 * @return void
 */
static void test_bitset(void) {
    Bitset set(2);
    std::vector<std::size_t> toCheck{0, 1, 5, 8, 63, 64, 67, 127};
    for (std::size_t i = 0; i < toCheck.size(); i++) {
        set.add(toCheck[i]);
        assert(set.contains(toCheck[i]));
    }
    assert(set.contains(128) == false);
    assert(set.contains(256) == false);
}

/**
 * @brief [Function djb2](http://www.cse.yorku.ca/~oz/hash.html), to get hash
 * for string
 *
 * @param s string to get hash from
 * @return hash for a string
 */
static std::size_t hashDJB2(std::string s) {
    std::size_t hash = 5381;
    for (std::size_t i = 0; i < s.size(); i++) {
        hash = ((hash << 5) + hash) + s[i];
    }
    return hash;
}

/**
 * @brief [Hash
 * function](https://stackoverflow.com/questions/8317508/hash-function-for-a-string),
 * to get hash for string
 *
 * @param s string to get hash from
 * @return hash for a string
 */
static std::size_t hashStr(std::string s) {
    std::size_t h = 37;
    std::size_t A = 54059;
    std::size_t B = 76963;
    for (std::size_t i = 0; i < s.size(); i++) {
        h = (h * A) ^ (s[i] * B);
    }
    return h;
}

/**
 * @brief Test for bloom filter with string as generic type
 * @return void
 */
static void test_bloom_filter_string(void) {
    BloomFilter<std::string> filter(10, {hashDJB2, hashStr});
    std::vector<std::string> toCheck{"hello", "world", "!"};
    std::vector<std::string> toFalse{"false", "world2", "!!!"};
    for (std::size_t i = 0; i < toCheck.size(); i++) {
        filter.add(toCheck[i]);
    }
    for (std::size_t i = 0; i < toFalse.size(); i++) {
        assert(filter.contains(toFalse[i]) == false);
    }
    for (std::size_t i = 0; i < toCheck.size(); i++) {
        assert(filter.contains(toCheck[i]));
    }
}

/**
 * @brief [Hash function for
 * test](https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key)
 *
 * @param x int to get hash from
 * @return hash for x
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
 * @param x int to get hash from
 * @return hash for x
 */
std::size_t hashInt_2(int x) {
    x = (x ^ (x >> 30)) * std::size_t(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * std::size_t(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

/**
 * @brief Test for bloom filter with int as generic type
 * @return void
 */
static void test_bloom_filter_int(void) {
    BloomFilter<int> filter(20, {hashInt_1, hashInt_2});
    std::vector<int> toCheck{100, 200, 300, 50};
    std::vector<int> toFalse{1, 2, 3, 4, 5, 6, 7, 8};
    for (std::size_t i = 0; i < toCheck.size(); i++) {
        filter.add(toCheck[i]);
    }
    for (std::size_t i = 0; i < toFalse.size(); i++) {
        assert(filter.contains(toFalse[i]) == false);
    }
    for (std::size_t i = 0; i < toCheck.size(); i++) {
        assert(filter.contains(toCheck[i]));
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(void) {
    test_bitset();  // run test for bitset, because bloom filter is depend on it
    test_bloom_filter_string();
    test_bloom_filter_int();
    return 0;
}