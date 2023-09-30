#include<bits/stdc++.h>
using namespace std;
//Not optimised 
unordered_map<string,bool>m;
int solve(string s,int k){
    string key=s+","+to_string(k);
    if(m.find(key)!=m.end()){
        return m[key];
    }
    if(k==1){
        bool c=true;
        for(int i=0;i<s.length()/2;i++){
            if(s[i]!=s[s.length()-i-1]) c=false;
        }
        return m[key]=c;
    }
    int ans=false;
    for(int i=1;i<k;i++){
        for(int j=1;j<=s.length()-(k-i);j++){
            if(j>=i){
                int left=solve(s.substr(0,j),i);
                int right=solve(s.substr(j),k-i);
                ans=max(ans,left & right);
            }
            else{
                break;
            }
        }
    }
    return m[key]=ans;
}
bool gsoc(string s){
    return solve(s,3);
}
int t[2001][2001];
bool isPalindrome(string &s,int i, int j){
    if(i>=j) return 1;
    if(t[i][j]!=-1) return t[i][j];
    if (s[i] == s[j]) return t[i][j] = isPalindrome(s, i + 1, j - 1);
		return t[i][j] = 0;
}
bool checkPartitioning(string s) {
    memset(t,-1,sizeof(t));
    int n=s.size();
    if(n==3) return true;
    for(int i=0;i<n;i++){
		for(int j=i+1;j<n-1;j++){
			if(isPalindrome(s,0,i) && isPalindrome(s,i+1,j) && isPalindrome(s,j+1,n-1))
				return true;
			}
		}
    return false;
}
int main(){
    string s;
    cin>>s;
    cout<<gsoc(s)<<endl;
    cout<<checkPartitioning(s)<<endl;
    return 0;
}