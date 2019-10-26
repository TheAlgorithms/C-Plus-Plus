class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.length();
        int step = 2 * numRows - 2;
        string ret;

        if (numRows == 0) {
            return "";
        }

        if (numRows == 1) {
            return s;
        }

        for (int i = 0; i < n; i += step) {
            ret.push_back(s[i]);
        }

        for (int i = 1; i < numRows - 1; i++) {
            int half_step[2] = {step - 2 * i, 2 * i};
            int k = i;
            for (int j = 0; k < n; j++) {
                ret.push_back(s[k]);
                k = k + half_step[j % 2];
            }
        }

        for (int i = numRows - 1; i < n; i += step) {
            ret.push_back(s[i]);
        }

        return ret;
    }
};