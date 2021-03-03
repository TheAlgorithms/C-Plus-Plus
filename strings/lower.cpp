#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif
#include <assert.h>

namespace strings {
/**
 * Will convert the entire string to lowercase letters
 * @param word is the text you want to lowercase
 * @return An lowercase copy of the string.
 */
std::string lower(std::string word) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] + 32;
        }
    }
    return word;
}
}  // namespace strings

/** Main function */
int main() {
    assert(strings::lower("wow") == "wow");
    assert(strings::lower("HellZo") == "hellzo");
    assert(strings::lower("WHAT") == "what");
    assert(strings::lower("wh[]32") == "wh[]32");
    assert(strings::lower("whAT") == "what");
    return 0;
}
