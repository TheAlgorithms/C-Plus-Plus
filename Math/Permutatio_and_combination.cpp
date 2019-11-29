// Copyright 2019 Arctic2333
#include <stdio.h>

void combine(int n, int m, int a[], int b[],
    const int M) {
    for (int j = n; j >= m; j--) {
        b[m - 1] = j - 1;
        if (m > 1) {
            combine(j - 1, m - 1, a, b, M);
        } else {
            for (int i = M - 1; i >= 0; i--)
                printf("%d", a[b[i]]);
            printf("\n");
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", & n, & m);
    int a[n], b[m];
    for (int i = 0; i < n; i++)
        a[i] = i + 1;  // It can be assigned according to the actual situation
    const int M = m;
    combine(n, m, a, b, M);
    return 0;
}
