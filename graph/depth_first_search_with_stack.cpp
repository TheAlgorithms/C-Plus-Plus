#include <iostream>
#include <list>
#include <stack>
#include <vector>

constexpr int WHITE = 0;
constexpr int GREY = 1;
constexpr int BLACK = 2;
constexpr int INF = 99999;

void dfs(const std::vector<std::list<int> > &graph, int start) {
    std::vector<int> checked(graph.size(), WHITE);
    checked[start] = GREY;
    std::stack<int> stack;
    stack.push(start);
    while (!stack.empty()) {
        int act = stack.top();
        stack.pop();

        if (checked[act] == GREY) {
            std::cout << act << ' ';
            for (auto it : graph[act]) {
                stack.push(it);
                if (checked[it] != BLACK) {
                    checked[it] = GREY;
                }
            }
            checked[act] = BLACK;  // nodo controllato
        }
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::list<int> > graph(INF);
    for (int i = 0; i < n; ++i) {
        int u = 0, w = 0;
        std::cin >> u >> w;
        graph[u].push_back(w);
    }

    dfs(graph, 0);

    return 0;
}
