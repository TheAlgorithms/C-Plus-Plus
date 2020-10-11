#include <cmath>
#include <iostream>
#include <vector>

struct Item {
    int weight;
    int profit;
};

float profitPerUnit(Item x) {
    return static_cast<float>(x.profit) / static_cast<float>(x.weight);
}

int partition(std::vector<Item> arr, int low, int high) {
    Item pivot = arr[high];  // pivot
    int i = (low - 1);       // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (profitPerUnit(arr[j]) <= profitPerUnit(pivot)) {
            i++;  // increment index of smaller element
            Item temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Item temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(const std::vector<Item> &arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    std::cout << "\nEnter the capacity of the knapsack : ";
    float capacity;
    std::cin >> capacity;
    std::cout << "\n Enter the number of Items : ";
    int n = 0;
    std::cin >> n;
    std::vector<Item> itemArray(n);
    for (int i = 0; i < n; i++) {
        std::cout << "\nEnter the weight and profit of item " << i + 1 << " : ";
        std::cin >> itemArray[i].weight;
        std::cin >> itemArray[i].profit;
    }

    quickSort(itemArray, 0, n - 1);

    // show(itemArray, n);

    float maxProfit = 0;
    int i = n;
    while (capacity > 0 && --i >= 0) {
        if (capacity >= static_cast<float>(itemArray[i].weight)) {
            maxProfit += static_cast<float>(itemArray[i].profit);
            capacity -= static_cast<float>(itemArray[i].weight);
            std::cout << "\n\t" << itemArray[i].weight << "\t"
                      << itemArray[i].profit;
        } else {
            maxProfit += profitPerUnit(itemArray[i]) * capacity;
            std::cout << "\n\t" << capacity << "\t"
                      << profitPerUnit(itemArray[i]) * capacity;
            capacity = 0;
            break;
        }
    }

    std::cout << "\nMax Profit : " << maxProfit;

    return 0;
}
