#include <iostream>
using namespace std;
int LBS(int ar[], int n) {
    int i, j;
    int lis[n];
    for (i = 0; i < n; i++) {
        lis[i] = 1;
    }
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (ar[i] > ar[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;
        }
    }

    int lds[n];
    for (i = 0; i < n; i++) {
        lds[i] = 1;
    }

    for (i = n - 2; i >= 0; i--) {
        for (j = n - 1; j > i; j--) {
            if (ar[i] > ar[j] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }
    int max_result = lis[0] + lds[0] - 1;
    for (i = 1; i < n; i++) {
        if (lis[i] + lds[i] - 1 > max_result) {
            max_result = lis[i] + lds[i] - 1;
        }
    }

    return max_result;
}
int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int ar[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
    }

    cout << LBS(ar, n) << endl;
    return 0;
}
