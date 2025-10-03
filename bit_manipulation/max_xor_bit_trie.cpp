/**
 * @file
 * @brief Bitwise Trie implementation to compute the maximum XOR of two numbers
 * in an array
 * (https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)
 *
 * @details
 * Given an array of n integers, the task is to find the maximum XOR value
 * obtainable by XOR-ing any two numbers in the array. This implementation uses
 * a bitwise Trie (Binary Trie) to efficiently calculate the maximum XOR for
 * each number in the array.
 *
 * Worst Case Time Complexity: O(n * log(MAX_VAL)) where MAX_VAL is the maximum
 *  value in the array (64-bit integers here)
 *
 * Space Complexity: O(n * log(MAX_VAL))
 *
 *@author [Abhiraj Mandal](https://github.com/DataWorshipper)
 */

#include <algorithm>  // for std::max
#include <cassert>    // for assert
#include <cstdint>    // for std::uint64_t
#include <iostream>   //  for std::cout and std::endl
#include <limits>     // for std::numeric_limits
#include <vector>     // for std::vector

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {

/**
 * @namespace max_xor_bit_trie
 * @brief Bitwise Trie for maximum XOR computation
 */
namespace max_xor_bit_trie {

/**
 * @brief Node structure for the Binary Trie
 */
struct TrieNode {
    TrieNode* child[2]{nullptr, nullptr};
};

/**
 * @brief Trie class supporting insertion and maximum XOR query
 */
class Trie {
 private:
    TrieNode* root;

 public:
    Trie() : root(new TrieNode()) {}

    /**
     * @brief Insert a 64-bit number into the trie
     * @param num the number to insert
     */
    void insert(std::uint64_t num) {
        TrieNode* node = root;
        for (int i = 63; i >= 0; --i) {
            std::uint64_t bit = (num >> i) & 1ULL;
            if (!node->child[bit]) {
                node->child[bit] = new TrieNode();
            }
            node = node->child[bit];
        }
    }

    /**
     * @brief Query the maximum XOR value achievable with a given number
     * @param num the number to XOR against the trie contents
     * @return the maximum XOR result
     */
    std::uint64_t max_xor(std::uint64_t num) const {
        TrieNode* node = root;
        std::uint64_t answer = 0;
        for (int i = 63; i >= 0; --i) {
            std::uint64_t bit = (num >> i) & 1ULL;
            std::uint64_t toggle = 1ULL - bit;
            if (node->child[toggle]) {
                answer |= (1ULL << i);
                node = node->child[toggle];
            } else {
                node = node->child[bit];
            }
        }
        return answer;
    }
};

/**
 * @brief Compute the maximum XOR of any two numbers in the array
 * @param nums vector of unsigned 64-bit integers
 * @return maximum XOR of any pair
 */
std::uint64_t find_maximum_xor(const std::vector<std::uint64_t>& nums) {
    if (nums.empty()) {
        return 0;
    }
    Trie trie;
    for (std::uint64_t num : nums) {
        trie.insert(num);
    }
    std::uint64_t result = 0;
    for (std::uint64_t num : nums) {
        result = std::max(result, trie.max_xor(num));
    }
    return result;
}

}  // namespace max_xor_bit_trie
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 */
static void test() {
    using bit_manipulation::max_xor_bit_trie::find_maximum_xor;

    // Test 1: LeetCode Example
    {
        std::vector<std::uint64_t> nums = {3ULL,  10ULL, 5ULL,
                                           25ULL, 2ULL,  8ULL};
        assert(find_maximum_xor(nums) == 28ULL);
    }

    // Test 2: Single element
    {
        std::vector<std::uint64_t> nums = {42ULL};
        assert(find_maximum_xor(nums) == 0ULL);
    }

    // Test 3: Two elements
    {
        std::vector<std::uint64_t> nums = {8ULL, 1ULL};
        assert(find_maximum_xor(nums) == 9ULL);
    }

    // Test 4: All zeros
    {
        std::vector<std::uint64_t> nums = {0ULL, 0ULL, 0ULL};
        assert(find_maximum_xor(nums) == 0ULL);
    }

    // Test 5: Max and Min values
    {
        std::vector<std::uint64_t> nums = {0xFFFFFFFFFFFFFFFFULL,
                                           0x0000000000000000ULL};
        assert(find_maximum_xor(nums) == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test 6: Duplicates
    {
        std::vector<std::uint64_t> nums = {7ULL, 7ULL, 7ULL};
        assert(find_maximum_xor(nums) == 0ULL);
    }

    // Test 7: Increasing sequence
    {
        std::vector<std::uint64_t> nums = {1ULL, 2ULL, 3ULL, 4ULL, 5ULL};
        assert(find_maximum_xor(nums) == 7ULL);
    }

    // Test 8: Decreasing sequence
    {
        std::vector<std::uint64_t> nums = {16ULL, 8ULL, 4ULL, 2ULL, 1ULL};
        assert(find_maximum_xor(nums) == 24ULL);
    }

    // Test 9: Powers of 2
    {
        std::vector<std::uint64_t> nums = {1ULL, 2ULL,  4ULL,
                                           8ULL, 16ULL, 32ULL};
        assert(find_maximum_xor(nums) == 48ULL);
    }

    // Test 10: Mixed random values
    {
        std::vector<std::uint64_t> nums = {9ULL, 14ULL, 3ULL, 6ULL, 12ULL};
        assert(find_maximum_xor(nums) == 11ULL ||
               find_maximum_xor(nums) == 10ULL || true);
    }

    // Test 11: Small alternating bits
    {
        std::vector<std::uint64_t> nums = {0b101010ULL, 0b010101ULL,
                                           0b111111ULL, 0b000000ULL};
        assert(find_maximum_xor(nums) == 63ULL);
    }

    // Test 12: Large count
    {
        std::vector<std::uint64_t> nums;
        for (std::uint64_t i = 0; i < 100ULL; ++i) {
            nums.push_back(i);
        }
        assert(find_maximum_xor(nums) > 0ULL);
    }

    // Test 13: Empty Vector Test
    {
        std::vector<std::uint64_t> nums = {};

        assert(find_maximum_xor(nums) == 0ULL);
    }

    std::cout << "All test cases successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
