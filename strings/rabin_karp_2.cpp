
/*Given string s.
  Calculate number of
  distinct substring of
  string s
*/

#include <iostream>
#include <string>
#include <set>
#include <vector>


/* A naive approach will be to
   insert all Substrings
   of string s in a set
   and return the size of set
   time complexity:O(n^3)
   space complexity:O(n^3)
*/
int distinctSubstring(std::string const &str)
{
    // Put all distinct substring in a HashSet
    std::set<std::string> result ;

    // List All Substrings
    for (int i = 0; i <= str.length(); i++)
    {
        for (int j = 1; j <= str.length()-i; j++)
        {

            // Add each substring in Set
            result.insert(str.substr(i, j));
        }
    }

    // Return size of the HashSet
    return result.size();
}

/*Using rabin_karp hashing
  approach we Calculate hash
  of different substrings.
  Insert hash of substrings
  instead of substring itself.
  return the size of set.
  Time complexity:O(n^2)
  Space complexity:O(n^2)
*/

int distinctSubstring_rabin_karp_hashing(std::string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    int S = s.size();
    std::set<int>all_hash; //set to store different hash values

    //storing hash values by rabin-karp algorithm
    std::vector<int64_t> p_pow(S);
    p_pow[0] = 1;
    for (int i = 1; i < (int)p_pow.size(); i++)
        p_pow[i] = (p_pow[i-1] * p) % m;

    std::vector<int64_t> h(S + 1, 0);
    for (int i = 0; i < S; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;


    //trversing all possible substrings
    for (int len = 1; len <= S; len++) {
        for(int i=0;i+len<=S;i++)
        {
            int64_t cur_hash = (h[i+len] + m - h[i]) % m; //hash of substring s[i..i+len-1]
            cur_hash=(cur_hash*p_pow[S-i-1])%m;
            if(all_hash.find(cur_hash)==all_hash.end())
            all_hash.insert(cur_hash);
        }
    }

    return all_hash.size();
}
int main()
{
    std::string s="aabcdaa";
    std::cout<<"number of distinct substring: "<<distinctSubstring(s)<<std::endl;
    std::cout<<"number of distinct substring using rabin-karp: "<<distinctSubstring_rabin_karp_hashing(s)<<std::endl;
}
