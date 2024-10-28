#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
struct Job {
    int id;        // Job ID
    int deadline;  // Job deadline
    int profit;    // Job profit
};

bool compare(Job a, Job b) { return a.profit > b.profit; }

void jobSequencing(vector<Job> &jobs, int n) {
    sort(jobs.begin(), jobs.end(), compare);
    vector<int> result(n, -1);    // Job sequence
    vector<bool> slot(n, false);  // To track if slot is occupied

    for (int i = 0; i < jobs.size(); i++) {
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!slot[j]) {
                result[j] = jobs[i].id;
                slot[j] = true;
                break;
            }
        }
    }

    // Print the job sequence for maximum profit
    cout << "Job sequence for maximum profit: ";
    for (int i = 0; i < n; i++) {
        if (result[i] != -1) {
            cout << result[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    vector<Job> jobs = {
        {1, 2, 100}, {2, 1, 19}, {3, 2, 27}, {4, 1, 25}, {5, 3, 15}};
    int n = jobs.size();

    jobSequencing(jobs, n);

    return 0;
}
