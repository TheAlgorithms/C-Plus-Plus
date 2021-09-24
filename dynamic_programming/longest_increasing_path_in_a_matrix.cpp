/**
 * @file
 * @brief Implementation of [Longest Increasing Path in a Matrix]
 * @details
 * 
 * Given an m x n int egers matrix, return the length of the longest increasing path in matrix.
 * From each cell, you can either move in four directions: left, right, up, or down. 
 * You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
 * Possible Constraint s:-
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 200
 * 0 <= matrix[i][j] <= 231 - 1
 * 
 * ### Algorithm
 * We Will do A DFS Traversal From every element of the matrix
 * and check for the longest increasing path and the answer will be maximum of
 * all the path.
 * As path can be repeated for example we move from a element at position i,j having value x
 * We do DFS traversal from that element x after certain traversal we got to a position for which we
 * already knew the longest increasing path so we can use that result. thus, avoiding overlapping case
 * Thats why we use dp aka dynamic programming in this. As there are two parameters that are changing 
 * ie i and j so the dimension of our dp array will be 2.
 * @author [Ayush Mishra](https://github.com/Beyonday008)
 */

#include <cassert>   /// for assert
#include<iostream>
#include<vector>
#include<cstring>

/*
* The "dir" array signify the four direction we can move in
* i.e down,up,right and left; 
*/
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}}; 
/*
As per our constraint  matrix size can be at max 200 by 200.  
So our dp array will be 200 by 200
*/
int  dp[201][201];

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */


namespace dynamic_programming{

/**
 * @namespace Longest Increasing Path in a Matrix
 * @brief Implementation of [Longest Increasing Path in a Matrix]
 */

namespace longest_increasing_path_in_a_matrix{

/**
 * @brief Takes input of current element position and to dfs traversal
 * to find the maximum path from this current value
 * if theres is a overlapping case it will use dp.
 * @param arr Original Array in which we need to find longest path
 * @param n No.of row
 * @param m No.of Column
 * @param i Current row
 * @param j Current Column
 * @returns dp[i][j] which is the current maximum longest path from arr[i][j]
 */
int  dfs(std::vector<std::vector<int>>&arr,int  n,int  m,int  i,int  j){
    /* 
    First of all we will see that whelter we already knew
    the longest increasing path of the current element if we knew
    we will just simply return that value ie path.(Avoiding overlapping cases) 
    */
    if(dp[i][j]){
        return dp[i][j];
    }

    // intialise a variable ma which will store the path value for current element.
    int ma = 0;

    /*
    Now we Have 4 Direction to go ie left,right,up and down.
    So We will loop through our direction array and add the value to 
    current index of row and column to get the left,right,up and down
    direction and then traverse them recursively.
    */
    for(int a=0;a<4;a++){
        /* 
        u represent next direction row index
        v represents next direction column index
        */
        int u = dir[a][0]+i,v=dir[a][1]+j;
        // std::cout<<u<<" "<<v<<std::endl;
        /*
        If the left direction or the right direction is 
        in the bounds of matrix ie u>=0 and u<n and v>=0 and v<m
        and also the path is more than current matrix element because
        we need increasing path so the next element value at the next recursive
        call must be greater than the current one

        If the above condition is satisfied we will do a recursive call
        ie we will go in depth and traverse further path 
        So this type of traversal is called DFS Traversal.
        */
        if(u>=0 && u<n && v>=0 &&v<m && arr[u][v]>arr[i][j]){
            // getting the len of path from current element of matrix
            int len = dfs(arr,n,m,u,v);

            // picking u the maximum of all the path.
            ma = std::max(ma,len);
            // cout<<ma<<endl;
        }
    }

    // since we haven't consider the current element so we will add "1" to it.
    // And Store in our dp array or we are doing a type of caching.
    dp[i][j] = ma+1;

    // return the value;
    return dp[i][j];
}


/**
 * @brief Takes input of the matrix and return the longest increasing path length
 * @param arr Original Array in which we need to find longest path
 * @returns ans which is the length of the longest increasing path in the matrix
 */
int  longestIncreasingPath(std::vector<std::vector<int>>&arr) {
    // size of row and column.
    int n = arr.size(),m=arr[0].size();

    // intialise our dp array 0 upto dp[n][m];
    int dp[n][m];

    // using memset to fill all the value upto dp[n][m]=0
    // one can also use for loop for the same.
    memset(dp,0,sizeof(dp));

    // intialising our answer variable to 0
    int ans = 0;

    // Now we will do dfs traversal for every element of our matrix ie arr
    // and pick the maximum out of all that will be our answer
    for(int i=0;i<n;i++){
        for(int j = 0;j<m;j++){
            /*
            dfs traversal from current element
            We will be passing 5 argument
            1.) Our matrix
            2.) Size of Our Row
            3.) Size of Our Column
            4.) Index of Row we currently at.
            5.) Index of Column we current at.
            */
            int curr = dfs(arr,n,m,i,j);

            // picking out the maximum
            ans = std::max(ans,curr);
        }
    }

    // And at last we will return our answer
    return ans;
}

}
} // namespace name



/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    
    std::vector<std::vector<int> > arr2 = {{3,2,1},{4,5,6}};
    /* Test Case 1:-
            3 2 1
            4 5 6

    * the Longest Increasing Path is :- arr2[0][2]->arr2[0][1]->arr2[0][0]->arr[1][0]->arr[1][1]->arr[1][2];
    * i.e :- 1->2->3->4->5->6
    
    * So The Length of Longest Increasing Path is :6 */
    int expected_answer = 6;
    int output = dynamic_programming::longest_increasing_path_in_a_matrix::longestIncreasingPath(arr2);
    assert(output == expected_answer); // this ensures that the algorithm works as expected
    std::cout<<"The Length of Longest Increasing Path is: "<<expected_answer<<std::endl;
}


/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int  main(int  argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
