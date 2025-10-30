// C++ Program for counting sort
#include <iostream>

using namespace std;

void countSort(string& arr) {
    int n = arr.length();
    string output(n, ' ');  // pre-allocate space

    int count[256] = {0};
    for (int i = 0; i < n; ++i) ++count[(unsigned char)arr[i]];

    for (int i = 1; i < 256; ++i) count[i] += count[i - 1];

    for (int i = 0; i < n; ++i) {
        output[count[(unsigned char)arr[i]] - 1] = arr[i];
        --count[(unsigned char)arr[i]];
    }

    arr = output;
    cout << "Sorted character array is " << arr;
}

int main() {
    string arr;
    cin >> arr;

    countSort(arr);

    return 0;
}
