/**
 * @file
 * @brief Stable Marriage Problem implementation
 * @details
 * This implementation utilizes the Gale-Shapley algorithm to find stable matches
 * between men and women based on their preferences.
 *
 * **Stable Marriage Problem** aims to find a stable matching between two equally sized 
 * sets of elements given an ordinal preference for each element. The algorithm was
 * introduced by David Gale and Lloyd Shapley in 1962.
 *
 * @author [B Karthik](https://github.com/BKarthik7)
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

void stableMatch(const vector<vector<int>>& women_prefs, const vector<vector<int>>& men_prefs, int n) {
    vector<int> engagements(n, -1);
    vector<bool> free_men(n, true);
    vector<int> next_proposal(n, 0); // Tracks the next woman to propose for each man

    while (true) {
        int freeMan;
        for (freeMan = 0; freeMan < n; freeMan++) {
            if (free_men[freeMan]) break;
        }
        if (freeMan == n) break;

        int womanToPropose = men_prefs[freeMan][next_proposal[freeMan]];
        next_proposal[freeMan]++;
        int currentFiance = engagements[womanToPropose];

        if (currentFiance == -1) {
            engagements[womanToPropose] = freeMan;
            free_men[freeMan] = false;
        } else {
            if (find(women_prefs[womanToPropose].begin(), women_prefs[womanToPropose].end(), freeMan) <
                find(women_prefs[womanToPropose].begin(), women_prefs[womanToPropose].end(), currentFiance)) {
                engagements[womanToPropose] = freeMan;
                free_men[freeMan] = false;
                free_men[currentFiance] = true;
            }
        }
    }

    cout << "Stable Matches:\n";
    for (int woman = 0; woman < n; woman++) {
        cout << "Woman " << woman << " is engaged to Man " << engagements[woman] << endl;
    }
}

void runTestCase(int caseNum) {
    const int n = 4; // Number of men and women

    // Test Case 1
    if (caseNum == 1) {
        cout << "Test Case 1:\n";
        vector<vector<int>> women_prefs = {
            {1, 0, 3, 2}, // Alice
            {0, 1, 2, 3}, // Becky
            {1, 2, 0, 3}, // Cathy
            {3, 2, 1, 0}  // Diana
        };
        vector<vector<int>> men_prefs = {
            {0, 1, 2, 3}, // Bob
            {1, 0, 3, 2}, // Charlie
            {0, 2, 3, 1}, // David
            {2, 1, 0, 3}  // Edward
        };
        stableMatch(women_prefs, men_prefs, n);
    }
    
    // Test Case 2
    else if (caseNum == 2) {
        cout << "Test Case 2:\n";
        vector<vector<int>> women_prefs = {
            {0, 1, 2, 3}, // Eve
            {1, 0, 3, 2}, // Grace
            {2, 1, 0, 3}, // Hannah
            {3, 2, 1, 0}  // Ivy
        };
        vector<vector<int>> men_prefs = {
            {1, 0, 3, 2}, // Frank
            {0, 1, 2, 3}, // George
            {1, 2, 0, 3}, // Henry
            {2, 0, 1, 3}  // Ian
        };
        stableMatch(women_prefs, men_prefs, n);
    }

    // Test Case 3
    else if (caseNum == 3) {
        cout << "Test Case 3:\n";
        vector<vector<int>> women_prefs = {
            {2, 1, 0, 3}, // Jade
            {0, 2, 3, 1}, // Lucy
            {3, 2, 1, 0}, // Mia
            {1, 3, 0, 2}  // Nina
        };
        vector<vector<int>> men_prefs = {
            {1, 0, 2, 3}, // Kyle
            {0, 2, 3, 1}, // Liam
            {2, 1, 3, 0}, // Mason
            {3, 2, 1, 0}  // Nathan
        };
        stableMatch(women_prefs, men_prefs, n);
    }
}

int main() {
    for (int i = 1; i <= 3; i++) {
        runTestCase(i);
        cout << endl;
    }
    return 0;
}
