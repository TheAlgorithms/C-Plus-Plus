#include <queue>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;
#define INF 10000010
vector<pair<int, int>> graph[5 * 100001];
int dis[5 * 100001];
int dij(vector<pair<int, int>> *v, int s, int *dis)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // source distance to zero.
    pq.push(make_pair(0, s));
    dis[s] = 0;
    int u;
    while (!pq.empty())
    {
        u = (pq.top()).second;
        pq.pop();
        for (vector<pair<int, int>>::iterator it = v[u].begin(); it != v[u].end(); it++)
        {
            if (dis[u] + it->first < dis[it->second])
            {
                dis[it->second] = dis[u] + it->first;
                pq.push(make_pair(dis[it->second], it->second));
            }
        }
    }
}
int main()
{
    int m, n, l, x, y, s;
    // n--> number of nodes , m --> number of edges
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        // input edges.
        scanf("%d%d%d", &x, &y, &l);
        graph[x].push_back(make_pair(l, y));
        graph[y].push_back(make_pair(l, x)); // comment this line for directed graph
    }
    // start node.
    scanf("%d", &s);
    // intialise all distances to infinity.
    for (int i = 1; i <= n; i++)
        dis[i] = INF;
    dij(graph, s, dis);

    for (int i = 1; i <= n; i++)
        if (dis[i] == INF)
            cout << "-1 ";
        else
            cout << dis[i] << " ";
    return 0;
}
