// C++ Program for counting sort
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void countSort(string& arr) {
    int n = static_cast<int>(arr.length());
    
    // Handle edge cases first
    if (n == 0) {
        cout << "Empty String\n";
        return;
    }
    
    if (n == 1) {
        cout << "Already Sorted " << arr << '\n';
        return;
    }

    // output string preallocated with correct size
    string output(n, '\0');

    // use 256 for all possible unsigned char values
    vector<int> count(256, 0);

    // store count of each character
    for (int i = 0; i < n; ++i) {
        ++count[static_cast<unsigned char>(arr[i])];
    }

    // change count[i] so that count[i] now contains actual
    // position of this character in output
    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    // build the output array (iterate from end for stable sort)
    for (int i = n - 1; i >= 0; --i) {
        unsigned char ch = static_cast<unsigned char>(arr[i]);
        int pos = count[ch] - 1;  // position index in output
        output[pos] = arr[i];
        --count[ch];
    }

    // copy output to arr
    arr = output;
    cout << "Sorted character array is " << arr << '\n';
}

int main() {
    string s1 = "hello";
    countSort(s1);  // Sorted character array is ehllo

    string s2 = "AaBbZz012";
    countSort(s2); // Sorted character array is 012ABZabz

    string s3 = "";
    countSort(s3); // Empty String

    string s4 = "x";
    countSort(s4); // Already Sorted x

    return 0;
}

