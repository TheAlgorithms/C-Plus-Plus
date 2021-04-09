/**
* @file
* @brief Implementation of Bitmasking DP approach
*
* @details
* Given Integer N and Array of size 2*N. Make N pairs using each element
* exactly once such that following score is maximized.
* score = summation(gcd(x_i, y_i) * i)
* for 1 <= i <= N, (x_i, y_i) is i-th pair.
* N <= 10
* 1 <= A[i] <= 1e9
*
* ###Algorithm
* For each Mask 0 to 111....(2*N times) Add new pair to this set from yet
* unselected elements and try to maximize the newly formed mask after
* adding these elements with value formed after adding new pair.
* the ans we are looking for will be in mask which shows all elements are
* added, that is 111...(2*N times).
*
* @author [Syed Faizan](https://github.com/faizan2700)
*/


#include <algorithm>
#include <assert.h>
#include <cstring>
#include <iostream>
#include <vector>


/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming{
/**
 * @namespace dp_bitmask
 * @brief Implementation of DP with Bitmasking
 */
namespace dp_bitmask{
/**
 * @brief find maximum value of new mask by adding
 * pair to previously formed mask.
 * @param A an array of elements from which pairs will be made.
 * @param N size of an array.
 * @return maximum score which can be formed with pairs of this array.
 */
uint64_t find_max_score(uint32_t A[], uint8_t N){

    uint32_t G[2*N][2*N]; // G[i][j] contains gcd of (A[i], A[j])
    for(uint8_t i = 0; i < 2*N; i++){
        for(uint8_t j = 0; j < 2*N; j++){
            G[i][j] = std::__gcd(A[i], A[j]);
        }
    }


    uint32_t M = 1 << 2*N;
    uint64_t dp[M]; // dp[i] contains max score possible by mask i
    memset(dp, 0, sizeof(dp));

    // the outer loop iterate over all possible mask till all the elements are added.
    // the first inner loop collects index of all un-added elements.
    // nested inner loop iterate over all the pairs formed by un added elements.
    for(uint32_t i = 0; i < M; i++){

        std::vector<uint8_t> unselected_elements;
        for(uint8_t j = 0; j < 2*N; j++) if((i>>j)%2==0) unselected_elements.push_back(j);

        uint8_t total_unselected = (uint8_t)unselected_elements.size();
        if(total_unselected%2==1) continue;

        uint8_t total_selected = 2*N - total_unselected;
        uint8_t total_pairs = total_selected/2;

        for(uint8_t j1 = 0; j1 < total_unselected; j1++){
            for(uint8_t j2 = j1+1; j2 < total_unselected; j2++){
                uint8_t x = unselected_elements[j1], y = unselected_elements[j2];
                uint32_t new_mask = i | (1<<x) | (1<<y);
                dp[new_mask] = std::max(dp[new_mask], dp[i] + 1LL * (total_pairs + 1) * G[x][y]);
            }
        }
    }

    //Max score is in the mask 2**(1<<2*N) - 1, which shows all elements are added.
    return dp[M-1];

}

} //namespace dp_bitmask
} //namespace dynamic_programming


/**
 * @brief Function to test above algorithm
 * @returns void
 */
static void test(){
    uint8_t N = 5;
    uint32_t A[2*N];
    uint64_t ans = 0;

    // Test 1
    for(uint8_t i = 0; i < 2*N; i++) A[i] = i+1;
    ans = dynamic_programming::dp_bitmask::find_max_score(A, N);
    assert(ans == 55);

    // Test 2
    N = 4;
    for(uint8_t i = 0; i < 2*N; i++) A[i] = i+1;
    ans = dynamic_programming::dp_bitmask::find_max_score(A, N);
    assert(ans == 28);

    return;
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(){
    //Testing
    test();
    return 0;
}
