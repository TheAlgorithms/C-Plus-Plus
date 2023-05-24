/**
 * @file
 * @brief contains the definition of the function longest_common_string_length
 * @details
 * the function longest_common_string_length computes the length
 * of the longest common string which can be created of two input strings
 * by removing characters from them
 */

#include <cassert>  /// for assert
#include <string>   /// for std::string
#include <utility>  /// for std::move
#include <vector>   /// for std::vector

/**
 * @brief computes the length of the longest common string created from input
 * strings
 * @details has O(str_a.size()*str_b.size()) time and memory complexity
 * @param str_a first input string
 * @param str_b second input string
 * @returns the length of the longest common string which can be strated from
 * str_a and str_b
 */
std::size_t longest_common_string_length(const std::string& str_a,
                                         const std::string& str_b) {
    const auto size_a = str_a.size();
    const auto size_b = str_b.size();
    std::vector<std::vector<std::size_t>> sub_sols(
        size_a + 1, std::vector<std::size_t>(size_b + 1, 0));

    const auto limit = static_cast<std::size_t>(-1);
    for (std::size_t pos_a = size_a - 1; pos_a != limit; --pos_a) {
        for (std::size_t pos_b = size_b - 1; pos_b != limit; --pos_b) {
            if (str_a[pos_a] == str_b[pos_b]) {
                sub_sols[pos_a][pos_b] = 1 + sub_sols[pos_a + 1][pos_b + 1];
            } else {
                sub_sols[pos_a][pos_b] = std::max(sub_sols[pos_a + 1][pos_b],
                                                  sub_sols[pos_a][pos_b + 1]);
            }
        }
    }

    return sub_sols[0][0];
}

struct TestCase {
    const std::string str_a;
    const std::string str_b;
    const std::size_t common_string_len;

    TestCase(std::string in_str_a, std::string in_str_b,
             const std::size_t in_common_string_len)
        : str_a(std::move(in_str_a)),
          str_b(std::move(in_str_b)),
          common_string_len(in_common_string_len) {}
};

std::vector<TestCase> get_test_cases() {
    return {TestCase("", "", 0),
            TestCase("ab", "ab", 2),
            TestCase("ab", "ba", 1),
            TestCase("", "xyz", 0),
            TestCase("abcde", "ace", 3),
            TestCase("BADANA", "ANADA", 3),
            TestCase("BADANA", "CANADAS", 3),
            TestCase("a1a234a5aaaa6", "A1AAAA234AAA56AAAAA", 6),
            TestCase("123x", "123", 3),
            TestCase("12x3x", "123", 3),
            TestCase("1x2x3x", "123", 3),
            TestCase("x1x2x3x", "123", 3),
            TestCase("x12x3x", "123", 3)};
}

/**
 * @brief checks the function longest_common_string_length agains example data
 * @param test_cases list of test cases
 * @tparam type representing a list of test cases
 */
template <typename TestCases>
void test_longest_common_string_length(const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        assert(longest_common_string_length(cur_tc.str_a, cur_tc.str_b) ==
               cur_tc.common_string_len);
    }
}

/**
 * @brief checks the function longest_common_string_length returns the same
 * result when its argument are flipped
 * @param test_cases list of test cases
 * @tparam type representing a list of test cases
 */
template <typename TestCases>
void test_longest_common_string_length_is_symmetric(
    const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        assert(longest_common_string_length(cur_tc.str_b, cur_tc.str_a) ==
               cur_tc.common_string_len);
    }
}

/**
 * @brief reverses a given string
 * @param in_str input string
 * @return the string in which the characters appear in the reversed order as in
 * in_str
 */
std::string reverse_str(const std::string& in_str) {
    return {in_str.rbegin(), in_str.rend()};
}

/**
 * @brief checks the function longest_common_string_length returns the same
 * result when its inputs are reversed
 * @param test_cases list of test cases
 * @tparam type representing a list of test cases
 */
template <typename TestCases>
void test_longest_common_string_length_for_reversed_inputs(
    const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        assert(longest_common_string_length(reverse_str(cur_tc.str_a),
                                            reverse_str(cur_tc.str_b)) ==
               cur_tc.common_string_len);
    }
}

/**
 * @brief runs all tests for longest_common_string_length funcion
 */
void tests() {
    const auto test_cases = get_test_cases();
    assert(test_cases.size() > 0);
    test_longest_common_string_length(test_cases);
    test_longest_common_string_length_is_symmetric(test_cases);
    test_longest_common_string_length_for_reversed_inputs(test_cases);
}

int main() {
    tests();
    return 0;
}
