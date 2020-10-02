#include <iostream>
#include <vector>

int LBS(std::vector<int> ar) {
    int i = 0;
    int j = 0;
    int n = ar.size();

    std::vector<int> lis;

    for (i = 0; i < n; i++) {
        lis.push_back(1);
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (ar[i] > ar[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    std::vector<int> lds;
    
    for (i = 0; i < n; i++) {
        lds.push_back(1);
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

    std::cout << "Enter the size of the array: ";
    std::cin >> n;

    std::vector<int> arr;
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        int temp = 0;
        std::cin >> temp;
        arr.push_back(temp);
    }

    std::cout << LBS(arr) << std::endl;
    return 0;
}
