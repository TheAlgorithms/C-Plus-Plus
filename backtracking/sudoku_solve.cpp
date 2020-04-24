#include <iostream>
using namespace std;
///N=9;
int n = 9;

bool isPossible(int mat[][9], int i, int j, int no)
{
    ///Row or col nahin hona chahiye
    for (int x = 0; x < n; x++)
    {
        if (mat[x][j] == no || mat[i][x] == no)
        {
            return false;
        }
    }

    /// Subgrid mein nahi hona chahiye
    int sx = (i / 3) * 3;
    int sy = (j / 3) * 3;

    for (int x = sx; x < sx + 3; x++)
    {
        for (int y = sy; y < sy + 3; y++)
        {
            if (mat[x][y] == no)
            {
                return false;
            }
        }
    }

    return true;
}
void printMat(int mat[][9])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
            if ((j + 1) % 3 == 0)
            {
                cout << '\t';
            }
        }
        if ((i + 1) % 3 == 0)
        {
            cout << endl;
        }
        cout << endl;
    }
}

bool solveSudoku(int mat[][9], int i, int j)
{
    ///Base Case
    if (i == 9)
    {
        ///Solve kr chuke hain for 9 rows already
        printMat(mat);
        return true;
    }

    ///Crossed the last  Cell in the row
    if (j == 9)
    {
        return solveSudoku(mat, i + 1, 0);
    }

    ///Blue Cell - Skip
    if (mat[i][j] != 0)
    {
        return solveSudoku(mat, i, j + 1);
    }
    ///White Cell
    ///Try to place every possible no
    for (int no = 1; no <= 9; no++)
    {
        if (isPossible(mat, i, j, no))
        {
            ///Place the no - assuming solution aa jayega
            mat[i][j] = no;
            bool aageKiSolveHui = solveSudoku(mat, i, j + 1);
            if (aageKiSolveHui)
            {
                return true;
            }
            ///Nahin solve hui
            ///loop will place the next no.
        }
    }
    ///Sare no try kr liey, kisi se bhi solve nahi hui
    mat[i][j] = 0;
    return false;
}

int main()
{

    int mat[9][9] =
        {{5, 3, 0, 0, 7, 0, 0, 0, 0},
         {6, 0, 0, 1, 9, 5, 0, 0, 0},
         {0, 9, 8, 0, 0, 0, 0, 6, 0},
         {8, 0, 0, 0, 6, 0, 0, 0, 3},
         {4, 0, 0, 8, 0, 3, 0, 0, 1},
         {7, 0, 0, 0, 2, 0, 0, 0, 6},
         {0, 6, 0, 0, 0, 0, 2, 8, 0},
         {0, 0, 0, 4, 1, 9, 0, 0, 5},
         {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    printMat(mat);
    cout << "Solution " << endl;
    solveSudoku(mat, 0, 0);

    return 0;
}
