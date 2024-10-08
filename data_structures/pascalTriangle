#include <iostream>
#include <vector>
using namespace std;

void printPascalsTriangle(int n) {
   
    vector<vector<int>> pascal(n);

   
    for (int i = 0; i < n; i++) {
        // Resize the current row to accommodate i + 1 elements
        pascal[i].resize(i + 1);
        
        // The first and last values in each row are always 1
        pascal[i][0] = pascal[i][i] = 1;

        // Calculate the values between the first and last element in each row
        for (int j = 1; j < i; j++) {
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }

    // Print Pascal's Triangle
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << pascal[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows;

    // Input the number of rows for Pascal's Triangle
    cout << "Enter the number of rows for Pascal's Triangle: ";
    cin >> rows;

    // Function call to print Pascal's Triangle
    printPascalsTriangle(rows);

    return 0;
}
