#include <algorithm>
#include <iostream>

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
