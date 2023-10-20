#include <iostream>
#include <vector>

using namespace std;

void printSubsets(vector<int>& nums, vector<int>& subset, int index) {
    // Print the current subset
    for (int i = 0; i < subset.size(); i++) {
        cout << subset[i] << " ";
    }
    cout << endl;

    // Generate all subsets by including the current element in the subset
    for (int i = index; i < nums.size(); i++) {
        // Include the current element
        subset.push_back(nums[i]);

        // Recursively generate subsets starting from the next index
        printSubsets(nums, subset, i + 1);

        // Exclude the current element to backtrack and generate other subsets
        subset.pop_back();
    }
}

void printAllSubsets(vector<int>& nums) {
    vector<int> subset;
    int index = 0;
    printSubsets(nums, subset, index);
}

int main() {
    vector<int> nums = {1, 2, 3};

    cout << "Subsets of the array: " << endl;
    printAllSubsets(nums);

    return 0;
}
