/*
Harry Potter has n mixtures in front of him, arranged in a row. Each mixture has one of 100 different colors (colors have numbers from 0 to 99).
He wants to mix all these mixtures together. At each step, he is going to take two mixtures that stand next to each other and mix them together, and put the resulting mixture in their place.
When mixing two mixtures of colors a and b, the resulting mixture will have the color (a+b) mod 100.
Also, there will be some smoke in the process. The amount of smoke generated when mixing two mixtures of colors a and b is a*b.
Find out what is the minimum amount of smoke that Harry can get when mixing all the mixtures together.

Input
There will be a number of test cases in the input.

The first line of each test case will contain n, the number of mixtures, 1 <= n <= 100.

The second line will contain n integers between 0 and 99 - the initial colors of the mixtures.

Output
For each test case, output the minimum amount of smoke.

Example
Input:
2
18 19
3
40 60 20

Output:
342
2400
In the second test case, there are two possibilities:

first mix 40 and 60 (smoke: 2400), getting 0, then mix 0 and 20 (smoke: 0); total amount of smoke is 2400
first mix 60 and 20 (smoke: 1200), getting 80, then mix 40 and 80 (smoke: 3200); total amount of smoke is 4400
The first scenario is a much better way to proceed.
*/


#include<iostream>
#include<climits>
using namespace std;

int a[1000];
int dp[1000][1000];

int sum(int s, int e){
    int ans =0;
    for(int i=s; i<=e; i++){
        ans += a[i];
        ans %= 100;
    }
    return ans;
}

int solveMixture(int i, int j){
    //base case
    if(i>=j){
        return 0;
    }

    //lookup
    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    dp[i][j] = INT_MAX;
    for(int k=i; k<=j; k++){
        dp[i][j] = min(dp[i][j], solveMixture(i,k) + solveMixture(k+1,j) + sum(i,k)*sum(k+1,j));
    }

    return dp[i][j];
}

int main(){

    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;

        for(int i=0; i<n; i++){
            cin>>a[i];
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                dp[i][j] = -1;
            }
        }

        cout<<solveMixture(0,n-1)<<endl;
        
    }

    //Test cases and outputs
    /*  2
        2
        18 19
        342
        3
        40 60 20
        2400     */  

    return 0;
}
