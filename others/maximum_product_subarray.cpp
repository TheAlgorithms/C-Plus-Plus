
// Program to find maximum product of a contiguous subarray within an array
#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

// This function returns the maximum product of a contiguous subarray within the given array.

int maxProduct(vector<int>& InputArray) {
    int maxProd = INT_MIN;
    int maxSoFar = 1, minSoFar = 1; // maintaining counter

    for (int i = 0; i < InputArray.size(); i++) {
       
        int newMaxSoFar = max({maxSoFar * InputArray[i], InputArray[i],minSoFar * InputArray[i]});

        int newMinSoFar = min({minSoFar * InputArray[i], InputArray[i], maxSoFar * InputArray[i]});

        maxProd = max(newMaxSoFar, maxProd);   
       
        maxSoFar = newMaxSoFar;
        minSoFar = newMinSoFar;
    }

    return maxProd;
}

int main() {
    int sizeOfArray, maxProd = 0;
    cin >> sizeOfArray;

    vector<int> InputArray;
    for (int i = 0; i < sizeOfArray; i++) {
        int num;
        cin >> num;
        InputArray.push_back(num);
    }
    maxProd = maxProduct(InputArray);
    cout << maxProd;
    return 0;
}
