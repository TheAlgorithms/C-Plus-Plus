#include<iostream>
#include<vector>
using namespace std;

class MissingNumberFinder {
public:
    MissingNumberFinder(const vector<int>& nums) : nums_(nums) {}

    int findMissingNumber() {
        int size = nums_.size();
        int expectedSum = (size + 1) * (size + 2) / 2; // Sum of a sequence from 1 to n+1
        int actualSum = 0;
        for(int i = 0; i < size; i++) {
            actualSum += nums_[i];
        }
        int missingNum = expectedSum - actualSum;
        return missingNum;
    }

private:
    const vector<int>& nums_;
};

int main() {
    vector<int> arr = {1, 2, 4, 5};
    
    // Create an instance of MissingNumberFinder with the array
    MissingNumberFinder finder(arr);

    // Call the findMissingNumber method to find the missing number
    int missing = finder.findMissingNumber();

    // Output the result
    cout << "The missing number is: " << missing << endl;

    return 0;
}
