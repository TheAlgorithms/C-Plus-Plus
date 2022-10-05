#include <iostream>
using namespace std;

// Prints a maximum number of activities that can be done by a single
// person, one at a time.
void activitySelector(int start_time[], int finish_time[], int total_num) {
    int i, j;

    cout << "Selected Activities" << endl;

    // Initialising with the first activity
    i = 0;
    cout << " " << i;

    // Consider rest of the activities
    for (j = 1; j < total_num; j++) {
        // If start time of next activity in the list is more than the finish
        // time of previous activity it gets selected
        if (start_time[j] >= finish_time[i]) {
            cout << " " << j;
            i = j;
        }
    }
}

// driver program to test above function
int main() {
    int start_time[] = {1, 3, 5, 7, 9, 9};
    int finish_time[] = {2, 4, 6, 7, 10, 9};
    int total_num = sizeof(start_time) / sizeof(start_time[0]);
    activitySelector(start_time, finish_time, total_num);
    return 0;
}