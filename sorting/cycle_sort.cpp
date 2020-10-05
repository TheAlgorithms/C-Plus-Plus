#include <iostream>

void swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// Function sort the array using Cycle sort
void cycleSort(int arr[], int n) {
    // count number of memory writes
    int writes = 0;

    // traverse array elements and put it to on
    // the right place
    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        // initialize item as starting point
        int item = arr[cycle_start];

        // Find position where we put the item. We basically
        // count all smaller elements on right side of item.
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i] < item)
                pos++;

        // If item is already in correct position
        if (pos == cycle_start)
            continue;

        // ignore all duplicate  elements
        while (item == arr[pos]) pos += 1;

        // put the item to it's right position
        if (pos != cycle_start) {
            swap(&item, &arr[pos]);
            writes++;
        }

        // Rotate rest of the cycle
        while (pos != cycle_start) {
            pos = cycle_start;

            // Find position where we put the element
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    pos += 1;

            // ignore all duplicate  elements
            while (item == arr[pos]) pos += 1;

            // put the item to it's right position
            if (item != arr[pos]) {
                swap(&item, &arr[pos]);
                writes++;
            }
        }
    }
}

int main() {
    // example
    int arr[] = {1, 8, 3, 9, 10, 10, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    cycleSort(arr, n);

    std::cout << "After sort : " << std::endl;
    for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
    return 0;
}