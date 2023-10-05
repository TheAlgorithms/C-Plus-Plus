#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

const int P = 5;
const int R = 3;

/**
 * BankersAlgorithm class represents the Banker's Algorithm for resource allocation.
 * It checks if a system is in a safe state and computes a safe sequence.
 */
class BankersAlgorithm {
public:
    /**
     * Constructor for BankersAlgorithm class.
     *
     * @param processes An array of process IDs.
     * @param avail An array representing the available resources.
     * @param maxm A 2D array representing the maximum resources for each process.
     * @param allot A 2D array representing the resources currently allocated to each process.
     * @param num_processes The number of processes.
     * @param num_resources The number of resource types.
     */
    BankersAlgorithm(int processes[], int avail[], int maxm[][R], int allot[][R], int num_processes, int num_resources)
        : num_processes_(num_processes), num_resources_(num_resources) {
        
        for (int i = 0; i < num_processes_; i++) {
            processes_.push_back(processes[i]);
        }
        
        for (int i = 0; i < num_resources_; i++) {
            avail_.push_back(avail[i]);
        }
        
        for (int i = 0; i < num_processes_; i++) {
            vector<int> max_row;
            vector<int> allot_row;
            vector<int> need_row;
            
            for (int j = 0; j < num_resources_; j++) {
                max_row.push_back(maxm[i][j]);
                allot_row.push_back(allot[i][j]);
                need_row.push_back(maxm[i][j] - allot[i][j]);
            }
            
            max_.push_back(max_row);
            allot_.push_back(allot_row);
            need_.push_back(need_row);
        }
        
        safe_sequence_.resize(num_processes_);
        work_ = avail_;
    }

    /**
     * Check if the system is in a safe state.
     *
     * @return True if the system is in a safe state, otherwise false.
     */
    bool is_safe() {
        vector<bool> finish(num_processes_, false);
        int count = 0;

        while (count < num_processes_) {
            bool found = false;
            for (int i = 0; i < num_processes_; i++) {
                if (!finish[i]) {
                    bool can_allocate = true;
                    for (int j = 0; j < num_resources_; j++) {
                        if (need_[i][j] > work_[j]) {
                            can_allocate = false;
                            break;
                        }
                    }
                    if (can_allocate) {
                        for (int j = 0; j < num_resources_; j++) {
                            work_[j] += allot_[i][j];
                        }
                        safe_sequence_[count++] = i;
                        finish[i] = true;
                        found = true;
                    }
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }

    /**
     * Print the safe sequence of processes.
     */
    void print_safe_sequence() {
        cout << "System is in a safe state. Safe sequence is: ";
        for (int i = 0; i < num_processes_ - 1; i++) {
            cout << "P" << processes_[safe_sequence_[i]] << " -> ";
        }
        cout << "P" << processes_[safe_sequence_[num_processes_ - 1]] << endl;
    }

private:
    int num_processes_;
    int num_resources_;
    vector<int> processes_;
    vector<int> avail_;
    vector<vector<int>> max_;
    vector<vector<int>> allot_;
    vector<vector<int>> need_;
    vector<int> safe_sequence_;
    vector<int> work_;
};

/**
 * Test the Banker's Algorithm with predefined test cases.
 * This function checks if the algorithm behaves correctly.
 */
void test_algorithm() {
    // Test Case 1
    int processes1[] = {0, 1, 2, 3, 4};
    int avail1[] = {3, 3, 2};
    int maxm1[][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int allot1[][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    BankersAlgorithm banker1(processes1, avail1, maxm1, allot1, 5, 3);
    assert(banker1.is_safe() == true);

    // Test Case 2
    int processes2[] = {0, 1, 2};
    int avail2[] = {1, 2, 2};
    int maxm2[][R] = {{2, 2, 2}, {3, 2, 2}, {2, 2, 2}};
    int allot2[][R] = {{1, 0, 1}, {2, 1, 0}, {1, 2, 2}};

    BankersAlgorithm banker2(processes2, avail2, maxm2, allot2, 3, 3);
    assert(banker2.is_safe() == false);
}

int main() {
    test_algorithm();
    return 0;
}
