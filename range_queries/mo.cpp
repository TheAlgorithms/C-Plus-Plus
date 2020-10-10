#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
const int N = 1e6 + 5;
std::array<int, N> a{};
std::array<int, N> bucket{};
std::array<int, N> cnt{};
int bucket_size;
struct query {
    int l, r, i;
} q[N];
int ans = 0;

void add(int index) {
    cnt[a[index]]++;
    if (cnt[a[index]] == 1) {
        ans++;
    }
}
void remove(int index) {
    cnt[a[index]]--;
    if (cnt[a[index]] == 0) {
        ans--;
    }
}

bool mycmp(query x, query y) {
    if (x.l / bucket_size != y.l / bucket_size) {
        return x.l / bucket_size < y.l / bucket_size;
    }
    return x.r < y.r;
}

int main() {
    int n = 0, t = 0, i = 0, j = 0, k = 0;
    std::cin >> n;
    for (i = 0; i < n; i++) std::cin >> a[i];
    bucket_size = std::ceil(std::sqrt(n));
    std::cin >> t;
    for (i = 0; i < t; i++) {
        std::cin >> q[i].l;
        std::cin >> q[i].r;
        q[i].l--;
        q[i].r--;
        q[i].i = i;
    }
    std::sort(q, q + t, mycmp);
    int left = 0, right = 0;
    for (i = 0; i < t; i++) {
        int L = q[i].l, R = q[i].r;
        while (left < L) {
            remove(left);
            left++;
        }
        while (left > L) {
            add(left - 1);
            left--;
        }
        while (right <= R) {
            add(right);
            right++;
        }
        while (right > R + 1) {
            remove(right - 1);
            right--;
        }
        bucket[q[i].i] = ans;
    }
    for (i = 0; i < t; i++) std::cout << bucket[i] << "\n";
    return 0;
}
