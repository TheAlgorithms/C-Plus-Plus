#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string result = "";
        int i = a.size() - 1, j = b.size() - 1, carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;

            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';

            result += (sum % 2) + '0';  
            carry = sum / 2;            
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution solution;
    
    // Example 1
    string a1 = "11", b1 = "1";
    cout << "Input: a = \"11\", b = \"1\"" << endl;
    cout << "Output: " << solution.addBinary(a1, b1) << endl << endl;

    // Example 2
    string a2 = "1010", b2 = "1011";
    cout << "Input: a = \"1010\", b = \"1011\"" << endl;
    cout << "Output: " << solution.addBinary(a2, b2) << endl;

    return 0;
}
