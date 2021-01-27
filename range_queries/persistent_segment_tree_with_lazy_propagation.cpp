#include<iostream>
#include<vector>

// query -> range sum
class perSegTree {
private:
    struct Node {
        Node *left;
        Node *right;
        int64_t val, prop;
        int version;

        Node() {
            left = right = nullptr;
            val = prop = version = 0;
        }
    };

    int n; // number of elements in the segment tree
    std::vector<Node *> ptrs; // ptrs[i] holds a root pointer to the segment tree after the ith update
    std::vector<int> vec;

    Node *newKid(Node *curr) {
        Node *newNode = new Node;
        *newNode = *curr;
        return newNode;
    }
    void lazy(int i, int j, Node *curr) {
        if (!curr->prop) {
            return;
        }
        curr->val += (j - i + 1) * curr->prop;
        if (i != j) {
            curr->left = newKid(curr->left);
            curr->right = newKid(curr->right);
            curr->left->prop += curr->prop;
            curr->right->prop += curr->prop;
            curr->left->version = curr->right->version = curr->version;
        }
        curr->prop = 0;
    }

    void construct(int i, int j, Node *&curr) {
        curr = new Node;
        if (i == j) {
            curr->val = vec[i];
        } else {
            int mid = i + (j - i) / 2;
            construct(i, mid, curr->left);
            construct(mid + 1, j, curr->right);
            curr->val = curr->left->val + curr->right->val;
        }
    }

    Node *update(int i, int j, int l, int r, int value, Node *curr) {
        lazy(i, j, curr);
        if (i >= l && j <= r) {
            Node *newNode = newKid(curr);
            newNode->prop += value;
            newNode->version = ptrs.size();
            lazy(i, j, newNode);
            return newNode;
        }
        if (i > r || j < l) {
            return curr;
        }
        Node *newNode = new Node;
        int mid = i + (j - i) / 2;
        newNode->left = update(i, mid, l, r, value, curr->left);
        newNode->right = update(mid + 1, j, l, r, value, curr->right);
        newNode->val = newNode->left->val + newNode->right->val;
        newNode->version = ptrs.size();
        return newNode;
    }

    int64_t query(int i, int j, int l, int r, Node *curr) {
        lazy(i, j, curr);
        if (j < l || r < i) {
            return 0;
        }
        if (i >= l && j <= r) {
            return curr->val;
        }
        int mid = i + (j - i) / 2;
        return query(i, mid, l, r, curr->left) + query(mid + 1, j, l, r, curr->right);
    }

    /*void clear(Node *&curr, int version) {
        if (!curr || curr->version != version) {
            return;
        }
        clear(curr->left, version);
        clear(curr->right, version);
        delete curr;
    }
    */ // for deallocation , version is passed to delete the current node iff its version = passed version
    // that is, this node was created when the segment tree, whose version = this node's version, was created
    // this is done to delete the segment trees top down version by version
public:
    perSegTree() {
        n = 0;
    }

    void construct(const std::vector<int> vec) // the segment tree will be built from the values in "vec", "vec" is 0 indexed
    {
        if (vec.empty()) {
            return;
        }
        n = vec.size();
        this->vec = vec;
        Node *root = nullptr;
        construct(0, n - 1, root);
        ptrs.push_back(root);
    }

    void update(int l, int r, int value) // all elements from index "l" to index "r" would by updated by "value", "l" and "r" are 0 indexed
    {
        ptrs.push_back(update(0, n - 1, l, r, value,
                              ptrs[ptrs.size() - 1])); // saving the root pointer to the new segment tree
    }

    int64_t query(int l, int r, int version) // querying the range from "l" to "r" in a segment tree after "version" updates, "l" and "r" are 0 indexed
    {
        return query(0, n - 1, l, r, ptrs[version]);
    }

    /*void clear() {
        for (int i = static_cast<int>(ptrs.size()) - 1; i >= 0; --i) {
            clear(ptrs[i],i); // every segment tree clears its nodes (nodes that were created when this segment tree was created)
        }
        while (!ptrs.empty()) {
            ptrs.pop_back();
        }
    }*/

    int size() // returns the number of segment trees (versions) , the number of updates done so far = returned value - 1 ,because one of the trees is the original segment tree
    {
        return ptrs.size();
    }
};

int main() {

    std::vector<int> arr = {-5, 2, 3, 11, -2, 7, 0, 1};
    perSegTree tree;
    std::cout << "Elements before any updates are {";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    tree.construct(arr); // constructing the original segment tree (version = 0)
    std::cout << "Querying range sum on version 0 from index 2 to 4 = 3+11-2 = " << tree.query(2, 4, 0) << '\n';
    std::cout << "Subtract 7 from all elements from index 1 to index 5 inclusive\n";
    tree.update(1, 5, -7); // subtracting 7 from index 1 to index 5
    std::cout << "Elements of the segment tree whose version = 1 (after 1 update) are {";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << tree.query(i, i, 1);
        if (i != arr.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    std::cout << "Add 10 to all elements from index 0 to index 7 inclusive\n";
    tree.update(0, 7, 10); // adding 10 to all elements
    std::cout << "Elements of the segment tree whose version = 2 (after 2 updates) are {";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << tree.query(i, i, 2);
        if (i != arr.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    std::cout << "Number of segment trees (versions) now = " << tree.size() << '\n';
    std::cout << "Querying range sum on version 0 from index 3 to 5 = 11-2+7 = " << tree.query(3, 5, 0) << '\n';
    std::cout << "Querying range sum on version 1 from index 3 to 5 = 4-9+0 = " << tree.query(3, 5, 1) << '\n';
    return 0;
}