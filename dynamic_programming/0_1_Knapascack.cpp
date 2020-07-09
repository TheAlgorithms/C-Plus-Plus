#include<iostream>

int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int Knapsack(int *wt, int *val , int W, int n)
{
    int arr[n + 1][W + 1];

    for(int i = 0; i < n + 1; i++)
    {
        for(int j = 0; j < W + 1; j++)
            if(i == 0 || j == 0)
                arr[i][j] = 0;
    }

    for(int i = 1 ; i < n + 1; i++)
    {
        for(int j = 1; j < W + 1; j++)
        {

            if(wt[i-1] <= j )
                arr[i][j] = max(val[i - 1] + arr[i - 1][j - wt[i - 1]], arr[i - 1][j]);

            else
                arr[i][j] = arr[i - 1][j];
        }
    }

    return arr[n][W];
}

int main()
{
    int n, W;

    std :: cout << "Enter no. of item ";
    std :: cin >> n;

    int *wt = new int [n];
    int *val = new int [n];

    for(int i = 0; i < n; i++)
    {
        std :: cout <<"Enter the weight and value of " << i + 1 << " item : ";
        std :: cin >> wt[i] >> val[i];
    }

    std :: cout << "Enter Max. capacity of Knapsack ";
    std :: cin >> W;


    int max_val = Knapsack(wt, val, W, n);

    cout << "Maximum value: " << max_val;
}
