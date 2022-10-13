
// Round Robin is a scheduling algorithm.
// In Round Robin each process is assigned a fixed time slot in a cyclic way.
// https://en.wikipedia.org/wiki/Round-robin_scheduling
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>

/*----------------------------------------------------------------
// Calculate the waiting times of a list of processes that have a
//        specified duration.
//
//        Return: The waiting time for each process.
//        >>> calculate_waiting_times([10, 5, 8])
//        [13, 10, 13]
//        >>> calculate_waiting_times([4, 6, 3, 1])
//        [5, 8, 9, 6]
//        >>> calculate_waiting_times([12, 2, 10])
//        [12, 2, 12]
//--------------------------------------------------------------*/
void calculate_waiting_times(std::vector<int> burst_times,
                                         std::vector<int> &waiting_times) {
    int quantum = 2;
    waiting_times;
    std::vector<int> rem_burst_times = burst_times;
    std::fill(waiting_times.begin(), waiting_times.end(), 0);
    bool done = false;
    int t = 0;
    while (!done) {
        done = true;
        for (int i = 0; i < burst_times.size(); i++) {
            auto burst_time = burst_times[i];
            if (rem_burst_times[i] > 0) {
                done = false;
                if (rem_burst_times[i] > quantum) {
                    t += quantum;
                    rem_burst_times[i] -= quantum;
                }
                else {
                    t += rem_burst_times[i];
                    waiting_times.push_back(t - burst_time);
                    rem_burst_times[i] = 0;
                }
            }
        }
    }
}

/*----------------------------------------------------------------
// calculate_turn_around_times([1, 2, 3, 4], [0, 1, 3])
//      [1, 3, 6]
//      calculate_turn_around_times([10, 3, 7], [10, 6, 11])
//      [20, 9, 18]
//--------------------------------------------------------------*/
void calculate_turn_around_times(std::vector<int> burst_times,
                                             std::vector<int> waiting_times,
                                             std::vector<int> &turn_around_times) {
    //return (burst + waiting for burst, waiting in zip(burst_times, waiting_times));
    for (int i = 0; i < waiting_times.size(); i++) {
        turn_around_times.push_back(burst_times[i] + waiting_times[i]);
    }
    return;
}

int main(int argc, char** argv) {
    std::vector<int> waiting_times, turn_around_times;
    std::vector<int> burst_times = {3, 5, 7};
    calculate_waiting_times(burst_times, waiting_times);
    calculate_turn_around_times(burst_times, waiting_times, turn_around_times);
    std::cout << "Process ID \tBurst Time \tWaiting Time \tTurnaround Time" << std::endl;
    
    for (int i = 0; i < 3; i++) {
        std::cout << "  " << (i + 1) << "\t\t " << burst_times[i] << "\t\t "
                  << waiting_times[i] << "\t\t" << turn_around_times[i]
                  << std::endl;
    }
    std::cout << "\nAverage waiting time = "
              << std::accumulate(waiting_times.begin(), waiting_times.end(),
                                 0.0) /
                     static_cast<double>(waiting_times.size())
              << std::endl;
    std::cout << "Average turn around time = "
              << std::accumulate(turn_around_times.begin(),
                                 turn_around_times.end(), 0.0) /
                     static_cast<double>(turn_around_times.size())
              << std::endl;
};