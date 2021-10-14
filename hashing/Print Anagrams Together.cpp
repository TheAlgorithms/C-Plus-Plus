#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
vector<vector<string> > Anagrams(vector<string>& string_list) ;

vector<vector<string> > Anagrams(vector<string>& str) 
{
    // Your Code Here
    int n = str.size();
    
    unordered_map<string, vector<string>>m;
    
    for(int i=0; i<n; i++){
        string temp = str[i];
        sort(str[i].begin(), str[i].end());
        
        m[str[i]].push_back(temp);
        
    }
    vector<vector<string>> ans;
    for(auto itr: m){
        ans.push_back(itr.second);
    }
    return ans;
}


int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<string> string_list(n);
        for (int i = 0; i < n; ++i)
            cin>>string_list[i]; 
        vector<vector<string> > result = Anagrams(string_list);
        sort(result.begin(),result.end());
        for (int i = 0; i < result.size(); i++)
        {
            for(int j=0; j < result[i].size(); j++)
            {
                cout<<result[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    return 0;
}
