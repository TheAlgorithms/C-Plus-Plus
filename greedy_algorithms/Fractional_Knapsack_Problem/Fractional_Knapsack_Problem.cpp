#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int weight;
    int value;
    double valuePerWeight;
};

bool compareItems(const Item& item1, const Item& item2) {
    return item1.valuePerWeight > item2.valuePerWeight;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(), compareItems);

    double maxValue = 0.0;

    for (const Item& item : items) {
        if (capacity <= 0) {
            break;
        }

        double fraction = min(static_cast<double>(item.weight),
                              static_cast<double>(capacity));
        maxValue += (fraction / item.weight) * item.value;
        capacity -= fraction;
    }

    return maxValue;
}

int main() {
    vector<Item> items = {
        {10, 60,
         0.0},  // Weight, Value, Value per Weight (initially set to 0.0)
        {20, 100, 0.0},
        {30, 120, 0.0}};

    int knapsackCapacity = 50;

    for (Item& item : items) {
        item.valuePerWeight = static_cast<double>(item.value) / item.weight;
    }

    double maxValue = fractionalKnapsack(items, knapsackCapacity);

    cout << "Maximum value in the knapsack: " << maxValue << endl;

    return 0;
}
