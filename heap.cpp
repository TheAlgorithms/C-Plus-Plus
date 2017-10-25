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

    inline bool is_empty() const {
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
};

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ::heap<min_container<int>> min_heap;
    ::heap<max_container<int>> max_heap;

    for (int i = 0; i < 10; i++) {
        min_heap.insert(i);
        max_heap.insert(i);
    }

    for (int i = 0; i < 10; i++) {
        cout << "min: " << min_heap.extract() << endl;
        cout << "max: " << max_heap.extract() << endl;
        cout << endl;
    }

    return 0;
}
