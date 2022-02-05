// C++ program to implement gravity/bead sort
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <memory>

#define BEAD(i, j) beads[i * max + j]

// function to perform the above algorithm
template <typename T, size_t N>
void beadSort(std::array<T, N>& a) {
    auto len = a.size();
    int max = *std::max_element(std::begin(a), std::end(a));

    auto beads = std::make_unique<unsigned char[]>(max * len);
    auto index = [&](auto const& i) { return beads.get() + i * max; };

    // mark the beads
    for (size_t i = 0; i < len; i++) std::memset(index(i), 1, a[i]);

    for (int j = 0; j < max; j++) {
        // count how many beads are on each post
        int sum = 0;
        for (size_t i = 0; i < len; i++) {
            sum += BEAD(i, j);
            BEAD(i, j) = 0;
        }

        // Move beads down
        for (size_t i = len - sum; i < len; i++) BEAD(i, j) = 1;
    }

    // Put sorted values in array using beads
    for (size_t i = 0; i < len; i++) {
        auto first{index(i)};
        a[i] = std::distance(first, std::find(first, first + max, 0));
    }
}

// driver function to test the algorithm
int main() {
    std::array<int, 8> a{5, 3, 1, 7, 4, 1, 1, 20};

    beadSort(a);

    for (auto const& element : a) printf("%d ", element);

    printf("\n");

    return 0;
}
