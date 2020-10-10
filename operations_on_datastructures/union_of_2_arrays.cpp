#include <iostream>
int main() {
    int i = 0, j = 0;
    std::array<int, 5> a{};
    std::array<int, 5> b{};
    std::cout << "Enter elements of array 1:";
    for (i = 0; i < 5; i++) std::cin >> a[i];
    std::cout << "Enter elements of array 2:";
    for (i = 0; i < 5; i++) std::cin >> b[i];
    i = 0;
    j = 0;
    while ((i < 5) && (j < 5)) {
        if (a[i] < b[j]) {
            std::cout << a[i++] << " ";
        } else if (a[i] > b[j]) {
            std::cout << b[j++] << " ";
        } else {
            std::cout << a[i++];
            j++;
        }
    }
    while (i < 5) std::cout << a[i++] << " ";
    while (j < 5) std::cout << b[j++] << " ";
    return 0;
}
