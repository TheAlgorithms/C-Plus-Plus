#include <queue>
#include <stdio.h>
#include <vector>

using std::queue;
using std::vector;

const int kEdgeSize = 6;

int main()
{
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        int N, M;
        scanf("%d %d", &N, &M);

        vector<vector<int>> adjlist(N + 1);
        for (int a = 1; a <= M; a++) {
            int A, B;
            scanf("%d %d", &A, &B);

            adjlist[A].push_back(B);
            adjlist[B].push_back(A);
        }

        int start_node = -1;
        scanf("%d", &start_node);

        queue<int> q;
        q.push(start_node);

        vector<int> dist(N + 1, -1);
        dist[start_node] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (size_t a = 0; a < adjlist[u].size(); a++) {
                int v = adjlist[u][a];

                if (dist[v] == -1) {
                    dist[v] = dist[u] + kEdgeSize;
                    q.push(v);
                }
            }
        }

        for (int a = 1; a <= N; a++)
            if (a != start_node)
                printf("%d ", dist[a]);
        printf("\n");
    }
}

