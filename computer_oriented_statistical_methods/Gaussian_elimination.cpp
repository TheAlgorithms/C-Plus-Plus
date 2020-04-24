#include <iostream>
using namespace std;

int main()
{
    int mat_size, i, j, step;

    cout << "Matrix size: ";
    cin >> mat_size;

    double mat[mat_size + 1][mat_size + 1], x[mat_size][mat_size + 1];

    cout << endl
         << "Enter value of the matrix: " << endl;
    for (i = 0; i < mat_size; i++)
    {
        for (j = 0; j <= mat_size; j++)
        {
            cin >> mat[i][j]; //Enter (mat_size*mat_size) value of the matrix.
        }
    }

    for (step = 0; step < mat_size - 1; step++)
    {
        for (i = step; i < mat_size - 1; i++)
        {
            double a = (mat[i + 1][step] / mat[step][step]);

            for (j = step; j <= mat_size; j++)
                mat[i + 1][j] = mat[i + 1][j] - (a * mat[step][j]);
        }
    }

    cout << endl
         << "Matrix using Gaussian Elimination method: " << endl;
    for (i = 0; i < mat_size; i++)
    {
        for (j = 0; j <= mat_size; j++)
        {
            x[i][j] = mat[i][j];
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl
         << "Value of the Gaussian Elimination method: " << endl;
    for (i = mat_size - 1; i >= 0; i--)
    {
        double sum = 0;
        for (j = mat_size - 1; j > i; j--)
        {
            x[i][j] = x[j][j] * x[i][j];
            sum = x[i][j] + sum;
        }
        if (x[i][i] == 0)
            x[i][i] = 0;
        else
            x[i][i] = (x[i][mat_size] - sum) / (x[i][i]);

        cout << "x" << i << "= " << x[i][i] << endl;
    }
    return 0;
}
