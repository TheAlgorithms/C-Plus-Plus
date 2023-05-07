
/**
 * @file
 * @brief A balanced binary search tree (BST) on the basis of binary search tree
 * and heap: the [Treap](https://en.wikipedia.org/wiki/Treap) algorithm
 * implementation
 * @details
 * Implementation of the treap data structre
 *
 * Support operations including insert, erase, and query (the rank of specified
 * element or the element ranked x) as the same as BST
 *
 * But these operations take O(log N) time, since treap keeps property of heap
 * using rotate operation, and the desired depth of the tree is O(log N).
 * There's very little chance that it will degenerate into a chain like BST
 *
 * @author [Kairao ZHENG](https://github.com/fgmn)
 */

#include <iostream>  /// For IO operations

const int maxNode = 1e6 + 5; //< maximum number of nodes
/**
 * @brief Struct representation of the treap
 */
struct Treap {
    /**
     * @brief Basic data definition
     * root The root of the treap
     * treapCnt Total number of current nodes in the treap
     * key Node identifier
     * priority Random priority
     * childs [i][0] represents left child of node i, and [i][1] represents
     * right size Maintains the subtree size for ranking query cnt The number of
     * copies per node
     */
    int root, treapCnt, key[maxNode], priority[maxNode];
    int childs[maxNode][2], cnt[maxNode], size[maxNode];
    /**
     * @brief Initialization
     */
    Treap() {
        root = 0;
        treapCnt = 1;
        priority[0] = INT_MAX;
        size[0] = 0;
    }
    /**
     * @brief Update the subtree size of the node
     * @param x The node to update
     */
    void update(int x) {
        size[x] = size[childs[x][0]] + cnt[x] + size[childs[x][1]];
    }
    /**
     * @brief Rotate
     * @param x The node to rotate
     * @param t 0 represent left hand, while 1 right hand
     */
    void rotate(int &x, int t) {
        int y = childs[x][t];
        childs[x][t] = childs[y][1 - t];
        childs[y][1 - t] = x;
        // The rotation will only change itself and its son nodes
        update(x);
        update(y);
        x = y;
    }
    /**
     * @brief Insert a value into the specified subtree
     * @param x Insert into the subtree of node x (Usually x=root)
     * @param k key
     */
    void _insert(int &x, int k) {
        if (x) {
            if (key[x] == k) {
                cnt[x]++;
            }  // If the node already exists, the number of copies is ++
            else {
                int t = (key[x] < k);  // Insert according to BST properties
                _insert(childs[x][t], k);
                // After insertion, the heap properties are retained by rotation
                if (priority[childs[x][t]] < priority[x]) {
                    rotate(x, t);
                }
            }
        } else {  // Create a new node
            x = treapCnt++;
            key[x] = k;
            cnt[x] = 1;
            priority[x] = rand();  // Random priority
            childs[x][0] = childs[x][1] = 0;
        }
        update(x);
    }
    /**
     * @brief Erase internal method
     * @param x Erase from the subtree of node x (Usually x=root)
     * @param k key
     */
    void _erase(int &x, int k) {
        if (key[x] == k) {
            if (cnt[x] > 1) {
                cnt[x]--;
            }  // If the node has more than one copy, the number of copies --
            else {
                if (childs[x][0] == 0 && childs[x][1] == 0) {
                    x = 0;
                    return;
                }  // If there are no children, delete and return
                // Otherwise, we need to rotate the sons and delete them
                // recursively
                int t = (priority[childs[x][0]] > priority[childs[x][1]]);
                rotate(x, t);
                _erase(x, k);
            }
        } else {  // Find the target value based on BST properties
            _erase(childs[x][key[x] < k], k);
        }
        update(x);
    }
    /**
     * @brief Find the KTH largest value (Also internal method)
     * @param x Query the subtree of node x (Usually x=root)
     * @param k The queried rank
     * @return The element ranked x
     */
    int _getKth(int &x, int k) {
        if (k <= size[childs[x][0]]) {
            return _get_k_th(childs[x][0], k);
        }
        k -= size[childs[x][0]] + cnt[x];
        if (k <= 0) {
            return key[x];
        }
        return _get_k_th(childs[x][1], k);
    }
    /**
     * @brief Query the rank of specified element (Also internal method)
     * @param x Query the subtree of node x (Usually x=root)
     * @param k The queried element
     * @return The rank of element k
     */
    int _getRank(int x, int k) {
        if (!x)
            return 0;
        if (k == key[x])
            return size[childs[x][0]] + 1;
        else if (k < key[x])
            return _getRank(childs[x][0], k);
        else
            return size[childs[x][0]] + cnt[x] + _getRank(childs[x][1], k);
    }
    /**
     * @brief Get the predecessor node of element k
     * @param k The queried element
     * @return The predecessor
     */
   int get_predecessor(int k) {
        int x = root, pre;
        while (x) {
            if (key[x] < k) {
                pre = key[x], x = childs[x][1];
            } else
                x = childs[x][0];
        }
        return pre;
    }
    /**
     * @brief Get the successor node of element k
     * @param k The queried element
     * @return The successor
     */
    int get_next(int k) {
        int x = root, next;
        while (x) {
            if (key[x] > k) {
                next = key[x], x = childs[x][0];
            } else
                x = childs[x][1];
        }
        return next;
    }
    /**
     * @brief External methods to set opertion object to be the whole tree
     */
    void insert(int k) { _insert(root, k); }
    void erase(int k) { _erase(root, k); }
    int get_k_th(int k) { return _get_k_th(root, k); }
    int getRank(int k) { return _getRank(root, k); }
} mTreap;

// The solution to luogu P3369
// Problem Link: https://www.luogu.com.cn/problem/P3369
void solve() {
    int n;
    std::cin >> n;
    int op, x;
    while (std::cin >> op >> x) {
        switch (op) {
            case 1:
                mTreap.insert(x);
                break;
            case 2:
                mTreap.erase(x);
                break;
            case 3:
                std::cout << mTreap.getRank(x) << '\n';
                break;
            case 4:
                std::cout << mTreap.getKth(x) << '\n';
                break;
            case 5:
                std::cout << mTreap.getPre(x) << '\n';
                break;
            case 6:
                std::cout << mTreap.getNxt(x) << '\n';
                break;
        }
    }
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    solve();
}
