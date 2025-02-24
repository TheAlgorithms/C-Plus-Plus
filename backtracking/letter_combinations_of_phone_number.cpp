/**
 * @file
 * @brief [Letter-Combinations](https://en.wikipedia.org/wiki/Phoneword) problem
 * @details Implements a function that returns all possible letter combinations
 * for a given string of digits (2-9) based on the classic mobile keypad mapping.
 *
 * @author [Saurabh Damle](https://github.com/saurabhdamle11)
 */

 #include <cassert>        /// for assert
 #include <iostream>       /// for IO operations
 #include <string>         /// for std::string
 #include <vector>         /// for std::vector
 
 /**
  * @namespace backtracking
  * @brief Backtracking algorithms
  */
 namespace backtracking {
 /**
  * @namespace letter_combinations_of_phone_number
  * @brief Functions for generating letter combinations for a given phone number string
  */
 namespace letter_combinations_of_phone_number {
 
 /**
  * @brief Helper function to generate all possible letter combinations
  * @param current_index Current position in the input digits string
  * @param digit_length Length of the input digits string
  * @param combinations Vector to store generated letter combinations
  * @param digits Input string of digits (2-9)
  * @param buffer Temporary string buffer for backtracking
  * @param char_number_map Mapping of digits to corresponding letter groups
  * 
  * This function recursively generates all possible letter combinations by iterating over
  * the possible characters corresponding to the current digit and appending them to the buffer.
  * It uses backtracking by removing the last appended character before returning to the previous state.
  */
 void generate_combinations(int32_t current_index, int32_t digit_length, std::vector<std::string>& combinations,
                            const std::string& digits, std::string buffer, const std::vector<std::string>& char_number_map) {
     if (current_index == digit_length) {
         if (!buffer.empty()) {
             combinations.push_back(buffer);
         }
         return;
     }
     std::string all_chars = char_number_map[digits[current_index] - '0'];
     for (char c : all_chars) {
         generate_combinations(current_index + 1, digit_length, combinations, digits, buffer + c, char_number_map);
     }
 }
 
 /**
  * @brief Generates all possible letter combinations for a given digit string
  * @param digits Input string of digits (2-9)
  * @returns Vector of strings containing all possible letter combinations
  * 
  * This function initializes the character mapping and calls the recursive helper function
  * `generate_combinations` to compute all possible letter combinations. If the input string
  * is empty, it returns an empty vector.
  */
 std::vector<std::string> letterCombinations(const std::string& digits) {
     if (digits.empty()) {
         return {};
     }
     std::vector<std::string> char_number_map = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
     std::vector<std::string> combinations;
     generate_combinations(0, digits.size(), combinations, digits, "", char_number_map);
     return combinations;
 }
 
 }  
 }  
 
 /**
  * @brief Test function to validate the implementation
  */
 static void test() {
     using namespace backtracking::letter_combinations_of_phone_number;
 
     std::cout << "1st test ";
     std::vector<std::string> expected1 = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
     assert(letterCombinations("23") == expected1);
     std::cout << "passed" << std::endl;
 
     std::cout << "2nd test ";
     std::vector<std::string> result = letterCombinations("7");
     std::vector<std::string> expected_result = {"p", "q", "r", "s"};
     assert(result == expected_result);
     std::cout << "passed" << std::endl;
 
     std::cout << "3rd test ";
     assert(letterCombinations("") == std::vector<std::string>{});
     std::cout << "passed" << std::endl;
 
     std::cout << "4th test ";
     std::vector<std::string> expected = {"w", "x", "y", "z"};
     assert(letterCombinations("9") == expected);
     std::cout << "passed" << std::endl;
 }
 
 /**
  * @brief Main function
  * @returns 0 on exit
  */
 int main() {
     test();  // Run test cases
     return 0;
 }
 