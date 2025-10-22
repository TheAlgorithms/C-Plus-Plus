
/*
---------------------------------------------------------
Algorithm: Meet in the Middle — Combinatorial Selection Problem
---------------------------------------------------------
Problem:
You are given `n` items, each with a cost and value.
Find the **maximum total value** you can achieve by selecting
a subset of items whose **total cost ≤ budget**.

Constraints:
- n ≤ 40  → too large for brute-force 2^n
- cost[i], value[i] ≤ 1e9

Optimization:
Use "Meet in the Middle" to reduce complexity from O(2^n)
to O(2^(n/2)) by dividing the items into two halves and combining
their possible subsets efficiently.

---------------------------------------------------------
Example:
Input:
    n = 5, budget = 10
    cost  = [4, 3, 5, 8, 2]
    value = [6, 4, 5, 10, 3]
Output:
    12
Explanation:
    Pick items with total cost = 9 (4 + 3 + 2)
    and total value = 6 + 4 + 3 = 13
    (≤ 10 → maximum achievable)
---------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------
// Helper: Generate all subsets with (cost, value) pairs
// -----------------------------------------------------
void generateSubsets(const vector<pair<int, int>>& items, vector<pair<long long, long long>>& subsets) {
    int n = items.size();
    int total = 1 << n; // 2^n possible subsets

    for (int mask = 0; mask < total; ++mask) {
        long long totalCost = 0, totalValue = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                totalCost += items[i].first;
                totalValue += items[i].second;
            }
        }
        subsets.push_back({totalCost, totalValue});
    }
}

// -----------------------------------------------------
// Function: Compute maximum total value under budget
// -----------------------------------------------------
long long maxValueUnderBudget(vector<pair<int, int>>& items, int budget) {
    int n = items.size();
    int mid = n / 2;

    // Split into two halves
    vector<pair<int, int>> leftItems(items.begin(), items.begin() + mid);
    vector<pair<int, int>> rightItems(items.begin() + mid, items.end());

    // Generate all subset pairs (cost, value)
    vector<pair<long long, long long>> leftSubsets, rightSubsets;
    generateSubsets(leftItems, leftSubsets);
    generateSubsets(rightItems, rightSubsets);

    // Sort right subsets by cost
    sort(rightSubsets.begin(), rightSubsets.end());

    // Optimize rightSubsets: remove dominated pairs
    // (Keep only subsets with strictly increasing values)
    vector<pair<long long, long long>> optimized;
    long long maxValue = 0;
    for (auto [c, v] : rightSubsets) {
        if (v > maxValue) {
            optimized.push_back({c, v});
            maxValue = v;
        }
    }
    rightSubsets = optimized;

    long long answer = 0;

    // For each subset on left, binary search best fit on right
    for (auto [costL, valL] : leftSubsets) {
        if (costL > budget) continue;

        long long remaining = budget - costL;

        // Binary search for the most value we can get within remaining budget
        int idx = upper_bound(rightSubsets.begin(), rightSubsets.end(), make_pair(remaining, LLONG_MAX)) - rightSubsets.begin() - 1;

        if (idx >= 0) {
            long long valR = rightSubsets[idx].second;
            answer = max(answer, valL + valR);
        }
    }

    return answer;
}

// -----------------------------------------------------
// Driver Code (Test)
// -----------------------------------------------------
int main() {
    vector<pair<int, int>> items = {
        {4, 6}, {3, 4}, {5, 5}, {8, 10}, {2, 3}
    };
    int budget = 10;

    cout << "Items (cost, value): ";
    for (auto &it : items) cout << "(" << it.first << "," << it.second << ") ";
    cout << "\nBudget: " << budget << endl;

    long long result = maxValueUnderBudget(items, budget);
    cout << "Maximum achievable value under budget = " << result << endl;

    return 0;
}

/*
---------------------------------------------------------
🧠 Explanation:

We split items into two halves:
Left = [{4,6}, {3,4}] → subsets:
  []: (0,0), [4]: (4,6), [3]: (3,4), [4,3]: (7,10)

Right = [{5,5}, {8,10}, {2,3}] → subsets:
  []:(0,0), [5]:(5,5), [8]:(8,10), [2]:(2,3),
  [5,8]:(13,15), [5,2]:(7,8), [8,2]:(10,13), [5,8,2]:(15,18)

After filtering dominated pairs in right half and combining both halves,
the best achievable total value ≤ budget(10) = 13.
---------------------------------------------------------
*/
