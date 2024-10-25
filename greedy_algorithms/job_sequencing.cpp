#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// A structure to represent a job
struct Job {
    char id;      // Job Id
    int deadline; // Deadline of job
    int profit;   // Profit if job is done before or on the deadline
};

// Comparison function to sort jobs based on their profit in descending order
bool comparison(Job a, Job b) {
    return (a.profit > b.profit);
}

// Function to schedule jobs and maximize profit
void jobSequencing(Job arr[], int n) {
    // Sort all jobs according to decreasing order of profit
    sort(arr, arr + n, comparison);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        maxDeadline = max(maxDeadline, arr[i].deadline);
    }

    // Create a time slot array to keep track of free time slots
    vector<int> result(maxDeadline, -1); // Initialize all slots as free (-1)
    vector<char> jobSequence(maxDeadline, ' '); // To store job sequence

    int totalProfit = 0;

    // Iterate over all jobs
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (starting from the last possible slot)
        for (int j = arr[i].deadline - 1; j >= 0; j--) {
            // If the slot is free, assign the job to this slot
            if (result[j] == -1) {
                result[j] = i;          // Store the job index in the result array
                jobSequence[j] = arr[i].id; // Store job ID in job sequence
                totalProfit += arr[i].profit; // Add profit of the job
                break;
            }
        }
    }

    // Display the job sequence and total profit
    cout << "Job sequence for maximum profit: ";
    for (int i = 0; i < maxDeadline; i++) {
        if (jobSequence[i] != ' ') {
            cout << jobSequence[i] << " ";
        }
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {
    Job arr[] = { {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15} };
    int n = sizeof(arr) / sizeof(arr[0]);
    jobSequencing(arr, n);
    return 0;
}
