#include <bits/stdc++.h>

using namespace std;

int a[100005];
int n;

int FindNextGap(int x) {
    x = (x * 10) / 13;

    return max(1, x);
}

void CombSort(int a[], int l, int r) {
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped) {
        gap = FindNextGap(gap);

        swapped = false;

        for(int i = l; i <= r - gap; ++i) {
            if (a[i] > a[i + gap]) {
                swap(a[i], a[i + gap]);
                swapped = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    CombSort(a, 1, n);

    for(int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}