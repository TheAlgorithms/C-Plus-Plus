#include <iostream>
int main() {
    int i = 0, j = 0;
    int a[5];
    int b[5];
    std::cout << "Enter elements of array 1:";
    for (i = 0; i < 5; i++) std::cin >> a[i];
    std::cout << "Enter elements of array 2:";
    for (i = 0; i < 5; i++) std::cin >> b[i];
    i = 0;
    j = 0;
    while ((i < 5) && (j < 5)) {
        if (a[i] < b[j])
            i++;
        else if (a[i] > b[j])
            j++;
        else {
            std::cout << b[j] << " ";
            i++;
            j++;
        }
    }
    // while (i < 5) std::cout << a[i++] << " ";
    //  while (j < 5) std::cout << b[j++] << " ";
    return 0;
}
