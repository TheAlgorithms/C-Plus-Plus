/*
Partition problem is to determine whether a given set can be partitioned 
into two subsets such that the sum of elements in both subsets is the same. 

Examples: 

arr[] = {1, 5, 11, 5}
Output: Equal Patrition Done!!
The array can be partitioned as {1, 5, 5} and {11}

arr[] = {1, 5, 3}
Output:Can't Patrition
The array cannot be partitioned into equal sum sets.


*/


#include <bits/stdc++.h>
using namespace std;

int dp[10001][10001];

int subset(vector<int> v,int s,int n){
   for(int i=0;i<=n;i++){
        for(int j=0;j<=s;j++){
              if(i==0){
                dp[i][j]=0;
            }
            if(j==0){
                dp[i][j]=1;
            }
        }}
    for(int i=1;i<=n;i++){
        for(int j=1;j<=s;j++){
           if(v[i-1]<=j){
                dp[i][j]=(dp[i-1][j-v[i-1]] || dp[i-1][j]);
                
            }else{
                dp[i][j]=dp[i-1][j];
                  
            }
        }
    }
    
    return dp[n][s];
    
}

int main() {
    int n;
    cin>>n;
	vector<int> v;
	for(int i=0;i<n;i++){
	    int num;
	    cin>>num;
	    v.push_back(num);
	 }
	 int sum=0;
	 for(int i=0;i<n;i++){
	     sum+=v[i];
	 }
	if(sum%2!=0){
	    cout<<"Can't Patrition";
	}else{
	    if(subset(v,sum/2,n)){
	        cout<<"Equal Patrition Done!!";
	    }else{
	        cout<<"Can't Patrition";
	    }
	}
	return 0;
}
