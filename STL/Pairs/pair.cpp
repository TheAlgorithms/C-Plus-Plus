
#include <bits/stdc++.h>
using namespace std;

int self_input()
{
    pair<int, char> r = {34, 't'};
    cout << r.first << " " << r.second;

    // runtime
    pair<int, string> r(34, "hjkhae");
}

int vector_of_pairs()
{
    vector<pair<int, int>> a;
    for (int i = 0; i < a.size(); i++)
    {
        int x, y;
        cin >> x >> y;
        a.push_back({x, y});
    }
}

int array_of_pairs()
{
    int n;
    cin >> n;
    pair<int, int> a[n];

    for (int i = 0; i < n; i++)
        cin >> a[i].first >> a[i].second;
}

int swap_pair()
{
    pair<int, char> p1 = {23, 't'};
    pair<int, char> p2 = {100, 'k'};

    p1.swap(p2); // swap function used in pair
}

int main()
{
    return 0;
}
