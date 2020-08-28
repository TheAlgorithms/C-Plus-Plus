/**
 * @file
 * @brief The implementation of [Hamilton's
 * cycle](https://en.wikipedia.org/wiki/Hamiltonian_path) dynamic solution for
 * vertices number less than 20.
 * @details
 * I use \f$2^n\times n\f$ matrix and for every \f$[i, j]\f$ (\f$i < 2^n\f$ and
 * \f$j < n\f$) in the matrix I store `true` if it is possible to get to all
 * vertices on which position in `i`'s binary representation is `1` so as
 * \f$j\f$ would be the last one.
 *
 * In the the end if any cell in \f$(2^n - 1)^{\mbox{th}}\f$ row is `true` there
 * exists hamiltonian cycle.
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
 * @param routes nxn boolean matrix of \f$[i, j]\f$ where \f$[i, j]\f$ is `true`
 * if there is a road from \f$i\f$ to \f$j\f$
 * @return `true` if there is Hamiltonian cycle in the graph
 * @return `false` if there is no Hamiltonian cycle in the graph
 */
bool hamilton_cycle(const std::vector<std::vector<bool>> &routes) {
    const size_t n = routes.size();
    // height of dp array which is 2^n
    const size_t height = 1 << n;
    std::vector<std::vector<bool>> dp(height, std::vector<bool>(n, false));

    // to fill in the [2^i, i] cells with true
    for (size_t i = 0; i < n; ++i) {
        dp[1 << i][i] = true;
    }
    for (size_t i = 1; i < height; i++) {
        std::vector<size_t> zeros, ones;
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
    for (size_t i = 0; i < n; i++) {
        is_cycle |= dp[height - 1][i];
        if (is_cycle) {  // if true, all subsequent loop will be true. hence
                         // break
            break;
        }
    }
    return is_cycle;
}

/**
 * this test is testing if ::hamilton_cycle returns `true` for
 * graph: `1 -> 2 -> 3 -> 4`
 * @return None
 */
static void test1() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, false, false}),
        std::vector<bool>({false, true, true, false}),
        std::vector<bool>({false, false, true, true}),
        std::vector<bool>({false, false, false, true})};

    bool ans = hamilton_cycle(arr);
    std::cout << "Test 1... ";
    assert(ans);
    std::cout << "passed\n";
}

/**
 * this test is testing if ::hamilton_cycle returns `false` for
 * \n graph:<pre>
 *  1 -> 2 -> 3
 *       |
 *       V
 *       4</pre>
 * @return None
 */
static void test2() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, false, false}),
        std::vector<bool>({false, true, true, true}),
        std::vector<bool>({false, false, true, false}),
        std::vector<bool>({false, false, false, true})};

    bool ans = hamilton_cycle(arr);

    std::cout << "Test 2... ";
    assert(!ans);  // not a cycle
    std::cout << "passed\n";
}

/**
 * this test is testing if ::hamilton_cycle returns `true` for
 * clique with 4 vertices
 * @return None
 */
static void test3() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true})};

    bool ans = hamilton_cycle(arr);

    std::cout << "Test 3... ";
    assert(ans);
    std::cout << "passed\n";
}

/**
 * Main function
 *
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 */
int main(int argc, char **argv) {
    test1();
    test2();
    test3();
    return 0;
}
