#include <iostream>
#include <string>
#include <vector>

// Function to check if a number is a palindrome
bool is_palindrome_number(long long n) {
    if (n < 0)
        return false;  // Negative numbers are not palindromes
    std::string s = std::to_string(n);
    int i = 0, j = static_cast<int>(s.size()) - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        ++i;
        --j;
    }
    return true;
}

#ifdef RUN_LOCAL
int main() {
    std::vector<long long> tests = {121, -121, 10, 12321, 0};
    for (auto t : tests) {
        std::cout << t << " -> " << (is_palindrome_number(t) ? "True" : "False")
                  << "\n";
    }
    return 0;
}
#endif