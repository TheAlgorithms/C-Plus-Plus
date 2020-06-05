#include <iostream>
using namespace std;

void GnomeSort(int arr[], int size) {
    // few easy cases
    if (size <= 1) return;

    int index = 0;  // initialize some variables.
    while (index < size) {
        // check for swap
        if ((index == 0) || (arr[index] >= arr[index - 1])) {
            index++;
        } else {
            swap(arr[index], arr[index - 1]);  // swap
            index--;
        }
    }
}
// Our main function
int main() {
    int arr[] = {-2, -10, 100, 35, 34, 99};
    int size = sizeof(arr) / sizeof(arr[0]);

    GnomeSort(arr, size);

    for (int i = 0; i < size; i++) printf("%d ", arr[i]);

    return 0;
}
