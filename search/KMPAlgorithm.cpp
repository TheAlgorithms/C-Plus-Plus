#include <iostream>
#include <vector>
#include <string>

std::vector<int> computeLPSArray(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> lps(m);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMP(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> lps = computeLPSArray(pattern);
    int i = 0, j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            std::cout << "Pattern found at index " << i - j << std::endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::string text = "ababcabcabababd";
    std::string pattern = "ababd";
    KMP(text, pattern);
    return 0;
}
