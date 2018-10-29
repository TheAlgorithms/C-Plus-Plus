#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

static inline void init_border(vector<size_t> &v, string &pattern) {
    size_t m = pattern.length();
    size_t c = m - 1;

    for (size_t i = 1, j = 0; i + j < m; i += max(j - v[j], static_cast<size_t>(1)), j = v[j])
        while (i + j < m && pattern[c - (i + j)] == pattern[c - j]) {
            ++j;
            v[i + j] = j;
        }
}

static inline void init_good_suffix(vector<size_t> &v, string &pattern) {
    size_t m = pattern.length();

    vector<size_t> b(pattern.length() + 1);
    init_border(b, pattern);

    fill(v.begin(), v.end(), m - b[m]);
    for (size_t l = 1; l <= m; ++l) {
        size_t j = min(m - 1 - b[l], m);
        if (v[j] > l - b[l])
            v[j] = l - b[l];
    };
}

static inline void init_bad_char(vector<size_t> &v, string &pattern) {
    size_t i = 0;
    for (char &c : pattern)
        v[c] = i++;
}

static inline vector<size_t> boyer_moore(string &text, string &pattern, vector<size_t> &bc, vector<size_t> &gs) {
    size_t n = text.length();
    size_t m = pattern.length();

    vector<size_t> occurrences;

    for (size_t i = 0; i <= n - m;) {
        size_t j = m - 1;
        while (j >= 0 && text[i + j] == pattern[j])
            --j;

        if (j == static_cast<size_t>(-1)) {
            occurrences.emplace_back(i);
            i += gs[m];
        } else
            i += min(max(gs[j], j - bc[text[i + j]]), m);
    }

    return occurrences;
}

static inline bool bm_exists(string &text, string &pattern, vector<size_t> &bc, vector<size_t> &gs) {
    size_t n = text.length();
    size_t m = pattern.length();

    for (size_t i = 0; i <= n - m;) {
        size_t j = m - 1;
        while (j >= 0 && text[i + j] == pattern[j])
            --j;

        if (j == static_cast<size_t>(-1))
            return true;

        i += min(max(gs[j], j - bc[text[i + j]]), m);
    }

    return false;
}

int main(int argc, char *argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ifstream file(argv[1]);
    string pattern = argv[2];

    vector<size_t> bc(UCHAR_MAX, static_cast<size_t>(-1));
    init_bad_char(bc, pattern);

    vector<size_t> gs(pattern.length() + 1);
    init_good_suffix(gs, pattern);

    string text;
    while (getline(file, text)) {
        if (!file.eof())
            text += '\n';

        if (text.length() < pattern.length())
            continue;

//        vector<size_t> occurrences = boyer_moore(text, pattern, alphabet, bc, gs);
//
//        for (auto i : occurrences)
//            cout << '\t' << i << endl;
//
//        if (!occurrences.empty())
//            cout << text;

        if (bm_exists(text, pattern, bc, gs))
            cout << text;

        if (file.eof())
            cout << endl;
    }

    return 0;
}
