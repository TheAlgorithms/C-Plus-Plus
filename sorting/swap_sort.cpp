#include <algorithm>  // for sort()
#include <iostream>
#include <vector>

/**
 * @brief Function to find the minimum number of swaps required to sort an array
 * @param arr reference to the vector of integers
 * @return minimum number of swaps needed
 */
int minSwaps(std::vector<int> &arr) {
    int n = arr.size();

    // Step 1: Create a vector of pairs.
    // Each pair contains the value and its original index.
    std::vector<std::pair<int, int>> pos(n);
    for (int i = 0; i < n; i++) {
        pos[i] = {arr[i], i};
    }

    // Step 2: Sort the vector based on the values.
    // This gives us the target position of each element.
    std::sort(pos.begin(), pos.end());

    // Step 3: Track which elements have been visited.
    std::vector<bool> visited(n, false);
    int swaps = 0;

    // Step 4: Traverse elements and count swaps using cycle detection.
    for (int i = 0; i < n; i++) {
        // If already visited or already in correct place, skip it.
        if (visited[i] || pos[i].second == i) {
            continue;
        }

        // Compute the size of the cycle.
        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = pos[j].second;  // Move to the next index in the cycle.
            cycle_size++;
        }

        // If there is a cycle of size > 1, we need (cycle_size - 1) swaps.
        if (cycle_size > 1) {
            swaps += (cycle_size - 1);
        }
    }

    return swaps;
}

int main() {
    // Example input array
    std::vector<int> arr = {6, 7, 8, 1, 2, 3, 9, 12};

    // Print the result
    std::cout << "Minimum number of swaps required to sort the array: "
              << minSwaps(arr) << std::endl;

    return 0;
}
