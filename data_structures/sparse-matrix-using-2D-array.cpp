#include <iostream>
using namespace std;

// main function
int main() {
    int ord;     // order of square matrix
    cout << "Enter the order of matrix : ";
    cin >> ord;
    int c1=0;
    int a[ord][ord];    // initialising an empty 2d array
    for (int i=0; i<ord; i++){
        for (int j=0; j<ord; j++){
            cout << "Element " << i << "," << j << " : ";
            cin >> a[i][j];
            if (a[i][j]==0){
                c1++;
            }
        }
    }
    int b[ord*ord];
    int ind=0;
    for (int i=0; i<ord; i++){
        for (int j=0; j<ord; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    if (c1>(ord*ord)/2){     // check for sparse matrix
        cout << "Matrix is a Sparse Matrix\nThe elements stored in 1D array are:\n";
        for (int i=0; i<ord; i++){
            for (int j=0; j<ord; j++){
                if (a[i][j]!=0){
                    b[ind]=a[i][j];
                    cout << b[ind] << " ";
                    ind++;
                }
            }
        }
    }
    return 0;
}
