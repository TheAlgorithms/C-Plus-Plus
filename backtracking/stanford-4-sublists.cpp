#include <iostream>
#include <vector>
#include <string>
using namespace std;

void generateSublistsHelper(vector<string> &strs, vector<vector<string>> &ans, vector<string> &chosen)
{
    if (strs.size() == 0)
    {
        ans.push_back(chosen); // ACCEPT SUBLIST
        return;
    }
    else
    {
        string s = strs[0];
        strs.erase(strs.begin());

        // CHOOSE/EXPLORE (WITHOUT S)
        generateSublistsHelper(strs, ans, chosen);

        // CHOOSE/EXPLORE (WITH S)
        chosen.push_back(s);
        generateSublistsHelper(strs, ans, chosen);

        // UNCHOOSE
        strs.insert(strs.begin(), s);
        chosen.pop_back();
    }
}

void generateSublists(vector<string> strs)
{
    vector<vector<string>> ans;
    vector<string> chosen;
    generateSublistsHelper(strs, ans, chosen);

    // print ans
    for (auto v : ans)
    {
        for (auto s : v)
            cout << s << " ";
        cout << "\n";
    }
}

int main()
{
    vector<string> strs = {"one", "two", "three"};
    generateSublists(strs);
    return 0;
}