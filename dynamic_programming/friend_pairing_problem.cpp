/**
 * @file
 * @brief [Friend Pairing Problem](https://www.geeksforgeeks.org/friends-pairing-problem) Implementation
 *
 * @details
 * Some friends want to go to party. Each one of them can go alone,
 * or with some other friend. Find the total number of ways N friends
 * can go to party. (return answer modulo 1e9 + 7)
 *
 * ### Algorithm
 * This problem can be solved with simple Dynamic Programming.
 * consider one friend decides to go alone, in that case total number
 * of ways will depend on what other friend decide. In different scenario
 * this friend decides to go with one of (n-1) friends then the total number of ways
 * will depend upon remaining (n-2) friends. so the final transition is..
 * dp[n] = dp[n-1] + (n-1)*dp[n-2];
 *
 * @author [Syed Faizan](https://github.com/faizan2700)
 */

 #include <cassert> /// assert for checking test
 #include <iostream> /// for IO operations
 #include <vector> /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
 namespace dynamic_programming{

/**
 * @namespace friend pairing problem
 * @brief Functions for [Friend pairing problem](https://www.geeksforgeeks.org/friends-pairing-problem) Implementation
 */
 namespace friend_pairing{

/**
 * @brief Find the total number of ways friend as described in problem
 * @param N number of friends going to the party.
 * @return Total number of ways
 */
 uint64_t calculate_total(const int &n){
    int M = 1e9 + 7; /// prime number for modulo, as stated in problem.
    std::vector<uint64_t> dp(n+1, 0); /// dp[i] shows number of ways of pairing i friends.
    dp[0] = dp[1] = 1; /// trivial base cases, if there are no friends, or only one friend
                       /// then only one way is possible.

    // i number of friends, dp[i] ways to distribute friends.
    for(int i = 2; i <= n; i++){
        dp[i] = dp[i-1] + (i-1)*dp[i-2];
        dp[i] %= M;
    }

    return dp[n];
 }
 }
 }


/**
 * @brief Self-test implementation
 * @returns void
 */
 static void test(){
    int n;
    // 1st test, trivial test
    n = 2;
    assert(dynamic_programming::friend_pairing::calculate_total(n) == 2);

    // 2nd test
    n = 10;
    assert(dynamic_programming::friend_pairing::calculate_total(n) == 9496);
 }

 /**
 * @brief Main function
 * @param argc count of arguments (ignored)
 * @param argv array of arguments (ignored)
 * @returns 0 on exit
 */
 int main(int argc, char* argv[]){
    test(); // run self-test implementation
    return 0;
 }
