/**
 * @file
 * @brief A simple program to check large value of a list.
 */

#include <iostream>
using namespace std;

/** function to find min number of given array and array size */
int find_min(int list[], int listSize){

    int minNum = list[0]; // initialize minNum with the first element of the list
    int i;

    // Iterate through the list
    for (i = 1; i < listSize; i++) {
        if (list[i] < minNum) { // check if the current element is less than the current minimum
            minNum = list[i]; // update the minimum number
        }
    }
    return minNum;
}

/** Main function */
int main() {
    int list[] = {5, 10, 15, 20, 25, 30, 4};
    int listSize = sizeof(list) / sizeof(list[0]);  // Size the array

    cout << "The minimum number in the list is: " << find_min(list,listSize) << endl;

    return 0;
}