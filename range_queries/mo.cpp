#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
const int N = 1e6 + 5;
int a[N], bucket[N], cnt[N];
int bucket_size;
struct query {
    int l, r, i;
} q[N];
int ans = 0;

/**
 * @brief Adds the element at `index` to the current frequency window.
 * @param index The index of the element in array `a` to add (what goes in).
 * @returns void (what comes out: returns nothing).
 * @note Modifies the global frequency array `cnt` by incrementing `cnt[a[index]]`,
 * and increments the global distinct counter `ans` if `cnt[a[index]] == 1` (what it changes).
 */
void add(int index) {
    cnt[a[index]]++;
    if (cnt[a[index]] == 1)
        ans++;
}
void remove(int index) {
    cnt[a[index]]--;
    if (cnt[a[index]] == 0)
        ans--;
}

bool mycmp(query x, query y) {
    if (x.l / bucket_size != y.l / bucket_size)
        return x.l / bucket_size < y.l / bucket_size;
    return x.r < y.r;
}

/**
 * @brief Test return value behavior.
 * `add` has return type void, meaning nothing is returned.
 */
static void test_return_value() {
    // Calling add() to verify it returns void
    add(0);
}

/**
 * @brief Test state mutations for smallest input (index 0, value 0).
 */
static void test_mutation_smallest_input() {
    ans = 0;
    a[0] = 0;
    cnt[0] = 0;

    add(0);

    if (cnt[0] != 1) {
        std::cerr << "Mutation check failed (smallest input): expected cnt[0] == 1, got "
                  << cnt[0] << "\n";
    }
    assert(cnt[0] == 1);

    if (ans != 1) {
        std::cerr << "Mutation check failed (smallest input): expected ans == 1, got "
                  << ans << "\n";
    }
    assert(ans == 1);
}

/**
 * @brief Test state mutations for ordinary input (index 1, value 7).
 */
static void test_mutation_ordinary_input() {
    ans = 1;
    a[1] = 7;
    cnt[7] = 0;

    add(1);

    if (cnt[7] != 1) {
        std::cerr << "Mutation check failed (ordinary input): expected cnt[7] == 1, got "
                  << cnt[7] << "\n";
    }
    assert(cnt[7] == 1);

    if (ans != 2) {
        std::cerr << "Mutation check failed (ordinary input): expected ans == 2, got "
                  << ans << "\n";
    }
    assert(ans == 2);
}

/**
 * @brief Test state mutations for repeated value (index 2, value 7 already in window).
 */
static void test_mutation_repeated_value() {
    a[2] = 7;

    add(2);

    if (cnt[7] != 2) {
        std::cerr << "Mutation check failed (repeated value): expected cnt[7] == 2, got "
                  << cnt[7] << "\n";
    }
    assert(cnt[7] == 2);

    if (ans != 2) {
        std::cerr << "Mutation check failed (repeated value): expected ans == 2, got "
                  << ans << "\n";
    }
    assert(ans == 2);
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    test_return_value();
    test_mutation_smallest_input();
    test_mutation_ordinary_input();
    test_mutation_repeated_value();
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
