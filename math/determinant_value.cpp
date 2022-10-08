#include <iostream>
#include <math.h>
using namespace std;
#define N 4
int determinantOfMatrix(int mat[N][N], int n)
{
    int num1, num2, det = 1, index, total = 1;

    // temporary array for storing row
    int temp[n + 1];

    // loop for traversing the diagonal elements
    for (int i = 0; i < n; i++)
    {
        index = i;

        // finding the index which has non zero value
        while (index < n && mat[index][i] == 0)
        {
            index++;
        }
        if (index == n) // if there is non zero element
        {
            // the determinant of matrix is zero
            continue;
        }
        if (index != i)
        {
            // loop for swapping the diagonal element row and index row
            for (int j = 0; j < n; j++)
            {
                swap(mat[index][j], mat[i][j]);
            }
            // determinant sign changes when we shift rows
            det *= pow(-1, index - i);
        }

        // storing the values of diagonal row elements
        for (int j = 0; j < n; j++)
        {
            temp[j] = mat[i][j];
        }
        // traversing every row below the diagonal element
        for (int j = i + 1; j < n; j++)
        {
            num1 = temp[i]; // value of diagonal element
            num2 = mat[j][i]; // value of next row element

            // traversing every column of row and multiplying to every row
            for (int k = 0; k < n; k++)
            {
                // multiplying to make the diagonal element and next row element equal
                mat[j][k] = (num1 * mat[j][k]) - (num2 * temp[k]);
            }
            total *= num1; // Using the property Det(kA)= k x Det(A);
        }
    }

    // multiplying the diagonal elements to get determinant
    for (int i = 0; i < n; i++)
    {
        det *= mat[i][i];
    }
    return (det / total); // Using the property Det(kA)/k = Det(A);
}

int main()
{
    int mat[N][N] = { { 1, 0, 2, -1 },
                      { 3, 0, 0, 5 },
                      { 2, 1, 4, -3 },
                      { 1, 0, 5, 0 } };

    printf("Determinant of the matrix is : %d", determinantOfMatrix(mat, N));
    return 0;
}
