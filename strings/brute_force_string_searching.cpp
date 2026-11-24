/**
 * @file
 * @brief          String pattern search - brute force
 * @details
 * Finds the first matching substring in the text, otherwise returns -1.
 * Time complexity: O(n * m), Space complexity: O(m), where n is the length of the text and m is the length of the pattern.
 */

#include <cassert> /// For assert
#include <iostream> /// For IO operations
#include <string> /// For std::string

/**
 * @namespace string_search
 * @brief String search algorithms
 */

namespace string_search {
	/**
	 * @brief Find a pattern in a string by comparing the pattern to every substring.
	 * @param text     Any string that might contain the pattern.
	 * @param pattern  String that we are searching for.
	 * @returns        Index where the pattern starts in the text
	 * @returns        -1 if the pattern was not found.
	 */
	int brute_force(const std::string& text, const std::string& pattern) {
		size_t pattern_length = pattern.length();
		size_t text_length = text.length();
		int index = -1;
		if (pattern_length <= text_length) {
			for (size_t i = 0; i < text_length - pattern_length + 1; i++) {
				std::string current_substring = text.substr(i, pattern_length);
				if (current_substring == pattern) {
					index = i;
					break;
				}
			}
		}
		return index;
	}
}  // namespace string_search

/**
 * @brief Self-test implementations
 * @returns void
 */

static void test() {
	assert(string_search::brute_force("a", "aa") == -1);
	assert(string_search::brute_force("aa", "a") == 0);
	assert(string_search::brute_force("bbb", "a") == -1);
	assert(string_search::brute_force("bbbbab", "ab") == 4);

	std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
	test();
	return 0;
}
