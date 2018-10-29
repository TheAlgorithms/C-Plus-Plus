#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using dynamic_bitset = bitset<sizeof(size_t) * 8>;

static inline void init_char_mask(vector<dynamic_bitset> &v, string &pattern) {
    dynamic_bitset pos_mask = -2;
    for (char &c : pattern) {
        v[static_cast<unsigned char>(c)] &= pos_mask;
        pos_mask <<= 1;
        pos_mask |= 0x01;
    }
}

static inline vector<size_t> wu_manber(vector<dynamic_bitset> &char_mask, size_t &m, string &text, size_t &e) {
    vector<size_t> occurrences;

    vector<dynamic_bitset> s(e + 1, -1);
    for (size_t i = 0; i < text.length(); ++i) {
        s[0] = (s[0] << 1) | char_mask[static_cast<unsigned char>(text[i])];

        dynamic_bitset prev = s[0];
        for (size_t j = 1; j <= e; ++j) {
            dynamic_bitset db = s[j];
            s[j] = ((s[j] << 1) | char_mask[static_cast<unsigned char>(text[i])]) & (s[j - 1] << 1) & (prev << 1) &
                   prev;
            prev = db;
        }

        if (!s[e][m - 1])
            occurrences.emplace_back(i);
    }

    return occurrences;
}

static inline bool wm_exists(vector<dynamic_bitset> &char_mask, size_t &m, string &text, size_t &e) {
    vector<dynamic_bitset> s(e + 1, -1);
    for (char &c : text) {
        s[0] = (s[0] << 1) | char_mask[static_cast<unsigned char>(c)];

        dynamic_bitset prev = s[0];
        for (size_t i = 1; i <= e; ++i) {
            dynamic_bitset db = s[i];
            s[i] = ((s[i] << 1) | char_mask[static_cast<unsigned char>(c)]) & (s[i - 1] << 1) & (prev << 1) & prev;
            prev = db;
        }

        if (!s[e][m - 1])
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

    size_t edit_distance;
    stringstream(argv[3]) >> edit_distance;

    vector<dynamic_bitset> cm(UCHAR_MAX, -1);
    init_char_mask(cm, pattern);

    string text;
    while (getline(file, text)) {
        if (!file.eof())
            text += '\n';

        if (text.length() < pattern.length())
            continue;

//        vector<size_t> occurrences = wu_manber(cm, m, text, edit_distance);
//
//        for (auto i : occurrences)
//            cout << '\t' << i << endl;
//
//        if (!occurrences.empty())
//            cout << text;

        if (wm_exists(cm, m, text, edit_distance))
            cout << text;

        if (file.eof())
            cout << endl;
    }

    return 0;
}
