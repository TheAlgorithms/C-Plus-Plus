/**
 * Binary Indexed Tree also called Fenwik Tree provides a way to represent an array of numbers in an array,
 * allowing prefix sums to be calculated efficiently
 * 
 * Time Complexity is O(logN) 
 * It requires less space comapred to segment tree.
 * Conditions for using Binary Tree:-
 *  -> Ensure that the function is associative
 *  -> Ensure that the function has an inverse (eg Multiplication has inverse Division, gcd() has no inverse) 
**/
#include <iostream>
using namespace std;

// used for querying the tree for RangeSum
int read(int index, int BIT[]) {
    int sum = 0;
    index = index + 1;
    while (index > 0) {
        sum += BIT[index];
        index -= (index & (-index));
    }
    return sum;
}

// used for updating the tree for RangeSum
void update(int index, int n, int value, int BIT[]) {
    index = index + 1;
    while (index <= n) {
        BIT[index] += value;
        index += (index & (-index));
    }
}

// Construction of BIT
int * cretateBITree(int arr[], int n) {
    int * BIT = new int[n + 1];
    for (int i = 1; i <= n; i ++) {
        BIT[i] = 0;
    }
    for (int i = 0; i < n; i ++) {
        update(i, n, arr[i], BIT);
    }
    return BIT;
}

int main() { 
    // this array will be used as BIT
    int arr[100];
    // here N is the number of elements
    int N;
    cout << "Enter the number of elements" << endl;
    cin >> N;
    for (int i = 0; i <= N - 1; i ++) {
        cout << "Element at Index " << i << ": ";
        cin >> arr[i];
    }
    int * BIT = cretateBITree(arr, N);
    cout << "Tree created perform queries i.e sum upto nth index in BIT" << endl;
    cout << "Enter the number of Tests" << endl;
    int t;
    cin >> t;
    while (t --) {
        cout << "Enter Query: ";
        int query;
        cin >> query;
        cout << "Sum in index range 0..." << query << " is: " << read(query, BIT) << endl;
    }

}
