#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ProcessNode {
    int id;
    vector<int> maxDemand;
    vector<int> allocatedResources;
    vector<int> needMatrix;
    ProcessNode* next;
};

// Linked list of processes
ProcessNode* head = nullptr;

// Available resources
vector<int> available;

// Function to initialize the linked list of processes
void initializeLinkedList() {
    // Get the number of processes from the user
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    // Initialize the available resources
    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter the number of available resources of type " << i << ": ";
        cin >> available[i];
    }

    // Iterate over the number of processes and create a process node for each
    // process
    for (int i = 0; i < numProcesses; i++) {
        ProcessNode* newNode = new ProcessNode();
        newNode->id = i;

        // Get the maximum resource demands of the process from the user
        for (int j = 0; j < available.size(); j++) {
            cout << "Enter the maximum resource demand of process " << i
                 << " for type " << j << ": ";
            cin >> newNode->maxDemand[j];
        }

        // Initialize the allocated resources to zero
        for (int j = 0; j < available.size(); j++) {
            newNode->allocatedResources[j] = 0;
        }

        // Calculate the need matrix
        for (int j = 0; j < available.size(); j++) {
            newNode->needMatrix[j] =
                newNode->maxDemand[j] - newNode->allocatedResources[j];
        }

        newNode->next = head;
        head = newNode;
    }
}

// Function to check if the system is in a safe state
bool isSafe() {
    // Work vector
    vector<int> work(available.size());

    // Finish vector
    vector<bool> finish(head->next->id + 1);

    // Initialize
    for (int i = 0; i < work.size(); i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < finish.size(); i++) {
        finish[i] = false;
    }

    // Iterate over all processes
    while (head != nullptr) {
        // Find a process that is not finished and whose needs are less than or
        // equal to the available resources
        if (!finish[head->id] &&
            all_of(head->needMatrix.begin(), head->needMatrix.end(),
                   [&work](int need) { return need <= work[need]; })) {
            // Allocate the resources to the process
            for (int j = 0; j < work.size(); j++) {
                work[j] -= head->allocatedResources[j];
            }

            // Mark the process as finished
            finish[head->id] = true;

            // Remove the process from the linked list
            ProcessNode* temp = head;
            head = head->next;
            delete temp;
        } else {
            // If no process can be allocated resources, the system is in a
            // deadlock
            return false;
        }
    }

    // If all processes are finished, the system is in a safe state
    return all_of(finish.begin(), finish.end(),
                  [](bool finished) { return finished; });
}

// Function to grant a resource request to a process
bool grantRequest(int processId, vector<int> request) {
    // Local variable
    ProcessNode head;

    // Check if the request is within the process's maximum demand
    if (!all_of(request.begin(), request.end(), [processId, &head](int need) {
            return need <= head.maxDemand[need];
        })) {
        return false;
    }

    // Grant the request
    for (int j = 0; j < request.size(); j++) {
        available[j] -= request[j];
        head.allocatedResources[j] -= request[j];
    }

    return true;
}

int main() {
    // Initialize the linked list of processes
    initializeLinkedList();

    // Get the resource request from the user
    int processId;
    vector<int> request;
    cout << "Enter the process ID: ";
    cin >> processId;

    cout << "Enter the resource request: ";
    for (int i = 0; i < available.size(); i++) {
        cin >> request[i];
    }

    // Grant the resource request
    bool success = grantRequest(processId, request);

    // If the request was granted, print a success message
    if (success) {
        cout << "The resource request was granted." << endl;
    } else {
        // If the request was not granted, print a failure message
        cout << "The resource request was denied." << endl;
    }

    return 0;
}
