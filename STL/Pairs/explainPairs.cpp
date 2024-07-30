#include <bits/stdc++.h>
using namespace std;

int explainPairs()
{
    // pair of intergers
    pair<int, int> p;
    p = {13, 24};
    // cout << p.first << " " << p.second << endl;

    // pair of integer and pair of integers
    pair<int, pair<int, int>> a;
    a = {13, {93, 89}};

    // pair of array of pair
    pair<int, int> arr[5] = {{13, 43}, {24, 78}, {73, 83}, {38, 48}, {12, 89}};
    // or
    arr[0] = {23, 48}, arr[1] = {32, 89}, arr[2] = {90, 89}, arr[3] = {38, 29}, arr[4] = {32, 49};

    for (int i = 0; i < 5; i++)
    {
        cout << arr[i].first << " " << arr[i].second << endl;
    }

    // how to enter elements in pair using loop
    pair<int, int> pr[10];
    for (int i = 0; i < 10; i++)
    {
        int n, m;
        cin >> n >> m;
        pr[i] = {n, m};
    }

    // how to print elements in pair using loop
    for (int i = 0; i < 10; i++)
    {
        cout << pr[i].first << " " << pr[i].second << endl;
    }
}

int main()
{
    explainPairs();
    return 0;
}