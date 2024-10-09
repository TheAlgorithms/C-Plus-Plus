/**
 * @file
 * @brief [Job Sequencing Problem]
 * (https://www.geeksforgeeks.org/job-sequencing-problem/)
 * Algorithm explanantion and implementation
 *
 * @details
 * Given an array of jobs where every job has a deadline and associated profit
 * if the job is finished before the deadline.
 * It is also given that every job takes
 * a single unit of time, so the minimum possible deadline for any job is 1.
 * Maximize the total profit if only one job can be scheduled at a time.
 *
 * Examples:
 *
 * @example
 * Input: Four Jobs with following deadlines and profits
 * JobID |  Deadline |  Profit
 * -----------------------------
 * a     |      4    |    20
 * b     |      1    |    10
 * c     |      1    |    40
 * d     |      1    |    30
 *
 * Output: Following is maximum profit sequence of jobs: c, a
 *
 * @example
 *  Input:  Five Jobs with following deadlines and profits
 *  JobID | Deadline | Profit
 * ---------------------------
 *   a    |     2     |  100
 *   b    |     1     |  19
 *   c    |     2     |  27
 *   d    |     1     |  25
 *   e    |     3     |  15
 * Output: Following is maximum profit sequence of jobs: c, a, e
 *
 *
 *
 * Naive Approach:
 * Generate all subsets of a given set of jobs and check individual subsets for
 * the feasibility of jobs in that subset. Keep track of maximum profit among
 * all feasible subsets.
 * The above approach's time complexity is: O(N^2) with auxliary space O(N)
 * N refers to the number of jobs.
 *
 *
 * Greedy Approach:
 * Greedily choose the jobs with maximum profit first, by sorting the jobs in
 * decreasing order of their profit. This would help to maximize the total
 * profit as choosing the job with maximum profit for every time slot will
 * eventually maximize the total profit.
 * The above approaches's time complexity is: O(NlogN) with auxliary space o(N)
 * N refers to the number of jobs.
 *
 *
 * Greedy approach psuedo-code:
  - Sort all jobs in decreasing order of profit.
  - Iterate on jobs in decreasing order of profit.
       - For each job , do the following:
           - Find a time slot i, such that slot is empty and i < deadline and i
             is greatest.
           - Put the job in this slot and mark this slot filled.
           - If no such i exists, then ignore the job.
 *
 * @author [Mahmoud Elkholy](https://github.com/maahmoudezzat)
 */

// Implementation of the greedy algorithm using priority_queue AKA max_heap.
// C++ code for the above approach
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// A structure to represent a job
struct Job {
    char id;     // Job Id
    int dead;    // Deadline of job
    int profit;  // Profit earned if job is completed before deadline
};

// Custom sorting helper struct which is used for sorting
// all jobs according to profit
struct jobProfit {
    bool operator()(Job const& a, Job const& b) {
        return (a.profit < b.profit);
    }
};

// Returns maximum profit from jobs
void printJobScheduling(Job arr[], int n) {
    vector<Job> result;
    sort(arr, arr + n, [](Job a, Job b) { return a.dead < b.dead; });

    // set a custom priority queue
    priority_queue<Job, vector<Job>, jobProfit> pq;

    for (int i = n - 1; i >= 0; i--) {
        int slot_available;

        // we count the slots available between two jobs
        if (i == 0) {
            slot_available = arr[i].dead;
        } else {
            slot_available = arr[i].dead - arr[i - 1].dead;
        }

        // include the profit of job(as priority),
        // deadline and job_id in maxHeap
        pq.push(arr[i]);

        while (slot_available > 0 && pq.size() > 0) {
            // get the job with the most profit
            Job job = pq.top();
            pq.pop();

            // reduce the slots
            slot_available--;

            // add it to the answer
            result.push_back(job);
        }
    }

    // sort the result based on the deadline
    sort(result.begin(), result.end(),
         [&](Job a, Job b) { return a.dead < b.dead; });

    // print the result
    for (int i = 0; i < result.size(); i++) cout << result[i].id << ' ';
    cout << endl;
}

// main function to test the code
int main() {
    Job arr[] = {
        {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};

    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Following is maximum profit sequence of jobs \n";

    // Function call
    printJobScheduling(arr, n);
    return 0;
}
