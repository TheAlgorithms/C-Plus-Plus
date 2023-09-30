// Problem Link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// This C++ program generates letter combinations for a given set of digits
// using the mapping of digits to letters on a phone keypad.
// It employs a recursive approach with backtracking to explore and construct the combinations.
// Example input: "23" produces combinations like "ad," "ae," "af," "bd," "be," "bf," "cd," "ce," "cf."


#include <iostream>
#include <vector>
#include <string>

class PhoneNumber {
public:
    // Helper function to generate letter combinations
    static void solve(std::vector<std::string>& ans, const std::string& digits, const std::vector<std::string>& mapping, int index, std::string& output) {
        // Base case: If we have processed all digits, add the current output to the result list
        if (index == digits.length()) {
            ans.push_back(output);
            return;
        }

        // Get the current digit and its corresponding letters
        int digit = digits[index] - '0';
        const std::string& value = mapping[digit];

        // Iterate through the letters for the current digit
        for (char ch : value) {
            // Append the current letter to the output
            output.push_back(ch);

            // Recursively move to the next digit
            solve(ans, digits, mapping, index + 1, output);

            // Backtrack by removing the last character to explore other combinations
            output.pop_back();
        }
    }

    // Main function to generate letter combinations for a given set of digits
    std::vector<std::string> letterCombinations(const std::string& digits) {
        std::vector<std::string> ans;

        // Check if the input digits are empty
        if (digits.empty()) {
            return ans;
        }

        // Mapping of digits to letters on a phone keypad
        const std::vector<std::string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        int index = 0; // Start with the first digit
        std::string output;
        solve(ans, digits, mapping, index, output); // Call the recursive solver
        return ans; // Return the list of letter combinations
    }
};

int main() {
    // Example input: "23"
    std::string digits = "23";
    PhoneNumber phoneNumber;
    std::vector<std::string> combinations = phoneNumber.letterCombinations(digits);

    // Display the generated letter combinations
    std::cout << "Letter combinations for digits " << digits << ":\n";
    for (const std::string& combination : combinations) {
        std::cout << combination << "\n";
    }

    return 0;
}
