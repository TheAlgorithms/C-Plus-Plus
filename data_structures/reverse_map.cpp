/**
 *   @author asart9O
 *   Simple reversemap data type
 *   the goal is - sort map not by key, but by value.
 */
#include<iostream> /// io
#include<map>
#include<set> /// for multiset
#include<unordered_map>
#include<vector>
#include<unordered_set>
#include<algorithm> // for find_if
#include<cassert>
using std::map;
using std::multiset;
using std::pair;
using std::vector;
template<typename key, typename value> /// declaring reverse map with key and value.
class ReverseMap
{
    private: ///declaring a backbone map
        map<value, multiset<key>> mp;
        vector<pair<key, value>> extract; /// vector to extract to
    public:
        ///inserting into ReverseMap
        void insert(const key& Key, const value& Value)
        {
            ///We insert key into map with value as key. Value gets sorted, multiset with keys stays.
            mp[Value].insert(Key);
        }
        vector<pair<key, value>> to_vector()
        {
            extract.clear(); /// clearing
            for(auto entry : mp)
            {
                value v = entry.first; /// getting value
                for(auto k : entry.second) /// iterating through keys
                {
                    /// locate existing pair in exctract
                    auto it = std::find_if(
                        extract.begin(), extract.end(),
                        [&](auto p) {return p.first == k;}
                    );
                    if(it == extract.end())
                    {
                        ///append
                        extract.emplace_back(k, v);
                    }
                    else
                    {
                        /// update, add v
                        it->second += v;
                    }
                }
            }
            ///sorting by second element
            std::sort(extract.begin(), extract.end(),
            [](auto a, auto b)
            {return a.second < b.second;});
            return extract;
        }
};
void test1()
{
    ReverseMap<int, int> map;
    map.insert(1, 2);
    map.insert(234324234, 1);
    map.insert(20, 3);
    map.insert(2, 2);
    vector<pair<int,int>> expected = {
        {234324234, 1},
        {1, 2},
        {2, 2},
        {20, 3}
    };
    auto result = map.to_vector();
    assert(result == expected);
}
void test2()
{
    ReverseMap<int, int> mapy;
    mapy.insert(-1, 3);
    mapy.insert(5, -20);
    mapy.insert(-1, 2);
    mapy.insert(1, 0);
    vector<pair<int,int>> expected = {
        {5, -20},
        {1, 0},
        {-1, 5}
    };
    auto result = mapy.to_vector();
    assert(result == expected);
}
int main()
{
    ///running tests.
    test1();
    test2();
    return 0;
}
