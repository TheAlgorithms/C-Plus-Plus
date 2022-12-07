/*

Code for Strassen's Matrix Multiplication Algorithm

Strassen's Matrix Multiplication techinque works upon the divide and conquer methedology.

Here, in the following code:
1) We have declared variables in accordance to the requirements
2) We ran two loops for taking input for 2 matrices, which are to be mulitplied
3) Then we took the elements from the matrices and assign them to variables p to v in accordance to the Strassen's Method which are
    p = a * (f - h)
    q = (a + b) * h
    r = (c + d) * e
    s = d * (g - e)
    t = (a + d) * (e + h)
    u = (b - d) * (g + h)
    v = (a - c) * (e + f)
4) Then we assigned the elements of the resultant matrix according to the Strassen's method, which is
        C = |t+s-q+u    p+q   |
            |   r+s    p+t-r-v|  
5) Then, we ran a loop in order to print the resultant matrix


Code Contributed by: Tiger Sharks

*/

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