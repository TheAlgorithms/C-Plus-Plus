#include <iostream>
#include <vector>
#include <queue>

// Define a structure to represent a process
struct Process {
    int id;         // Process ID
    int burst;      // Burst time
    int remaining;  // Remaining burst time

    Process(int id, int burst)
        : id(id), burst(burst), remaining(burst) {}
};

// Round Robin Scheduling algorithm
void roundRobinScheduling(std::vector<Process>& processes, int timeQuantum) {
    // Create a queue to store processes
    std::queue<Process> processQueue;

    int currentTime = 0;
    int completed = 0;

    while (completed < processes.size()) {
        // Add processes to the queue with remaining burst time
        for (Process& process : processes) {
            if (process.remaining > 0 && process.id >= completed) {
                processQueue.push(process);
            }
        }

        if (!processQueue.empty()) {
            Process currentProcess = processQueue.front();
            processQueue.pop();

            // Execute the process for the time quantum or its remaining burst time, whichever is smaller
            int executeTime = std::min(timeQuantum, currentProcess.remaining);
            currentProcess.remaining -= executeTime;
            currentTime += executeTime;

            // Print the process execution
            std::cout << "P" << currentProcess.id << " | ";

            // Check if the process is completed
            if (currentProcess.remaining == 0) {
                completed++;
                std::cout << "Completion time: " << currentTime << std::endl;
            } else {
                // Add the process back to the queue
                processQueue.push(currentProcess);
            }
        } else {
            // If the queue is empty, there's no active process
            currentTime++;
            std::cout << "Idle | ";
        }
    }
}

int main() {
    // Create a vector of processes with their burst times
    std::vector<Process> processes = {
        Process(1, 24),
        Process(2, 3),
        Process(3, 3)
    };

    int timeQuantum = 4;

    // Run the Round Robin Scheduling algorithm
    std::cout << "Gantt Chart:" << std::endl;
    roundRobinScheduling(processes, timeQuantum);

    return 0;
}
