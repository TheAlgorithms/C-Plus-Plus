#include <bits/stdc++.h>
using namespace std;

int Max1DRangeSum(int A[], int n)
{
    int sum = 0, ans = 0;
    for (int i = 0; i < n; i++)   //O(n)
    {
        sum += A[i];
        ans = max(ans, sum);
        if (sum < 0) sum = 0;
    }
    return ans;
}

int main()
{
    int n = 9, A[] = { 4, -5, 4, -3, 4, 4, -4, 4, -5 };
    printf("Max 1D Range Sum = %d\n", Max1DRangeSum(A,n));

    return 0;
}
