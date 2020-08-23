/*  Implementing Gale–Shapley algorithm to solve the stable marriage problem in C++.

The Stable Marriage Problem states that given N men and N women, 
where each person has ranked all members of the opposite sex in order of preference, 
marry the men and women together such that there are no two people of opposite sex,
who would both rather have each other than their current partners. 
If there are no such people, all the marriages are said to be “stable”

 Following is Gale–Shapley algorithm to find a stable matching:
 The idea is to iterate through all free men while there is any free man available. 
 Every free man goes to all women in his preference list according to the order. 
 For every woman he goes to, he checks if the woman is free, if yes, they both become engaged. 
 If the woman is not free, then the woman chooses either says no to him or dumps her current engagement 
 according to her preference list. So an engagement done once can be broken if a woman gets better option. 
 Time Complexity of Gale-Shapley Algorithm is O(n^2).
 
 Gale-Shapley Algorithm :
 
Initialize all men and women to free
while there exist a free man m who still has a woman w to propose to 
{
    w = m's highest ranked such woman to whom he has not yet proposed
    if w is free
       (m, w) become engaged
    else some pair (m', w) already exists
       if w prefers m to m'
          (m, w) become engaged
           m' becomes free
       else
          (m', w) remain engaged    
}

                                                                        */
                                                                        

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;
 
const char *men_data[][11] = {
    { "abe",  "abi","eve","cath","ivy","jan","dee","fay","bea","hope","gay" },
    { "bob",  "cath","hope","abi","dee","eve","fay","bea","jan","ivy","gay" },
    { "col",  "hope","eve","abi","dee","bea","fay","ivy","gay","cath","jan" },
    { "dan",  "ivy","fay","dee","gay","hope","eve","jan","bea","cath","abi" },
    { "ed",   "jan","dee","bea","cath","fay","eve","abi","ivy","hope","gay" },
    { "fred", "bea","abi","dee","gay","eve","ivy","cath","jan","hope","fay" },
    { "gav",  "gay","eve","ivy","bea","cath","abi","dee","hope","jan","fay" },
    { "hal",  "abi","eve","hope","fay","ivy","cath","jan","bea","gay","dee" },
    { "ian",  "hope","cath","dee","gay","bea","abi","fay","ivy","jan","eve" },
    { "jon",  "abi","fay","jan","gay","eve","bea","dee","cath","ivy","hope" }
};
 
const char *women_data[][11] = {
    { "abi",  "bob","fred","jon","gav","ian","abe","dan","ed","col","hal" },
    { "bea",  "bob","abe","col","fred","gav","dan","ian","ed","jon","hal" },
    { "cath", "fred","bob","ed","gav","hal","col","ian","abe","dan","jon" },
    { "dee",  "fred","jon","col","abe","ian","hal","gav","dan","bob","ed" },
    { "eve",  "jon","hal","fred","dan","abe","gav","col","ed","ian","bob" },
    { "fay",  "bob","abe","ed","ian","jon","dan","fred","gav","col","hal" },
    { "gay",  "jon","gav","hal","fred","bob","abe","col","ed","dan","ian" },
    { "hope", "gav","jon","bob","abe","ian","dan","hal","ed","col","fred" },
    { "ivy",  "ian","col","hal","gav","fred","bob","abe","ed","jon","dan" },
    { "jan",  "ed","hal","gav","abe","bob","jon","col","ian","fred","dan" }
};
 
typedef vector<string> PrefList;
typedef map<string, PrefList> PrefMap;
typedef map<string, string> Couples;
 
// Does 'first' appear before 'second' in preference list?
bool prefers(const PrefList &prefer, const string &first, const string &second)
{
    for (PrefList::const_iterator it = prefer.begin(); it != prefer.end(); ++it)
    {
        if (*it == first) return true;
        if (*it == second) return false;
    }
    return false; // no preference
}
 
void check_stability(const Couples &engaged, const PrefMap &men_pref, const PrefMap &women_pref)
{
    cout << "Stablility:\n";
    bool stable = true;
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        const string &bride = it->first;
        const string &groom = it->second;
        const PrefList &preflist = men_pref.at(groom);
 
        for (PrefList::const_iterator it = preflist.begin(); it != preflist.end(); ++it)
        {
            if (*it == bride) // he prefers his bride
                break;
            if (prefers(preflist, *it, bride) && // he prefers another woman
                prefers(women_pref.at(*it), groom, engaged.at(*it))) // other woman prefers him
            {
                cout << "\t" << *it <<
                    " prefers " << groom <<
                    " over " << engaged.at(*it) <<
                    " and " << groom <<
                    " prefers " << *it <<
                    " over " << bride << "\n";
                stable = false;
            }
        }
    }
    if (stable) cout << "\t(all marriages stable)\n";
}
 
int main()
{
    PrefMap men_pref, women_pref;
    queue<string> bachelors;
 
    // init data structures
    for (int i = 0; i < 10; ++i) // person
    {
        for (int j = 1; j < 11; ++j) // preference
        {
              men_pref[  men_data[i][0]].push_back(  men_data[i][j]);
            women_pref[women_data[i][0]].push_back(women_data[i][j]);
        }
        bachelors.push(men_data[i][0]);
    }
 
    Couples engaged; // <woman,man>
 
    cout << "Matchmaking:\n";
    while (!bachelors.empty())
    {
        const string &suitor = bachelors.front();
        const PrefList &preflist = men_pref[suitor];
 
        for (PrefList::const_iterator it = preflist.begin(); it != preflist.end(); ++it)
        {
            const string &bride = *it;
 
            if (engaged.find(bride) == engaged.end()) // she's available
            {
                cout << "\t" << bride << " and " << suitor << "\n";
                engaged[bride] = suitor; // hook up
                break;
            }
 
            const string &groom = engaged[bride];
 
            if (prefers(women_pref[bride], suitor, groom))
            {
                cout << "\t" << bride << " dumped " << groom << " for " << suitor << "\n";
                bachelors.push(groom); // dump that zero
                engaged[bride] = suitor; // get a hero
                break;
            }
        }
        bachelors.pop(); // pop at the end to not invalidate suitor reference
    }
 
    cout << "Engagements:\n";
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        cout << "\t" << it->first << " and " << it->second << "\n";
    }
 
    check_stability(engaged, men_pref, women_pref);
 
    cout << "Perturb:\n";
    std::swap(engaged["abi"], engaged["bea"]);
    cout << "\tengage abi with " << engaged["abi"] << " and bea with " << engaged["bea"] << "\n";
 
    check_stability(engaged, men_pref, women_pref);
    
    return 0;
}