#include <iostream>
#include <string>
using namespace std;

// Run Length Encoding
string encode(const string& input) {
    string encoded = "";
    int n = input.length();
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        encoded += input[i] + to_string(count);
    }
    return encoded;
}

// Run Length Decoding
string decode(const string& input) {
    string decoded = "";
    int n = input.length();
    for (int i = 0; i < n; i += 2) {
        char ch = input[i];
        int count = input[i + 1] - '0';
        decoded += string(count, ch);
    }
    return decoded;
}

// Driver code
int main() {
    string original = "aaabbcdddd";
    string encoded = encode(original);
    string decoded = decode(encoded);

    cout << "Original: " << original << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}
