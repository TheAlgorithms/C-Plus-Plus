#include <bits/stdc++.h>

#define endl '\n'

template<typename T>
struct heap {
    std::vector<T> array;

    static inline unsigned long parent(unsigned long pos) {
        return (pos - 1) >> 1;
    }

    static inline unsigned long left_child(unsigned long pos) {
        return (pos << 1) + 1;
    }

    static inline unsigned long right_child(unsigned long pos) {
        return (pos << 1) + 2;
    }

    void bubble_up(unsigned long i) {
        while (i > 0 && this->array[heap::parent(i)] < this->array[i]) {
            std::swap(this->array[heap::parent(i)], this->array[i]);
            i = heap::parent(i);
        }
    }

    void heapify(int i) {
        int e = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < this->array.size() && this->array[e] < this->array[l])
            e = l;

        if (r < this->array.size() && this->array[e] < this->array[r])
            e = r;

        if (e != i) {
            std::swap(this->array[e], this->array[i]);
            heapify(e);
        }
    }

    void insert(T t) {
        this->array.push_back(t);
        this->bubble_up(this->array.size() - 1);
    }

    T extract() {
        T t = this->array[0];
        std::swap(this->array[0], this->array[this->array.size() - 1]);
        this->array.pop_back();
        heapify(0);
        return t;
    }

    inline bool empty() const {
        return this->array.empty();
    }
};

template<typename T>
struct min_container {
    T value;

    min_container(T value) {
        this->value = value;
    }

    bool operator<(const min_container &rhs) const {
        return value >= rhs.value;
    }

    friend std::ostream &operator<<(std::ostream &os, const min_container &container) {
        os << container.value;
        return os;
    }

    operator T() {
        return this->value;
    }
};

template<typename T>
struct max_container {
    T value;

    max_container(T value) {
        this->value = value;
    }

    bool operator<(const max_container &rhs) const {
        return value < rhs.value;
    }

    friend std::ostream &operator<<(std::ostream &os, const max_container &container) {
        os << container.value;
        return os;
    }

    operator T() {
        return this->value;
    }
};

int dijkstra(std::vector<std::vector<std::pair<int, int>>> &graph, int u, int v) {
    std::vector<int> w(graph.size(), INT_MAX);
    w[u] = 0;

    ::heap<::min_container<std::pair<int, int>>> heap;
    heap.insert(std::make_pair(w[u], u));
    while (!heap.empty()) {
        std::pair<int, int> el = heap.extract().value;

        for (auto &e : graph[el.second])
            if (w[e.first] > w[el.second] + e.second) {
                w[e.first] = w[el.second] + e.second;

                heap.insert(std::make_pair(w[e.first], e.first));
            }
    }

    return w[v];
}

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<pair<int, int>>> graph(4);
    graph[0].emplace_back(1, 1);
    graph[0].emplace_back(3, 10);
    graph[1].emplace_back(2, 1);
    graph[1].emplace_back(3, 5);
    graph[2].emplace_back(3, 1);

    cout << dijkstra(graph, 0, 3) << endl;

    return 0;
}
