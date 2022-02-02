// C++ program to implement gravity/bead sort
#include <cstdio>
#include <cstring>
#include <memory>
#include <algorithm>

#define BEAD(i, j) beads[i * max + j]

// function to perform the above algorithm
void beadSort(int *a, size_t len) {
    int max = *std::max_element(a, a + len);

    auto beads = std::make_unique<unsigned char[]>(max * len);

    // mark the beads
    for (int i = 0; i < len; i++)
        for (int j = 0; j < a[i]; j++) BEAD(i, j) = 1;

    for (int j = 0; j < max; j++) {
        // count how many beads are on each post
        int sum = 0;
        for (int i = 0; i < len; i++) {
            sum += BEAD(i, j);
            BEAD(i, j) = 0;
        }

        // Move beads down
        for (int i = len - sum; i < len; i++) BEAD(i, j) = 1;
    }

    // Put sorted values in array using beads
    for (int i = 0; i < len; i++) {
        int j;
        for (j = 0; j < max && BEAD(i, j); j++) {
        }

        a[i] = j;
    }
}

// driver function to test the algorithm
int main() {
    int a[] = {5, 3, 1, 7, 4, 1, 1, 20};
    int len = sizeof(a) / sizeof(a[0]);

    beadSort(a, len);

    for (int i = 0; i < len; i++) printf("%d ", a[i]);

    return 0;
}
