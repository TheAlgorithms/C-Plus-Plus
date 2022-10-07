/*
 * @file
 * @brief Implementation to
 *XOR of Sum of All Pairs
 
 @details
 *We are given an array of integers and we have to find
 *the XOR of the sum of all pairs in the array.
 
Example :
[1 5 2 1 2] Here XOR of sum of all the pairs would be:
Ans = (1+5)^(1+2)^(1+1)^(1+2)^(5+2)^(5+1)^(5+2)^(2+1)^(2+2)^(1+2) 
Ans = 6^3^2^3^7^6^7^3^4^3 Eventually it will result in 10 So our output must be 10


2. Approach :
The problem here deals with finding the XOR of the sum of all pairs of the given array.
Let us consider another example: Input array: [ a, b, c, d ]

*We now want to know the XOR of all the pairings.
*One solution is to use nested looping, which involves generating each pair and then performing an XOR on the result. 
*In this scenario, the time complexity would be O(n2), but we'd like to reduce it to O (n).
*If we look closely, we can see that (a + b) repeats as (b+ a), and similarly, (a + c) repeats as (c + a), and so on.
*We can also observe that (a + a), (b + b), (c + c), and (d + d) are the only ones that don't repeat. 
*We can also observe that (a + a), (b + b), (c + c), and (d + d) are the only ones that don't repeat.
*As the repeating pairs like (a + b) and (b + a), (a + c) and (c + a),
*and so on cancel out, taking XOR of all the pairs equals taking XOR of (a + a), (b + b), (c + c), and (d + d).
*Also, {(a + a) ^ (b + b) ^ (c + c) ^ (d + d)} = {(2 * a) ^ (2 * b) ^ (2 * c) ^ (2 * d)} 
*As a result, we were able to change our O(n2) solution to an O(n) solution
*by simply examining repetitive patterns.
*We can further reduce this by one more property of the XOR operator. {(2 * a) ^ (2 * b) ^ (2 * c) ^ (2 * d)} = 2 * (a ^ b ^ c ^ d)
*Because (2*a) adds a zero to the right in the binary of a, this holds true.
*B, c, and d are in the same boat. When these doubled values are XORed,
*the rightmost zeros of each value give zero solely at the rightmost bit of the binary response. 
*And if we XOR all the elements first, then double the result, 
*we've introduced a zero in the binary to the right of the answer.
*Let's try to code this :
*/

// Time Complexity : O(N)
// Space Complexity : O(1)  (no extra space) 

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
  int xor_sum(vector<int> &v1)
  {
    int ans = 0;
    for (int &ele : v1)
      ans ^= (ele + ele);
    return ans;
  }
};
void test();
int main()
{
  test();
  return 0;
}
void test()
{
  Solution s;
  int cnt = 0; // for counting the test cases that passes
  vector<int> v1 = {1, 5, 2};
  if (s.xor_sum(v1) == 12)
    cnt++;
  vector<int> v2 = {1, 7, 9, 21};
  if (s.xor_sum(v2) == 52)
    cnt++;
  vector<int> v3 = {3, 5, 6, 2};
  if (s.xor_sum(v3) == 4)
    cnt++;
  vector<int> v4 = {12, 54, 2, 2};
  if (s.xor_sum(v4) == 116)
    cnt++;
  vector<int> v5 = {1, 5, 2, 1, 2};
  if (s.xor_sum(v5) == 10)
    cnt++;
  if (cnt == 5)
    cout << "ALL TEST CASES PASSED"
         << "\n";
}
