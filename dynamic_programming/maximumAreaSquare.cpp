/*
PROBLEM : Given an m x n binary matrix filled with 0's and 1's, 
            find the largest square containing only 1's and return its area.
            
            
APPROACH : 1) Construct a sum matrix dp[m][n] for the given matrix[m][n].
                a)  Copy first row and first columns as it is from M[][] to S[][].
                    because matrix having a single row or column can only have  squares of size 1.
                b)  For other entries, use following expressions to construct S[][]
                        If matrix[i][j] is 1 then
                            dp[i][j] = min(matrix[i][j-1], matrix[i-1][j], matrix[i-1][j-1]) + 1
                        Else If M[i][j] is 0
                            dp[i][j] = 0
            2) Find the maximum element in dp[m][n]
            3) Using the value and coordinates of maximum entry in matrix[i], print 
                sub-matrix of M[][]
                
INPUT FORMAT : First line will contain two space seperated integers m and n 
                next m lines contains a binary string of length n. each character of the string can either '0' or '1'.
                
OUTPUT FORMAT : Single integer denoting the maximum area of square submatrix having all 1s inside it.

TIME COMPLEXITY :   O(m*n)
SPACE COMPLEXITY:   O(m*n) 
    
*/


#include <bits/stdc++.h>
using namespace std ;


int maximalSquare(vector<string> &matrix , int m , int n)
{
//  Creating a 2D array dp of m*n
//  dp[i][j] will store the edge length of that  square submatrix whose area will be maximum
//    considering the given to be only matrix[0][0] to matrix[i][j]
	int dp[m][n] ;


//  if cosidering a matrix having only 1 row then only 1 size square can be formed
//  That is why,  dp[0][i]  =  1 if matrix[0][i] is 1 otherwise 0. (0 <= i <= n)
	for (int j = 0 ; j < n ; j++) {
		if (matrix[0][j] == '1') {
			dp[0][j] = 1 ;
		}
		else {
			dp[0][j] =  0 ;
		}
	}

// similary for 1st column
	for (int j = 0 ; j < m ; j++) {
		if (matrix[0][j] == '1') {
			dp[j][0] = 1 ;
		}
		else {
			dp[j][0] =  0 ;
		}
	}



//  Now if matrix[i][j] = 0 , then dp[i][j] = 0
//  because ith row or jth row can,t contribute to required answer.
//  and if matrix[i][j] = 1, then dp[i][j] = min(matrix[i][j-1] , matrix[i -1][j] , matrix[i-1][j-1])
//	becasue we are trying to include ith row and jth column to existing answer
//  taking minimum to make sure the submatrix to be square.
	for (int i = 1 ; i < m ; i++) {
		for (int j = 1 ; j < n ; j++) {
			if (matrix[i][j] == '0') {
				dp[i][j] = 0  ;
			}
			else {
				dp[i][j] = min({dp[i][j - 1] , dp[i - 1][j] , dp[i - 1][j - 1]}) + 1 ;
				// Minimum of three or more  numbers can be found by enclosing the numbers between
				// a curly braces before passing it to min.
			}
		}
	}


//  Initialise edge = -1 and then take ans =  max(ans , dp[i][j])
	int e = -1  ;
	for (int i = 0 ; i < m ; i++) {
		for (int j = 0  ; j < n ; j++) {
			e =  max(e , dp[i][j]) ;
		}
	}

// Now required square matrix have an edge e . Hence area =  e*e ;
    int area = e*e ;
	return area ;

}

//********** Test Cases *****************
void test()
{
    cout<<"Test case 1 \n" ;
	int m = 5 , n = 4  ;
	vector<string> mat(m) ;
	mat[0] = "1101";
	mat[1] = "0111";
	mat[2] = "1111";
	mat[3] = "1111" ;
	mat[4] = "0000";


	int ans =  maximalSquare(mat , m , n) ;

	cout << ans  ;

/* Explaination
    
    DP array generated for this case is 
    1 1 0 1 
    1 2 1 1 
    0 1 2 2 
    1 1 2 3 
    0 0 0 0
    
    maximum element is dp[3][3] =  3  ;
    It means the edge of maximum area square will be 3.
    Hence, its area will be 3*3 =  9 ;
    
    >> Bottom-right vertex of our square will lie at matrix[3][3] and top-left  vertex will lie at matrix[1][1].
    
*/




}




//************** Main function ***********
int main()
{
	int m , n ;

// Input size of binary matrix m = rows , n =  columns
	cin >> m >> n ;

// creating a vector  of string type of size m (Number of rows )
// Here m is passed as an argument to the constructor of vector to create vector of size m
	vector<string> matrix(m) ;

// Input binary matrix :
	for (int i = 0 ; i < m ; i++) {
		cin >> matrix[i] ;
	}

	int ans = maximalSquare(matrix , m ,n) ;
    cout<<ans<<"\n" ;
    
	test() ;
}

//******************************************
/*
Author Name : Vikash Prajapati
Codeforces Handle : vikash_2k19
Codechef Handle   : vikash_2k19
*/
