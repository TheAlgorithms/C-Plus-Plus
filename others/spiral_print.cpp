#include <iostream>
using namespace std;

void genArray(int a[][10], int r, int c)
{

    int value = 1;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            a[i][j] = value;
            cout << a[i][j] << " ";
            value++;
        }
        cout << endl;
    }
}
void spiralPrint(int a[][10], int r, int c)
{

    int startRow = 0, endRow = r - 1;
    int startCol = 0, endCol = c - 1;
    int cnt = 0;

    while (startRow <= endRow && startCol <= endCol)
    {

        ///Print start row
        for (int i = startCol; i <= endCol; i++, cnt++)
        {
            cout << a[startRow][i] << " ";
        }
        startRow++;

        ///Print the end col
        for (int i = startRow; i <= endRow; i++, cnt++)
        {
            cout << a[i][endCol] << " ";
        }
        endCol--;

        ///Print the end row
        if (cnt == r * c)
        {
            break;
        }

        for (int i = endCol; i >= startCol; i--, cnt++)
        {
            cout << a[endRow][i] << " ";
        }
        endRow--;

        ///Print the start Col
        if (cnt == r * c)
        {
            break;
        }
        for (int i = endRow; i >= startRow; i--, cnt++)
        {
            cout << a[i][startCol] << " ";
        }
        startCol++;
    }
}

int main()
{
    int a[10][10];

    int r, c;
    cin >> r >> c;
    genArray(a, r, c);
    spiralPrint(a, r, c);

    return 0;
}
