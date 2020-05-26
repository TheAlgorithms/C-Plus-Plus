#include <algorithm>
#include <iostream>

#ifdef _MSC_VER
// Required to compile std::toString function using MSVC
#include <string>
#else
#include <cstring>
#endif

int main() {
    int num;
    std::cout << "Enter number = ";
    std::cin >> num;

    std::string s1 = std::to_string(num);
    std::string s2 = s1;

    reverse(s1.begin(), s1.end());

    if (s1 == s2)
        std::cout << "true";
    else
        std::cout << "false";

    return 0;
}
