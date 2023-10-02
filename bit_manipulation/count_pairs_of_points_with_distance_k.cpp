#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int countPairs(vector<vector<int>>& c, int k) {
        int n = c.size();
        int cx, cy, minx, maxx;
        int res = 0;
        map<pair<int, int>, int> mp;

        // Count occurrences of points in the map
        for(auto p : c) {
            mp[{p[0], p[1]}]++;
        }

        // Iterate through the points and find pairs satisfying the condition
        for(int i = 0; i < n; i++) {
            cx = c[i][0];
            cy = c[i][1];
            mp[{cx, cy}]--; // Remove the current point from the map
            for(int i = 0; i <= k; i++) {
                int x = cx ^ i;
                int y = (k - i) ^ cy;
                if(mp.find({x, y}) != mp.end()) {
                    res += mp[{x, y}];
                }
            }
        }
        return res;
    }
};

int main() {
    // User input for vector of points
    cout << "Enter the number of points: ";
    int n;
    cin >> n;
    vector<vector<int>> points;
    cout << "Enter points (x y):" << endl;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
    }

    // User input for k
    int k;
    cout << "Enter value of k: ";
    cin >> k;

    // Calculate and output the result
    Solution solution;
    int result = solution.countPairs(points, k);
    cout << "Number of pairs satisfying the condition: " << result << endl;
    return 0;
}
