#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
BINARY TO DECIMAL METHOD
This method converts binary to decimal by reversing a binary string and calculating the decimal representation using the "pow" algorithm.
**/

int binaryToDecimal(string &binary)
{
    reverse(binary.begin(), binary.end());
    int decimal = 0, i = 0, binarySize = binary.size();

    while (binarySize--) {
        if (binary[i] == '1')
            decimal += pow(2, i);
        i++;
    }

    return decimal;
}

int main()
{
    string binary;
    cout << "Enter a binary number: ";
    cin >> binary;
    cout << "Binary to decimal is: " << binaryToDecimal(binary);
}
