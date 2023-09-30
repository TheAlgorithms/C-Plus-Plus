#include<bits/stdc++.h>
using namespace std;
unordered_map<string,int> m;
int solve(string s,int k){
    string key=s+","+to_string(k);
    if(m.find(key)!=m.end()){
        return m[key];
    }
    if(k==1){
        int c=0;
        for(int i=0;i<s.length()/2;i++){
            if(s[i]!=s[s.length()-i-1]) c++;
        }
        return c;
    }
    int ans=INT_MAX;
    for(int i=1;i<k;i++){
        for(int j=1;j<=s.length()-(k-i);j++){
            if(j>=i){
                int left=solve(s.substr(0,j),i);
                int right=solve(s.substr(j),k-i);
                ans=min(ans,left+right);
            }
            else{
                break;
            }
        }
    }
    return m[key]=ans;
}
int main(){
    string s;
    int k;
    cin>>s;
    cin>>k;
    cout<<solve(s,k);
    return 0;
}