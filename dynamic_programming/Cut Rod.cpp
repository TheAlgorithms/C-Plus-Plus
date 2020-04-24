/*Given a rod of length n inches and an array of prices that 
contains prices of all pieces of size smaller than n. Determine 
the maximum value obtainable by cutting up the rod and selling 
the pieces.*/

#include <iostream>
using namespace std;
int cutrod(int p[], int n)
{
    int r[n + 1];
    r[0] = 0;
    for (int j = 0; j < n; j++)
    {
        int q = INT_MIN;
        for (int i = 0; i <= j; i++)
        {
            q = max(q, p[i] + r[j - i]);
        }
        r[j + 1] = q;
    }
    return r[n];
}
int main()
{
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
    cout << cutrod(price, 30);
    return 0;
}
