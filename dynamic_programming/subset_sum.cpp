/**
 * @file
 * @brief Implementation of subset_sum problem
 *
 * @details
 * Give a value "V" and set of non-negative integers
 * Determine if there is subset which has sum = V.
 *
 * ### Algorithm
 * DP[i][j] shows considering i-elements from start, is it possible to get
 * the sum = j?. we will populate this dp for sum 0 to required sum, adding
 * one element at time. and dp[n][V] will store the boolean value for answer.
 *
 * @author [Syed Faizan](https://github.com/faizan2700)
 */

 #include <array>
 #include <iostream>
 #include <cassert>
 #include <vector>

 /**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace subset_sum
 * @brief Implementation of subset_sum problem
 */
namespace subset_sum {
/**
 * @brief for each sum less than V calculate if it is possible
 * to get with help of first i elements. By making use of previously
 * calculated info subset sum can be solved in O(n*V) complexity.
 * @tparam T size of the set
 * @param A set of the allowed values.
 * @param n size of the array A.
 * @param v is give sum of subset to be checked.
 * @return true if possible to get subset sum of value "v", false otherwise.
 */
template <size_t T>
bool subset_sum(const std::array<int, T> &A, const uint32_t &n, const uint64_t &v) {

    uint64_t S = 0;
    for(int i = 0; i < n; i++) S += A[i];

    if(v > S) return false; // if value is greater than sum of set than not possible.

    std::vector< std::vector<bool> > dp(n+1, std::vector<bool>(v + 1, false));

    for(int i = 0; i <= n; i++) dp[i][0] = true; // 0 sum is always possible.
    for(int i = 1; i <= v; i++) dp[0][i] = false; // no sum is possible when 0 elements are included.

    //outer loop iterates over all the element
    //inner loop iterates over all the possible sum.
    //for elements including till i, sum "j" can only be obtained if it is available with or without current element.
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= v; j++){
            dp[i][j] = dp[i-1][j] or (j>=A[i-1]? dp[i-1][j-A[i-1]] : 0);
        }
    }

    //1 if obtainable, 0 otherwise.
    return dp[n][v];

}
} // namespace dynamic_programming
} // namespace subset_sum



/**
 * @brief Function to test subset_sum
 * @returns void
 */
static void test(){

    bool ans;
    uint64_t v;
    // Test 1
    const uint32_t N1 = 5;
    v = 9;
    std::array<int, N1> A = {1, 2, 3, 4, 5};
    ans = dynamic_programming::subset_sum::subset_sum(A, N1, v);
    assert(ans);

    // Test 2
    const uint32_t N2 = 6;
    v = 13;
    std::array<int, N2> B = {2, 4, 6, 8, 10, 12};
    ans = dynamic_programming::subset_sum::subset_sum(B, N2, v);
    assert(!ans);

    return;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(){
    // Testing
    test();
    return 0;
}
