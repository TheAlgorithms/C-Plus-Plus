#include <iostream>
#include <list>
#include <queue>


#define WHITE 0
#define GREY 1
#define BLACK 2
#define INF 99999

using namespace std;

int checked[999] = { WHITE };

void bfs(const list<int> lista[], int start) {
	queue<int> q;

	int checked[999] = { WHITE };

	q.push(start);

	checked[start] = GREY;
	while (!q.empty()) {
		int act = q.front();
		q.pop();

		if (checked[act] == GREY) {
			cout << act << ' ';
			for (auto it = lista[act].begin(); it != lista[act].end(); ++it) {
				q.push(*it);
				if (checked[*it] != BLACK)
					checked[*it] = GREY;
			}
			checked[act] = BLACK; //nodo controllato
		}
	}
}

int main() {
	int u, w;
	int n;
	cin >> n;
	list<int> lista[INF];
	for (int i = 0; i < n; ++i) {
		cin >> u >> w;
		lista[u].push_back(w);
	}

	bfs(lista, 0);


	return 0;
}
