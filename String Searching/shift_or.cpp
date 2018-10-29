#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using dynamic_bitset = bitset<sizeof(size_t) * 8>;

static inline void init_char_mask(vector<dynamic_bitset> &v, string &pattern) {
    dynamic_bitset pos_mask = -2;
    for (char &c : pattern) {
        v[c] &= pos_mask;
        pos_mask <<= 1;
        pos_mask |= 0x1;
    }
}

static inline vector<size_t> shift_or(vector<dynamic_bitset> &char_mask, size_t &m, string &text) {
    vector<size_t> occurrences;

    dynamic_bitset s = -1;
    for (int i = 0; i < text.length(); ++i) {
        s = (s << 1) | char_mask[static_cast<unsigned char>(text[i])];

        if (!s[m - 1])
            occurrences.emplace_back(i - m + 1);
    }

    return occurrences;
}

static inline bool so_exists(vector<dynamic_bitset> &char_mask, size_t &m, string &text) {
    dynamic_bitset s = -1;
    for (char &c : text) {
        s = (s << 1) | char_mask[static_cast<unsigned char>(c)];

        if (!s[m - 1])
            return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ifstream file(argv[1]);

    string pattern = argv[2];
    size_t m = pattern.length();

    vector<dynamic_bitset> cm(UCHAR_MAX, -1);
    init_char_mask(cm, pattern);

    string text;
    while (getline(file, text)) {
        if (!file.eof())
            text += '\n';

        if (text.length() < pattern.length())
            continue;

//        vector<size_t> occurrences = shift_or(cm, m, text);
//
//        for (auto i : occurrences)
//            cout << '\t' << i << endl;
//
//        if (!occurrences.empty())
//            cout << text;

        if (so_exists(cm, m, text))
            cout << text;

        if (file.eof())
            cout << endl;
    }

    return 0;
}
