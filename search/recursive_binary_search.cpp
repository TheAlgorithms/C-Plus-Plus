#include <iostream>
using namespace std;
//This is a recursive approach to binary search which uses recursion
int recursive_binary_search(int a[], int l, int r, int key) {
    int mid = (l + r) / 2;
    if (l == r && key != a[0]) // Base condition (if only 1 element is present in the array)
        return -1;
    if (key == a[mid])
        return mid;
    else if (key < a[mid])
        return recursive_binary_search(a, l, mid - 1, key);
    else
        return recursive_binary_search(a, mid + 1, r, key);
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int key;
    cin >> key;
    int res = recursive_binary_search(a, 0, n - 1, key);
    if (res == -1)
        cout << "Element not found \n";
    else
        cout << "Element found at " + res;
}