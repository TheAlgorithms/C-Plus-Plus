#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
#define ll long long

// This function is used to find longest palindromic subsequence.
//It finds longest common subsequence of given string and its reverse , which gives required seq.
void solve(string s1,string s2,ll n,ll m){

	ll dp[n+1][m+1];//to store length of lcs

	for(ll i=0;i<=n;i++){
		for(ll j=0;j<=m;j++){

            // Base Condition
			if(i==0||j==0)
				dp[i][j] = 0;

			else if(s1[i-1] == s2[j-1])
				dp[i][j] = dp[i-1][j-1] + 1;

			else
				dp[i][j] = max(dp[i-1][j],dp[i][j-1]);

		}
	}

    // dp[n][m] contains length of lcs.
	ll length = dp[n][m];

	cout<<"Length of longest palindromic subsequence is : \t"<<length <<"\n";

	// Contains the longest palindromic subsequence
	char lcs[length+1];

	// null character
	lcs[length] = '\0';

	ll index = length-1;//to indicate current index in lcs.
	ll i=n,j=m;

	while(i>0 && j>0){

        // If this condition is satisfied then it is part of palindromic subsequence.
		if(s1[i-1] == s2[j-1]){
			lcs[index--] = s1[i-1];
			i--;
			j--;
		}

		else if(dp[i-1][j]>dp[i][j-1])
			i--;

		else j--;

	}

	cout<<"Longest Palindromic Subsequences is : \t"<<lcs<<endl;
	return;

}

int main(){

	string str1;

	cout<<"Enter String :\n";
	cin>>str1;


	string str2 = str1;
	//Reverse given string and find lcs of both string which is longest palindromic subsequence.
	reverse(str2.begin(),str2.end());

	// Calculate length of both strings.
	ll length_str1 = str1.length();
	ll length_str2 = str2.length();

	cout<<"\n";
	solve(str1,str2,length_str1,length_str2);

}

//Sample test cases
/*
I/P - programming
O/P - Length of longest palindromic subsequence is :  4
      Longest Palindromic Subsequences is :   gmmg

*/
