#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif
#include <assert.h>

namespace strings {
/**
 * This function will capitalize the first letter of a sentence or a word
 * @param str is the text you want to capitalize
 * @return An uppercase copy of the string.
 */
std::string capitalize(std::string str) {
    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - 32;
        return str;
    } else {
        return str;
    }
}
}  // namespace strings

int main() {
    assert(strings::capitalize("hello world") == "Hello world");
    assert(strings::capitalize("123 hello world") == "123 hello world");
    assert(strings::capitalize(" hello world") == " hello world");
    assert(strings::capitalize("a") == "A");
    assert(strings::capitalize("") == "");

    return 0;
}