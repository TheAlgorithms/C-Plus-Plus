#include <algorithm>  /// for std::min
#include <array>      /// for std::array
#include <cassert>    /// for assert
#include <iostream>   /// for std::cout
#include <limits>     /// for std::numeric_limits
#include <vector>     /// for std::vector

/**
 * @file
 * @brief Binomial Heap (https://en.wikipedia.org/wiki/Binomial_heap)
 * @details
 * A binomial heap is made by a collection of binomial trees that supports
 * insert, get-min, delete-min and merging two binomial heaps in O(log n) time.
 * @author [Sarvesh](https://github.com/sarveshjoshi29)
 */

/**
 * @namespace data_structures
 * @brief Data structures algorithms
 */
namespace data_structures {

/**
 * @brief A min-heap implementation using a collection of binomial trees
 * @tparam T type of elements stored in the heap
 */
template <typename T>
class binomial_heap {
 private:
    static constexpr size_t N = 32;  ///< maximum number of binomial trees

    /**
     * @brief Node of a binomial tree
     */
    struct Node {
        T val;                        ///< value stored in the node
        std::vector<Node*> children;  ///< child nodes
        Node(T val_in) : val{val_in} {}
        ~Node() {
            for (auto p : children) {
                if (p != nullptr) {
                    delete p;
                }
            }
        }

        Node(const Node& other) {
            val = other.val;
            for (auto c : other.children) {
                Node* curr = new Node(*c);
                children.push_back(curr);
            }
        }

        Node& operator=(const Node& other) {
            if (this == &other) {
                return *this;
            }
            val = other.val;
            for (auto p : children) {
                delete p;
            }
            children.clear();
            for (auto c : other.children) {
                Node* curr = new Node(*c);
                children.push_back(curr);
            }
            return *this;
        }
    };

    /**
     * @brief Wrapper holding a binomial tree root and its order
     */
    struct binomial_component {
        Node* root;    ///< root node of the binomial tree
        size_t order;  ///< order (degree) of the binomial tree
        binomial_component(size_t ord = 0) {
            root = nullptr;
            order = ord;
        }
        ~binomial_component() {
            if (root != nullptr) {
                delete root;
            }
        }

        binomial_component(const binomial_component& other) {
            order = other.order;
            root = other.root ? new Node(*other.root) : nullptr;
        }

        binomial_component& operator=(const binomial_component& other) {
            if (this == &other) {
                return *this;
            }
            order = other.order;
            delete root;
            root = other.root ? new Node(*other.root) : nullptr;
            return *this;
        }
    };

    std::array<binomial_component*, N>
        components{};  ///< components[i] holds the tree of order i

    /**
     * @brief Merge two binomial components of the same order
     * @param a first component
     * @param b second component
     * @returns merged component with order incremented, or nullptr if merge is
     * invalid
     */
    binomial_component* merge_components(binomial_component* a,
                                         binomial_component* b) {
        if (a == nullptr || b == nullptr) {
            return nullptr;
        }
        if (a->order != b->order) {
            return nullptr;
        }

        // min heap property
        if (a->root->val <= b->root->val) {
            a->order++;
            a->root->children.push_back(b->root);
            b->root = nullptr;
            delete b;
            return a;
        } else {
            b->order++;
            b->root->children.push_back(a->root);
            a->root = nullptr;
            delete a;
            return b;
        }
    }

    /**
     * @brief Merge a set of components into the heap using carry propagation
     * @param new_comps array of components to merge in
     */
    void merge_set_of_comps(std::array<binomial_component*, N>& new_comps) {
        std::array<binomial_component*, N> carry{};
        std::array<binomial_component*, N> ans{};
        for (int i = 0; i < N - 1; i++) {
            binomial_component* pt1 = merge_components(carry[i], components[i]);
            if (pt1 != nullptr) {
                carry[i + 1] = pt1;
                ans[i] = new_comps[i];
                continue;
            }
            binomial_component* pt2 = merge_components(carry[i], new_comps[i]);
            if (pt2 != nullptr) {
                carry[i + 1] = pt2;
                ans[i] = components[i];
                continue;
            }
            binomial_component* pt3 =
                merge_components(components[i], new_comps[i]);
            if (pt3 != nullptr) {
                carry[i + 1] = pt3;
                ans[i] = carry[i];
                continue;
            }
            if (carry[i] != nullptr)
                ans[i] = carry[i];
            else if (components[i] != nullptr)
                ans[i] = components[i];
            else
                ans[i] = new_comps[i];
        }

        components = ans;
    }

