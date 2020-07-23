/**
 * @file
 * @brief The implementation of hamilton's cycle dynamic solution for vertices
 * number less than 20.
 * @details
 * I use 2^n * n matrix it's and for every [i, j] (i < 2^n and j < n) in the
 * matrix I store there if it is possible to get to all vertices on which
 * position in i's binary representation is 1 so as j would be the last one.
 *
 * In the the end if any cell in (2^n - 1)th row is true there exists
 * hamiltonian cycle
 *
 * @author [vakhokoto](https://github.com/vakhokoto)
 * @author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <iostream>
#include <vector>

/**
 * The function determines if there is a hamilton's cycle in the graph
 *
 * @param n is the number of vertices in the graph
 * @param routes nxn boolean matrix of [i, j] where [i, j] is true if there is a
 * road between from i to j
 * @return `true` if there is hamiltonian cycle in the graph
 * @return `false` if there is no hamiltonian cycle in the graph
 */
bool hamilton_cycle(const std::vector<std::vector<bool>> &routes) {
    size_t n = routes.size();
    // height of dp array which is 2^n
    size_t height = 1 << n;
    std::vector<std::vector<bool>> dp(height, std::vector<bool>(n, false));

    // to fill in the [2^i, i] cells with true
    for (size_t i = 0; i < n; ++i) {
        dp[1 << i][i] = true;
    }
    for (size_t i = 1; i < height; i++) {
        std::vector<int> zeros, ones;
        // finding positions with 1s and 0s and separate them
        for (size_t pos = 0; pos < n; ++pos) {
            if ((1 << pos) & i) {
                ones.push_back(pos);
            } else {
                zeros.push_back(pos);
            }
        }

        for (auto &o : ones) {
            if (!dp[i][o]) {
                continue;
            }

            for (auto &z : zeros) {
                if (!routes[o][z]) {
                    continue;
                }
                dp[i + (1 << z)][z] = true;
            }
        }
    }

    bool is_cycle = false;
    for (int i = 0; i < n; i++) {
        is_cycle |= dp[height - 1][i];
    }
    return is_cycle;
}

/**
 * this test is testing if hamilton_cycle returns true for
 * graph: 1 -> 2 -> 3 -> 4
 */
bool test1() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, false, false}),
        std::vector<bool>({false, true, true, false}),
        std::vector<bool>({false, false, true, true}),
        std::vector<bool>({false, false, false, true})};

    bool ans = hamilton_cycle(arr);
    assert(ans);
    std::cout << "Test 1 passed\n";
    return ans;
}

/**
 * this test is testing if hamilton_cycle returns false for
 * graph: 1 -> 2 -> 3
 *             |
 *             V
 *             4
 */
bool test2() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, false, false}),
        std::vector<bool>({false, true, true, true}),
        std::vector<bool>({false, false, true, false}),
        std::vector<bool>({false, false, false, true})};

    bool ans = hamilton_cycle(arr);

    assert(!ans);  // not a cycle
    std::cout << "Test 2 passed\n";

    return !ans;
}

/**
 * this test is testing if hamilton_cycle returns true for
 * clique with 4 vertices
 */
bool test3() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true})};

    bool ans = hamilton_cycle(arr);

    assert(ans);
    std::cout << "Test 3 passed\n";

    return ans;
}

/**
 * Main function
 *
 * @param argc argument count
 * @param argv array of arguments
 */
int main(int argc, char **argv) {
    test1();
    test2();
    test3();
    return 0;
}
