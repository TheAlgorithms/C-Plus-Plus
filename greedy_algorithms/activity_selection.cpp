/**
Problem Statement:
You are given n activities with their start and finish times. Select the maximum number of activities
that can be performed by a single person, assuming that a person can only work on a single activity at a time.
Solution:
Since the activities are sorted in increasing order of finish time, we chose the activity whose finish time is less than
all other activities and start time is more than the previous activities finish time. We should sort the activities in
increasing order of finish time of activities.
*/
// The assumption here is input activities will be provided in sorted order of finish time of activities.
#include <cassert>   /// for assert
#include <iostream>
#include <vector>

// Prints a maximum set of activities that can be done by a
// single person, one at a time.
std::vector<int> getMaxActivities(std::vector<int> start, std::vector<int> finish, int n)
{
    int i, j;
    std::vector<int> ans;


    // Since we greedily start selecting the activities the first activity is always selected
    i = 0;
    ans.push_back(i);

    // Considering the rest of the activities
    for (j = 1; j < n; j++) {
        // If this activity has start time greater than or
        // equal to the finish time of previously selected
        // activity, then select it
        if (start[j] >= finish[i]) {
            ans.push_back(j);
            i = j;
        }
    }
    return ans;
}

static void tests() {
    std::vector<int> start = {1, 3, 0, 5, 8, 5};
    std::vector<int> finish = {2, 4, 6, 7, 9, 9};

    std::vector<int> ans = getMaxActivities(start, finish, start.size());
    std::vector<int> activities = {0, 1, 6, 4};

    for(int i = 0 ; i < activities.size(); i++){
        uint64_t activityNumber = ans[i];
        assert(activityNumber == activities[i]);
    }
}

// Driver code
int main()
{
    //tests();
    std::vector<int> start = {1, 3, 0, 5, 8, 5};
    std::vector<int> finish = {2, 4, 6, 7, 9, 9};
    // Function call
    std::vector<int> ans = getMaxActivities(start, finish, start.size());
    std::cout << "Following activities are selected" << "\n";
    for(int x: ans) {
        std::cout << x <<", ";
    }
    return 0;
}