 public:
    /**
     * @brief Insert a value into the heap
     * @param val value to insert
     */
    void insert(T val) {
        Node* curr = new Node(val);
        binomial_component* comp = new binomial_component(0);
        comp->root = curr;

        std::array<binomial_component*, N> new_comps{};
        new_comps[0] = comp;
        merge_set_of_comps(new_comps);
    }

    /**
     * @brief Remove the minimum element from the heap
     */
    void pop() {
        T ans = std::numeric_limits<T>::max();
        binomial_component* min_comp = nullptr;
        for (auto p : components) {
            if (p != nullptr && p->root->val < ans) {
                ans = p->root->val;
                min_comp = p;
            }
        }
        if (min_comp == nullptr) {
            return;
        }
        std::array<binomial_component*, N> new_comps{};
        for (size_t i = 0; i < min_comp->root->children.size(); i++) {
            binomial_component* bc = new binomial_component(i);
            bc->root = min_comp->root->children[i];
            new_comps[i] = bc;
        }
        min_comp->root->children.clear();
        components[min_comp->order] = nullptr;
        delete min_comp;
        merge_set_of_comps(new_comps);
    }

    /**
     * @brief Get the minimum element in the heap
     * @returns the minimum value
     */
    T get_min() {
        T ans = std::numeric_limits<T>::max();
        for (auto p : components) {
            if (p != nullptr) {
                ans = std::min(ans, p->root->val);
            }
        }
        return ans;
    }

    /**
     * @brief Get the minimum element in the heap (alias for get_min)
     * @returns the minimum value
     */
    T top() {
        T ans = std::numeric_limits<T>::max();
        for (auto p : components) {
            if (p != nullptr) {
                ans = std::min(ans, p->root->val);
            }
        }
        return ans;
    }

    /**
     * @brief Default constructor
     */
    binomial_heap() {}

    /**
     * @brief Destructor to free all allocated memory
     */
    ~binomial_heap() {
        for (auto p : components) {
            if (p != nullptr) {
                delete p;
            }
        }
    }

    /**
     * @brief Copy constructor
     */
    binomial_heap(const binomial_heap& other) {
        for (size_t i = 0; i < N; i++) {
            components[i] = other.components[i]
                                ? new binomial_component(*other.components[i])
                                : nullptr;
        }
    }

    /**
     * @brief Copy assignment operator
     */
    binomial_heap& operator=(const binomial_heap& other) {
        if (this == &other) {
            return *this;
        }
        for (size_t i = 0; i < N; i++) {
            delete components[i];
            components[i] = other.components[i]
                                ? new binomial_component(*other.components[i])
                                : nullptr;
        }
        return *this;
    }

    /**
     * @brief Merge another heap into this heap, consuming the other heap
     * @param other heap to merge (left empty after merge)
     */
    void merge(binomial_heap& other) {
        merge_set_of_comps(other.components);
        other.components.fill(nullptr);
    }

