#include <iostream>
using namespace std;

struct Item {
    int weight;
    int profit;
};

float profitPerUnit(Item x) { return (float)x.profit / (float)x.weight; }

int partition(Item arr[], int low, int high) {
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

void quickSort(Item arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    cout << "\nEnter the capacity of the knapsack : ";
    float capacity;
    cin >> capacity;
    cout << "\n Enter the number of Items : ";
    int n;
    cin >> n;
    Item itemArray[n];
    for (int i = 0; i < n; i++) {
        cout << "\nEnter the weight and profit of item " << i + 1 << " : ";
        cin >> itemArray[i].weight;
        cin >> itemArray[i].profit;
    }

    quickSort(itemArray, 0, n - 1);

    // show(itemArray, n);

    float maxProfit = 0;
    int i = n;
    while (capacity > 0 && --i >= 0) {
        if (capacity >= itemArray[i].weight) {
            maxProfit += itemArray[i].profit;
            capacity -= itemArray[i].weight;
            cout << "\n\t" << itemArray[i].weight << "\t"
                 << itemArray[i].profit;
        } else {
            maxProfit += profitPerUnit(itemArray[i]) * capacity;
            cout << "\n\t" << capacity << "\t"
                 << profitPerUnit(itemArray[i]) * capacity;
            capacity = 0;
            break;
        }
    }

    cout << "\nMax Profit : " << maxProfit;

    return 0;
}
