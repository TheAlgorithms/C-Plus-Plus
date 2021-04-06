/*
@details
 Given two strings str1 & str2 and we have to calculate the minimum
 number of operations (Insert, Delete, Replace) required to convert
 str1 to str2.

 @Author
 Nirzak (github.com/nirzak)
 */
#include<cassert>
#include<iostream>
/*
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */

namespace dynamic_programming
{
/*
 * @namespace Minimum Edit Distance
 * @brief Implementation of 0-1 Knapsack problem
 */


namespace minimum_edit_distance
{
/*function to return minimum of three operations
Insert, Replace or Delete
*/
int min(int x, int y, int z)
{
    if (x <= y && x <= z)
        return x;
    if (y <= x && y <= z)
        return y;
    else
        return z;
}


int editDistDP(std::string str1, std::string str2, int m, int n)
{
    // Create a table to store results of subproblems
    int dp[m+1][n+1];

    // Fill d[][] in bottom up manner
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i==0)
                dp[i][j] = j;  // Min. operations = j

            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j==0)
                dp[i][j] = i; // Min. operations = i

            // If last characters are same, ignore last char
            // and recur for remaining string
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];

            // If the last character is different, consider all
            // possibilities and find the minimum
            else
                dp[i][j] = 1 + min(dp[i][j-1],
                                   dp[i-1][j],
                                   dp[i-1][j-1]);
        }
    }

    return dp[m][n];
}
}
}

//function to test above algorithm
static void test()
{
    //test 1
    std::string str1 = "INTENTION";
    std::string str2 = "EXECUTION";
    const int expected_output1 = 5;
    const int output1 = dynamic_programming::
                        minimum_edit_distance::
                        editDistDP(str1, str2,str1.length(),str2.length());
    assert(output1==expected_output1);
    std::cout << "Minimum Number of Operations Required: "<< output1<<std::endl;
    //test 2
    std::string str3 = "SATURDAY";
    std::string str4 = "SUNDAY";
    const int expected_output2 = 3;
    const int output2 = dynamic_programming::
                        minimum_edit_distance::
                        editDistDP(str3, str4, str3.length(),str4.length());
    assert(output2==expected_output2);
    std::cout << "Minimum Number of Operations Required: "<< output2<<std::endl;


}

// Driver program
int main()
{
    test();
    return 0;
}
