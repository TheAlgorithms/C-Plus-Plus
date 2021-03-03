#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif
#include <assert.h>

namespace strings {
/**
 * Will convert the entire string to uppercase letters
 * @param word is the text you want to uppercase
 * @return An uppercase copy of the string.
 */
std::string upper(std::string word) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = word[i] - 32;
        }
    }
    return word;
}
}  // namespace strings

/** Main function */
int main() {
    assert(strings::upper("wow") == "WOW");
    assert(strings::upper("hellzo") == "HELLZO");
    assert(strings::upper("what") == "WHAT");
    assert(strings::upper("wh[]32") == "WH[]32");
    assert(strings::upper("what") == "WHAT");
    return 0;
}
