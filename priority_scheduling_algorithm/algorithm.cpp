#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int process_id;
    int priority;
    int arrival_time;
    int burst_time;
    int remaining_time; // For preemptive scheduling
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void calculate_non_preemptive_priority(std::vector<Process>& processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
        // Find the process with the highest priority that has arrived
        int idx = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            current_time += processes[idx].burst_time;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        }
        else {
            current_time++;
        }
    }
}

void calculate_preemptive_priority(std::vector<Process>& processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
        // Find the process with the highest priority that has arrived and still has burst time left
        int idx = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].remaining_time--;
            current_time++;

            // If the process is completed
            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                completed++;
            }
        }
        else {
            current_time++;
        }
    }
}

void print_process_table(const std::vector<Process>& processes) {
    std::cout << "\nProcess ID\tPriority\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& process : processes) {
        std::cout << process.process_id << "\t\t" << process.priority << "\t\t"
            << process.arrival_time << "\t\t" << process.burst_time << "\t\t"
            << process.completion_time << "\t\t" << process.turnaround_time << "\t\t"
            << process.waiting_time << "\n";
    }
}


int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter the arrival time, burst time, and priority for process " << i + 1 << ": ";
        processes[i].process_id = i + 1;
        std::cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time for preemptive scheduling
        processes[i].completion_time = 0; // Indicates the process is not yet completed
    }

    int choice;
    std::cout << "Choose scheduling type (1: Non-Preemptive, 2: Preemptive): ";
    std::cin >> choice;

    if (choice == 1) {
        calculate_non_preemptive_priority(processes);
    }
    else if (choice == 2) {
        calculate_preemptive_priority(processes);
    }
    else {
        std::cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    print_process_table(processes);

    return 0;
}
