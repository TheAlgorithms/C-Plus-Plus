/**
 * Combination Sum - Backtracking Problem
 *
 * Given a set of candidate numbers (distinct integers) and a target number,
 * find all unique combinations in candidates where the candidate numbers sum to the target.
 * You may use the same number multiple times.
 *
 * Example:
 * Input: candidates = [2, 3, 6, 7], target = 7
 * Output: [[2,2,3],[7]]
 *
 * ---------------------------------------------
 * Brute Force Approach:
 * Try every possible subset and check if the sum equals the target.
 * Time Complexity: O(2^n * k) where k is average length of subset
 * Space Complexity: O(k * x) where x is number of valid combinations
 *
 * ---------------------------------------------
 * Optimized Approach - Backtracking:
 * Use recursion and backtrack when the current sum exceeds the target.
 * Time Complexity: Better than brute force, but still exponential in worst-case.
 */

#include <iostream>
#include <vector>
using namespace std;

// ------------------- Brute Force Style (for explanation) -------------------
void findAllSubsets(int index, int target, vector<int>& candidates, vector<int>& current, vector<vector<int>>& result) {
    if (index == candidates.size()) {
        if (target == 0) result.push_back(current);
        return;
    }

    // Pick the current element
    if (candidates[index] <= target) {
        current.push_back(candidates[index]);
        findAllSubsets(index, target - candidates[index], candidates, current, result);
        current.pop_back();
    }

    // Do not pick the current element
    findAllSubsets(index + 1, target, candidates, current, result);
}

// ------------------- Optimized Backtracking -------------------
void backtrack(int index, int target, vector<int>& candidates, vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }

    for (int i = index; i < candidates.size(); i++) {
        if (candidates[i] <= target) {
            current.push_back(candidates[i]);
            backtrack(i, target - candidates[i], candidates, current, result); // not i+1 because we can reuse
            current.pop_back(); // backtrack
        }
    }
}

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    vector<vector<int>> bruteForceResult, backtrackingResult;
    vector<int> temp;

    // Brute Force Result
    findAllSubsets(0, target, candidates, temp, bruteForceResult);
    cout << "Brute Force Result:\n";
    for (auto& comb : bruteForceResult) {
        for (int num : comb) cout << num << " ";
        cout << endl;
    }

    // Backtracking Result
    backtrack(0, target, candidates, temp, backtrackingResult);
    cout << "\nOptimized Backtracking Result:\n";
    for (auto& comb : backtrackingResult) {
        for (int num : comb) cout << num << " ";
        cout << endl;
    }

    return 0;
}
