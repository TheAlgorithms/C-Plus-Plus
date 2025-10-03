#include <algorithm>
#include <iostream>
#include <vector>

void dutchNationalFlag(std::vector<int> &arr) {
    int low = 0, mid = 0, high = arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0)  // if arr[mid] is 0 it needs to be placed in the
                            // beginning so swap it with low position
            swap(arr[low++], arr[mid++]);
        else if (arr[mid] ==
                 1)  // if arr[mid] is 1 it needs to be placed in the middle ,so
                     // just increase the value of mid
            mid++;
        else
            swap(arr[mid],
                 arr[high--]);  // if arr[mid] is 2 it needs to be placed in the
                                // beginning so swap it with high position
    }
}

int main() {
    vector<int> arr = {2, 0, 1, 2, 1, 0, 1, 2};
    dutchNationalFlag(arr);

    for (int x : arr) cout << x << " ";
    cout << "\n";
}
// a dry run to explain the code:
// arr = {2, 0, 1, 2, 1, 0, 1, 2} We have three pointers :

//     low → start of 0’s segment

//         mid → current element

//             high → end of 2’s segment

//                 Initially :

//     ini Copy code low = 0,
//                   mid = 0,
//                   high = 7 arr = [ 2, 0, 1, 2, 1, 0, 1, 2 ] Step 1
//     : arr[mid] = 2

//                  Swap arr[mid] and
//                  arr[high] → swap 2 with 2(no change)

//                      Decrement high = 6

//       ini Copy code arr = [ 2, 0, 1, 2, 1, 0, 1, 2 ] low = 0,
//                   mid = 0,
//                   high = 6 Step 2 : arr[mid] = 2

//                                                Swap arr[mid] and
//                                                arr[high] → swap 2 with 1

//                                                Decrement high = 5

//                                     ini Copy code arr =
//                                         [ 1, 0, 1, 2, 1, 0, 2, 2 ] low = 0,
//                   mid = 0,
//                   high = 5 Step 3 : arr[mid] = 1

//                                     Do nothing,
//                   just increment mid = 1

//                   ini Copy code arr = [ 1, 0, 1, 2, 1, 0, 2, 2 ] low = 0,
//                   mid = 1,
//                   high = 5 Step 4 : arr[mid] = 0

//                                                Swap arr[low] and
//                                                arr[mid] → swap 1 and 0

//                                                Increment low = 1,
//                   mid = 2

//                   ini Copy code arr = [ 0, 1, 1, 2, 1, 0, 2, 2 ] low = 1,
//                   mid = 2,
//                   high = 5 Step 5 : arr[mid] = 1

//                                     Increment mid = 3

//                                     ini Copy code arr =
//                                         [ 0, 1, 1, 2, 1, 0, 2, 2 ] low = 1,
//                   mid = 3,
//                   high = 5 Step 6 : arr[mid] = 2

//                                                Swap arr[mid] and
//                                                arr[high] → swap 2 and 0

//                                                Decrement high = 4

//                                     ini Copy code arr =
//                                         [ 0, 1, 1, 0, 1, 2, 2, 2 ] low = 1,
//                   mid = 3,
//                   high = 4 Step 7 : arr[mid] = 0

//                                                Swap arr[low] and
//                                                arr[mid] → swap 1 and 0

//                                                Increment low = 2,
//                   mid = 4

//                   ini Copy code arr = [ 0, 0, 1, 1, 1, 2, 2, 2 ] low = 2,
//                   mid = 4,
//                   high = 4 Step 8 : arr[mid] = 1

//                                     Increment mid = 5 → now mid > high,
//                   done !

//  Final sorted array :

//     csharp Copy code[0, 0, 1, 1, 1, 2, 2, 2]