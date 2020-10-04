#include<bits/stdc++.h>
using namespace std;
string LexicographicalMaxString(string str) 
{ 
    // loop to find the max leicographic 
    // substring in the substring array 
    string mx = ""; 
    for (int i = 0; i < str.length(); ++i) 
        mx = max(mx, str.substr(i)); 
  
    return mx; 
} 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    ll n;    //length of string
    cin>>n;
    string s;
    cin>>s;
    cout<<LexicographicalMaxString(s); 
	
}
