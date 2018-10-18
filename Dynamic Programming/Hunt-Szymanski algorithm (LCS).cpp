#include<iostream>
#include<vector>
#include<algorithm>

size_t lcs_hunt_szymanski(const std::string & s, const std::string & t){
    std::vector<std::vector<int> > positions(128);
    
    for(size_t i = 0; i != s.size(); i++)
        positions[s[i]].push_back(i);
    for(auto v : positions)
        std::reverse(v.begin(), v.end());
    
    std::vector<int> dp;
    
    for(auto c : t)
        for(auto pos : positions[c]){
            auto it = std::lower_bound(dp.begin(), dp.end(), pos);
            if(dp.end() == it)
                dp.push_back(pos);
            else
                *it = pos; 
        }

    return dp.size();
}

int main(){
    std::string s = "abacabadabacaba";
    std::string t = "badabaAabAcCbadabaDbaca";

    std::cout << lcs_hunt_szymanski(s, t);

    return 0;
}