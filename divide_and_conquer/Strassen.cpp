#include <iostream>
using namespace std;

int main()
{
    int m1[2][2], m2[2][2], res[2][2], x, y;
    int p, q, r, s, t, u, v;

    cout << endl << "Enter the Elements for Matrix 1:" << endl;
    for (x = 0; x < 2; x++)
    {
        for (y = 0; y < 2; y++)
        {
            cin >> m1[x][y];
        }
    }

    cout << endl << "Enter the Elements for Matrix 2:" << endl;
    for (x = 0; x < 2; x++)
    {
        for (y = 0; y < 2; y++)
        {
            cin >> m2[x][y];
        }
    }

    p = (m1[0][0] + m1[1][1]) * (m2[0][0] + m2[1][1]);
    q = (m1[1][0] + m1[1][1]) * m2[0][0];
    r = m1[0][0] * (m2[0][1] - m2[1][1]);
    s = m1[1][1] * (m2[1][0] - m2[0][0]);
    t = (m1[0][0] + m1[0][1]) * m2[1][1];
    u = (m1[1][0] - m1[0][0]) * (m2[0][0] + m2[0][1]);
    v = (m1[0][1] - m1[1][1]) * (m2[1][0] + m2[1][1]);

    res[0][0] = p + s - t + v;
    res[0][1] = r + t;
    res[1][0] = q + s;
    res[1][1] = p - q + r + u;

    cout << endl << "The resultant Matrix is:" << endl;
    for (x = 0; x < 2; x++)
    {
        cout << endl;
        for (y = 0; y < 2; y++)
        {
            cout << res[x][y] << "\t";
        }
    }
    cout << endl;

    return 0;
}