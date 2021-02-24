#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif
#include <assert.h>

std::string upper(std::string word) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = word[i] - 32;
        }
    }
    return word;
}

/** Main function */
int main() {
    assert(upper("wow") == "WOW");
    assert(upper("hellzo") == "HELLZO");
    assert(upper("what") == "WHAT");
    assert(upper("wh[]32") == "WH[]32");
    assert(upper("what") == "WHAT");
    return 0;
}
