#include <iostream>
#include <list>
#include <stack>

#define WHITE 0
#define GREY 1
#define BLACK 2
#define INF 99999

using namespace std;

int checked[999] = {WHITE};

void dfs(const list<int> lista[], int start)
{
    stack<int> stack;

    int checked[999] = {WHITE};

    stack.push(start);

    checked[start] = GREY;
    while (!stack.empty())
    {
        int act = stack.top();
        stack.pop();

        if (checked[act] == GREY)
        {
            cout << act << ' ';
            for (auto it = lista[act].begin(); it != lista[act].end(); ++it)
            {
                stack.push(*it);
                if (checked[*it] != BLACK)
                    checked[*it] = GREY;
            }
            checked[act] = BLACK; //nodo controllato
        }
    }
}

int main()
{
    int u, w;
    int n;
    cin >> n;
    list<int> lista[INF];
    for (int i = 0; i < n; ++i)
    {
        cin >> u >> w;
        lista[u].push_back(w);
    }

    dfs(lista, 0);

    return 0;
}
