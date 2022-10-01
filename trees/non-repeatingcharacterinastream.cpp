#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
	public:
	// static int may[26];
    int may[26] = { 0 };
	string ans="";
		string FirstNonRepeating(string A){
		    for(int i=0;i<A.length();i++)
		    {
		        int a=int(A[i])-97;
		        if(may[a]!=0)
		        {
		            ans.append("#");
		        }
		        else
		        {
		            may[a]=may[a]+1;
		            ans.append(A,i,i+1);
		        }
		    }
		    return ans;
		}
};

// { Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		string A;
		cin >> A;
		Solution obj;
		string ans = obj.FirstNonRepeating(A);
		cout << ans << "\n";
	}
	return 0;
}  // } Driver Code Ends