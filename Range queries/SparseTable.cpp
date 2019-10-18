#include <vector>
using namespace std;

template <class type_t>
struct SparseTable {
    int n;
    vector<vector<type_t>> mat;

    type_t func(const type_t& a, const type_t& b) const {
        return max(a, b);
    }

    SparseTable(const vector<type_t>& a) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for (int j = 1; j < max_log; j++) {
            mat[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    type_t get(int from, int to) const {
        assert(0 <= from && from <= to && to <= n - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }

/*
    Use the following function for operations that are not idempotent

    type_t get(int from, int to) const {
        int res = -inf;     // inf for min query
        int max_log = 32 - __builtin_clz(n);
        for (int j = max_log - 1; j >= 0; j--) {
            if ((1 << j) <= (to - from + 1)) {
                res = func(res, mat[j][from]);
                from += (1 << j);
            }
        }
        return res;
    }
*/
};
