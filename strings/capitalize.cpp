#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif
#include <assert.h>

std::string capitalize(std::string string) {
    if (string[0] >= 'a' && string[0] <= 'z') {
        return string.insert(0, 1, string[0] - 32).erase(1, 1);
    } else {
        return string;
    }
}

int main() {
    assert(capitalize("hello world") == "Hello world");
    assert(capitalize("123 hello world") == "123 hello world");
    assert(capitalize(" hello world") == " hello world");
    assert(capitalize("a") == "A");
    assert(capitalize("") == "");
    return 0;
}