// Perform Binary search on an array
#include <iostream>
using namespace std;
int binary(int start, int endd, int arr[], int no) {
    int midd = (start + endd) / 2;  // Searching the middle element's index
    if (start >= endd) {
        cout << "Element not found!";

        return -1;
    }

    else if ((arr[start] == no) || (arr[endd] == no) ||
             (arr[midd] == no)) {  // if the required number is present at
                                   // start,endd or midd index
        cout << "Element found!";

        return 1;

    } else if (no > arr[midd]) {  // if number to be found is greater than
                                  // middle than apply binary search on the
                                  // right side of arr[midd]  element
        return binary(midd + 1, endd, arr, no);

    } else {  // else apply binary search to the left side of arr[midd]
        return binary(start, midd - 1, arr, no);
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 10, ret;
    ret = binary(0, n, arr, 1);
}