    /**
     * @brief Create a new heap by merging two heaps without modifying either
     * @param other heap to unify with
     * @returns a new binomial_heap containing all elements from both heaps
     */
    binomial_heap unify(const binomial_heap& other) const {
        binomial_heap result(*this);
        binomial_heap temp(other);
        result.merge(temp);
        return result;
    }
};

}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test 1: single insert and get_min
    {
        data_structures::binomial_heap<int> h;
        h.insert(5);
        assert(h.get_min() == 5);
    }

    // Test 2: insert two elements, min is correct
    {
        data_structures::binomial_heap<int> h;
        h.insert(10);
        h.insert(3);
        assert(h.get_min() == 3);
    }

    // Test 3: insert in decreasing order
    {
        data_structures::binomial_heap<int> h;
        h.insert(5);
        h.insert(4);
        h.insert(3);
        h.insert(2);
        h.insert(1);
        assert(h.get_min() == 1);
    }

    // Test 4: insert in increasing order
    {
        data_structures::binomial_heap<int> h;
        h.insert(1);
        h.insert(2);
        h.insert(3);
        h.insert(4);
        h.insert(5);
        assert(h.get_min() == 1);
    }

    // Test 5: pop removes the minimum
    {
        data_structures::binomial_heap<int> h;
        h.insert(3);
        h.insert(1);
        h.insert(2);
        assert(h.get_min() == 1);
        h.pop();
        assert(h.get_min() == 2);
        h.pop();
        assert(h.get_min() == 3);
    }

    // Test 6: test functioning of top and get_min
    {
        data_structures::binomial_heap<int> h;
        h.insert(7);
        h.insert(2);
        h.insert(9);
        assert(h.top() == h.get_min());
        assert(h.top() == 2);
    }

    // Test 7: pop all elements in sorted order
    {
        data_structures::binomial_heap<int> h;
        h.insert(4);
        h.insert(2);
        h.insert(7);
        h.insert(1);
        h.insert(5);
        int prev = h.get_min();
        h.pop();
        while (h.get_min() != std::numeric_limits<int>::max()) {
            assert(h.get_min() >= prev);
            prev = h.get_min();
            h.pop();
        }
    }

    // Test 8: duplicate values
    {
        data_structures::binomial_heap<int> h;
        h.insert(3);
        h.insert(3);
        h.insert(3);
        assert(h.get_min() == 3);
        h.pop();
        assert(h.get_min() == 3);
        h.pop();
        assert(h.get_min() == 3);
    }

    // Test 9: merge consumes the other heap
    {
        data_structures::binomial_heap<int> h1;
        h1.insert(5);
        h1.insert(3);
        data_structures::binomial_heap<int> h2;
        h2.insert(1);
        h2.insert(4);
        h1.merge(h2);
        assert(h1.get_min() == 1);
        assert(h2.get_min() == std::numeric_limits<int>::max());
    }

    // Test 10: merge and pop all in sorted order
    {
        data_structures::binomial_heap<int> h1;
        h1.insert(10);
        h1.insert(2);
        data_structures::binomial_heap<int> h2;
        h2.insert(7);
        h2.insert(1);
        h1.merge(h2);
        assert(h1.get_min() == 1);
        h1.pop();
        assert(h1.get_min() == 2);
        h1.pop();
        assert(h1.get_min() == 7);
        h1.pop();
        assert(h1.get_min() == 10);
    }

    // Test 11: unify keeps both heaps unchanged
    {
        data_structures::binomial_heap<int> h1;
        h1.insert(5);
        h1.insert(3);
        data_structures::binomial_heap<int> h2;
        h2.insert(1);
        h2.insert(4);
        data_structures::binomial_heap<int> h3 = h1.unify(h2);
        assert(h1.get_min() == 3);
        assert(h2.get_min() == 1);
        assert(h3.get_min() == 1);
    }

    // Test 12: unify and pop all in sorted order
    {
        data_structures::binomial_heap<int> h1;
        h1.insert(6);
        h1.insert(2);
        data_structures::binomial_heap<int> h2;
        h2.insert(9);
        h2.insert(1);
        data_structures::binomial_heap<int> h3 = h1.unify(h2);
        assert(h3.get_min() == 1);
        h3.pop();
        assert(h3.get_min() == 2);
        h3.pop();
        assert(h3.get_min() == 6);
        h3.pop();
        assert(h3.get_min() == 9);
    }

    // Test 13: negative values
    {
        data_structures::binomial_heap<int> h;
        h.insert(-1);
        h.insert(-5);
        h.insert(0);
        h.insert(3);
        assert(h.get_min() == -5);
        h.pop();
        assert(h.get_min() == -1);
    }

    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
