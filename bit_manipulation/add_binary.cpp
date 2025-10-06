#include <iostream>
#include <string>
#include <algorithm>

std::string add_binary(std::string a, std::string b) {
    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0;
    std::string result = "";

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0'; // convert char to int
        if (j >= 0) sum += b[j--] - '0';
        result += (sum % 2) + '0'; // convert int back to char
        carry = sum / 2;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string a = "1010";
    std::string b = "1011";
    std::cout << "Sum: " << add_binary(a, b) << std::endl; // Output: 10101
    return 0;
}
