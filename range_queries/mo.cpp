/**
 *
 * @file
 * \brief A C++ Program to compute unique elements of ranges for different range
 * queries
 *
 * \details
 * The preprocessing part takes O(m Log m) time.
 * Processing all queries takes O(n * √n) + O(m * √n) = O((m+n) * √n) time.
 */
#include <algorithm>
#include <iostream>
const int N = 1e6 + 5;
int a[N], bucket[N], cnt[N];
// Variable to represent block size. This is made global so compare() of sort
// can use it.
int bucket_size;
// Structure to represent a query range
struct query {
    int l, r, i;
} q[N];
// variable to maintain the count of unique elements.
int ans = 0;
// Function to add elements
void add(int index) {
    cnt[a[index]]++;
    if (cnt[a[index]] == 1)
        ans++;
}
// Function to remove elements
void remove(int index) {
    cnt[a[index]]--;
    if (cnt[a[index]] == 0)
        ans--;
}
/**
 *Function used to sort all queries so that all queries
 *of the same block are arranged together and within a block,
 *queries are sorted in increasing order of R values.
 */
bool mycmp(query x, query y) {
    // Different blocks, sort by block.
    if (x.l / bucket_size != y.l / bucket_size)
        return x.l / bucket_size < y.l / bucket_size;
    // Same block, sort by R value
    return x.r < y.r;
}

/**
 * Main Function
 */
int main() {
    int n, t, i, j, k = 0;
    cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i]
    }
    // Find block size
    bucket_size = ceil(sqrt(n));
    std::cin >> t;
    for (i = 0; i < t; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].l--;
        q[i].r--;
        q[i].i = i;
    }
    // Sort all queries so that queries of same blocks are arranged together.

    std::sort(q, q + t, mycmp);
    // Initialize current left, current right
    int left = 0, right = 0;
    // Traverse through all queries
    for (i = 0; i < t; i++) {
        // L and R values of current range
        int L = q[i].l, R = q[i].r;
        // Remove extra elements of previous range
        while (left < L) {
            remove(left);
            left++;
        }
        // Add Elements of current Range
        while (left > L) {
            add(left - 1);
            left--;
        }
        while (right <= R) {
            add(right);
            right++;
        }

        // Remove elements of previous range.
        while (right > R + 1) {
            remove(right - 1);
            right--;
        }
        bucket[q[i].i] = ans;
    }
    // Print unique elements in current range
    for (i = 0; i < t; i++) {
        
        std::cout << bucket[i] << endl;
    }
    return 0;
}
