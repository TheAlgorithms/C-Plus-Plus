#include <iostream>
#include <vector>
#include <algorithm>

// Define a structure to represent a process
struct Process {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    double ratio;   // Response ratio

    Process(int id, int arrival, int burst)
        : id(id), arrival(arrival), burst(burst), ratio(0) {}
};

// Function to calculate response ratios for all processes
void calculateResponseRatios(std::vector<Process>& processes, int currentTime) {
    for (auto& process : processes) {
        if (process.arrival <= currentTime) {
            // Calculate response ratio: (waiting time + burst time) / burst time
            process.ratio = (currentTime - process.arrival + process.burst) / static_cast<double>(process.burst);
        } else {
            // For processes that haven't arrived yet, set the ratio to a high value
            process.ratio = 999999.0; // A large number as a placeholder
        }
    }
}

// HRRN Scheduling algorithm
void hrrnScheduling(std::vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    while (true) {
        // Calculate response ratios for all processes at the current time
        calculateResponseRatios(processes, currentTime);

        // Find the process with the highest response ratio
        double highestRatio = -1;
        int selectedProcess = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].ratio > highestRatio) {
                highestRatio = processes[i].ratio;
                selectedProcess = i;
            }
        }

        if (selectedProcess == -1) {
            // No process is available to run, so we'll wait for the next process to arrive
            currentTime++;
        } else {
            // Execute the selected process
            std::cout << "Process " << processes[selectedProcess].id << " is running at time " << currentTime << std::endl;
            currentTime += processes[selectedProcess].burst;

            // Mark the process as completed
            processes[selectedProcess].ratio = -1;

            if (currentTime >= n) {
                // All processes have been completed
                break;
            }
        }
    }
}

int main() {
    // Create a vector of processes with their arrival and burst times
    std::vector<Process> processes = {
        Process(1, 0, 4),
        Process(2, 1, 3),
        Process(3, 2, 5),
        Process(4, 3, 2)
    };

    // Run the HRRN Scheduling algorithm
    hrrnScheduling(processes);

    return 0;
}
