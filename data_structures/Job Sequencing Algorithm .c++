#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Structure to represent a job
struct Job {
    int id;       // Job ID
    int deadline; // Job deadline
    int profit;   // Profit if job is done before or on deadline
};

// Comparator function to sort jobs by profit in descending order
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Function to find the maximum profit sequence of jobs
void jobSequencing(vector<Job> &jobs, int n) {
    // Sort jobs in decreasing order of profit
    sort(jobs.begin(), jobs.end(), compare);

    // Array to keep track of free time slots
    vector<int> result(n, -1); // Initially all slots are free
    vector<bool> slot(n, false); // Boolean array to check if slot is occupied

    int maxProfit = 0;  // Variable to store the total profit
    int jobCount = 0;   // Variable to count the number of jobs done

    // Iterate through all jobs
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job, starting from its deadline
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (slot[j] == false) { // Free slot found
                result[j] = i;       // Assign job to this slot
                slot[j] = true;      // Mark this slot as occupied
                maxProfit += jobs[i].profit; // Add profit of this job
                jobCount++;
                break;
            }
        }
    }

    // Display the result
    cout << "Number of jobs done: " << jobCount << endl;
    cout << "Total Profit: " << maxProfit << endl;
    cout << "Jobs sequence for maximum profit: ";
    for (int i = 0; i < n; i++) {
        if (result[i] != -1) {
            cout << "Job" << jobs[result[i]].id << " ";
        }
    }
    cout << endl;
}

// Main function
int main() {
    vector<Job> jobs = {
        {1, 2, 100}, {2, 1, 19}, {3, 2, 27}, {4, 1, 25}, {5, 3, 15}
    };
    int n = jobs.size();

    jobSequencing(jobs, n);

    return 0;
}
