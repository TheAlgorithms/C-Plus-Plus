#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cout << "Enter size of array=\t";
    std::cin >> n;
    std::cout << "Enter Number of indeces u want to rotate the array to left=\t";
    std::cin >> k;
    std::vector<int> a;
    std::cout << "Enter  elements of array=\t";
    int value;
    for (int i = 0; i < n; i++) {
        std::cin >> value;
        a.push_back(value);
    }
    int temp = 0;
    for (int i = 0; i < k; i++) {
        temp = a[0];
        for (int j = 0; j < n; j++) {
            if (j == n - 1) {
                a[n - 1] = temp;
            } else {
                a[j] = a[j + 1];
            }
        }
    }
    std::cout << "Your rotated array is=\t";
    for (int j = 0; j < n; j++) {
        std::cout << a[j] << " ";
    }
    getchar();
    return 0;
}
