#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif
#include <assert.h>

std::string lower(std::string word) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] + 32;
        }
    }
    return word;
}

/** Main function */
int main() {
    assert(lower("wow") == "wow");
    assert(lower("HellZo") == "hellzo");
    assert(lower("WHAT") == "what");
    assert(lower("wh[]32") == "wh[]32");
    assert(lower("whAT") == "what");
    return 0;
}
