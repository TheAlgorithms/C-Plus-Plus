/**
 * @file
 * @brief A demo 2-3-4 tree implementation
 * @details
 * 2–3–4 tree is a self-balancing data structure that is an isometry of
 * red–black trees. Though we seldom use them in practice, we study them
 * to understand the theory behind Red-Black tree. Please read following
 * links for more infomation.
 * [2–3–4 tree](https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree)
 * [2-3-4 Trees: A Visual
Introduction](https://www.educative.io/page/5689413791121408/80001)
 * We Only implement some basic and complicated operations in this demo.
 * Other operations should be easy to be added.
 * @author [liuhuan](https://github.com/fedom)
 */
#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <fstream>   /// for std::ofstream
#include <iostream>  /// for std::cout
#include <memory>    /// for std::unique_ptr
#include <queue>     /// for std::queue
#include <string>    /// for std::to_string

/**
 * @namespace data_structures
 * @brief Algorithms with data structures
 */
namespace data_structures {
/**
 * @namespace tree_234
 * @brief Functions for [2–3–4 tree](https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree)
 */
namespace tree_234 {
/** @brief 2-3-4 tree node class */
class Node {
 public:
    /**
     * @brief Node constructor
     * @param item the first value we insert to the node
     */
    explicit Node(int64_t item)
        : count(1),
          items({{item, 0, 0}}),
          children({{nullptr, nullptr, nullptr, nullptr}}) {}

    /**
     * @brief Get the item count that current saved in the node
     * @return item count
     */
    int8_t GetCount() { return count; }

    /**
     * @brief Set the item count of the node
     *
     * This is only used when we spliting and merging node where we need to do
     * some raw operation manually. In common inserting and removing operation
     * the count is maintained automatically.
     *
     * @param c the count to set
     */
    void SetCount(int8_t c) { count = c; }

    /**
     * @brief Check if node is a leaf
     * @return true if node is leaf, false otherwise
     */
    bool IsLeaf() { return children[0] == nullptr; }

    /**
     * @brief Check if node is a full (4-node)
     * @return true if node is full (4-node), false otherwise
     */
    bool IsFull() { return count == 3; }

    /**
     * @brief Check if node is a 2-node
     * @return true if node is 2-node, otherwise false
     */
    bool Is2Node() { return count == 1; }

    /** @brief Check if node is a 3-node or 4-node, this is useful when we
     * delete item from 2-3-4 tree
     * @return true if node is 3-node or 4-node, false otherwise
     */
    bool Is34Node() { return count == 2 || count == 3; }

    /**
     * @brief Check if item is in the node
     * @param item item to check
     * @return true if item in the node, otherwise false
     */
    bool Contains(int64_t item) {
        for (int8_t i = 0; i < count; i++) {
            if (item == items[i]) {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Get the index of the item in the node, 0-based
     * @param item item to check
     * @return 0-based index of the item in the node, if not in the node, -1 is
     * returned
     */
    int8_t GetItemIndex(int64_t item) {
        for (int8_t i = 0; i < count; i++) {
            if (items[i] == item) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief Get max item (rightmost) in the current node
     * @return max item
     */
    int64_t GetMaxItem() { return items[count - 1]; }

    /**
     * @brief get min item (leftmost) in the current node
     * @return min item
     */
    int64_t GetMinItem() { return items[0]; }

    /**
     * @brief Get item of the \index index
     * @param index the item index to get
     * @return the item
     */
    int64_t GetItem(int8_t index) { return items[index]; }

    /**
     * @brief Set item value at position of index
     * @param index the index of the item to set
     * @param new_item item value
     */
    void SetItem(int8_t index, int64_t new_item) {
        assert(index >= 0 && index <= 2);

        items[index] = new_item;
    }

    /**
     * @brief Insert item to the proper position of the node and return the
     * position index.
     *
     * This is a helper function we use during insertion. Please mind that when
     * insert a item, we aslo need to take care of two child pointers. One is
     * the original child pointer at the insertion position. It can be placed as
     * new item's either left child or right child. And the other is the new
     * child that should be added. For our dedicated situation here, we choose
     * to use the original child as the new item's left child, and add a null
     * pointer to its right child. So after use the function, please update
     * these two children pointer manually.
     *
     * @param item value to be inserted to the node
     * @return index where item is inserted, caller can use this
     * index to update its left and right child
     */
    int InsertItem(int item) {
        assert(!IsFull());

        if (Contains(item)) {
            return -1;
        }

        int8_t i = 0;
        for (i = 0; i < count; i++) {
            if (items[i] > item) {
                break;
            }
        }

        InsertItemByIndex(i, item, nullptr, true);
        return i;
    }

    /**
     * @brief Insert a value to the index position
     * @param index index where to insert item
     * @param item  value to insert
     * @param with_child new added child pointer
     * @param to_left true indicate adding with_child to new item's left child,
     * otherwise to right child
     */
    void InsertItemByIndex(int8_t index, int64_t item, Node *with_child,
                           bool to_left = true) {
        assert(count < 3 && index >= 0 && index < 3);

        for (int8_t i = count - 1; i >= index; i--) {
            items[i + 1] = items[i];
        }

        items[index] = item;

        int8_t start_index = to_left ? index : index + 1;

        for (int8_t i = count; i >= start_index; i--) {
            children[i + 1] = children[i];
        }

        children[start_index] = with_child;

        count++;
    }

    /**
     * @brief Insert a value to the index position
     * @param index index of the item to remove
     * @param keep_left which child of the item to keep, true keep the left
     * child, false keep the right child
     * @return the removed child pointer
     */
    Node *RemoveItemByIndex(int8_t index, bool keep_left) {
        assert(index >= 0 && index < count);
        Node *removed_child = keep_left ? children[index + 1] : children[index];
        for (int8_t i = index; i < count - 1; i++) {
            items[i] = items[i + 1];
        }

        for (int8_t i = keep_left ? index + 1 : index; i < count; i++) {
            children[i] = children[i + 1];
        }

        count--;
        return removed_child;
    }

    /**
     * @brief Get the child's index of the children array
     * @param child child pointer of which to get the index
     * @return the index of child
     */
    int8_t GetChildIndex(Node *child) {
        for (int8_t i = 0; i < count + 1; i++) {
            if (children[i] == child) {
                return i;
            }
        }

        return -1;
    }

    /**
     * @brief Get the child pointer at position of index
     * @param index index of child to get
     * @return the child pointer
     */
    Node *GetChild(int8_t index) { return children[index]; }

    /**
     * @brief Set child pointer to the position of index
     * @param index children index
     * @param child pointer to set
     */
    void SetChild(int8_t index, Node *child) { children[index] = child; }

    /**
     * @brief Get rightmose child of the current node
     * @return the rightmost child
     */
    Node *GetRightmostChild() { return children[count]; }

    /**
     * @brief Get leftmose child of the current node
     * @return the leftmost child
     */
    Node *GetLeftmostChild() { return children[0]; }

    /**
     * @brief Get left child of item at item_index
     * @param item_index  index of the item whose left child to be get
     * @return left child of items[index]'s
     */
    Node *GetItemLeftChild(int8_t item_index) {
        if (item_index < 0 || item_index > count - 1) {
            return nullptr;
        }

        return children[item_index];
    }

    /**
     * @brief Get right child of item at item_index
     * @param item_index  index of the item whose right child to be get
     * @return right child of items[index]'s
     */
    Node *GetItemRightChild(int8_t item_index) {
        if (item_index < 0 || item_index > count - 1) {
            return nullptr;
        }

        return children[item_index + 1];
    }

    /**
     * @brief Get next node which is possibly contains item
     * @param item item to search
     * @return the next node that possibly contains item
     */
    Node *GetNextPossibleChild(int64_t item) {
        int i = 0;
        for (i = 0; i < count; i++) {
            if (items[i] > item) {
                break;
            }
        }
        return children[i];
    }

 private:
    std::array<int64_t, 3> items;  ///< store items

    std::array<Node *, 4> children;  ///< store the children pointers

    int8_t count = 0;  ///< track the current item count
};

/** @brief 2-3-4 tree class */
class Tree234 {
 public:
    Tree234() = default;
    Tree234(const Tree234 &) = delete;
    Tree234(const Tree234 &&) = delete;
    Tree234 &operator=(const Tree234 &) = delete;
    Tree234 &operator=(const Tree234 &&) = delete;

    ~Tree234();

    /**
     * @brief Insert item to tree
     * @param item item to insert
     */
    void Insert(int64_t item);

    /**
     * @brief Remove item from tree
     * @param item item to remove
     * @return true if item found and removed, false otherwise
     */
    bool Remove(int64_t item);

    /** @brief In-order traverse */
    void Traverse();

    /**
     * @brief Print tree into a dot file
     * @param file_name output file name, if nullptr then use "out.dot" as
     * default
     */
    void Print(const char *file_name = nullptr);

 private:
    /**
     * @brief A insert implementation of pre-split
     * @param item item to insert
     */
    void InsertPreSplit(int64_t item);

    /**
     * @brief A insert implementation of post-merge
     * @param item item to insert
     */
    void InsertPostMerge(int64_t item);

    /**
     * @brief A helper function used by post-merge insert
     * @param tree tree where to insert item
     * @param item item to insert
     * @return the node that split as the parent when overflow happen
     */
    Node *Insert(Node *tree, int64_t item);

    /**
     * @brief A helper function used during post-merge insert
     *
     * When the inserting leads to overflow, it will split the node to 1 parent
     * and 2 children. The parent will be merged to its origin parent after
     * that. This is the function to complete this task. So the param node is
     * always a 2-node.
     *
     * @param dst_node the target node we will merge node to, can be type of
     * 2-node, 3-node or 4-node
     * @param node the source node we will merge from, type must be 2-node
     * @return overflow node of this level
     */
    Node *MergeNode(Node *dst_node, Node *node);

    /**
     * @brief Merge node to a not-full target node
     *
     * Since the target node is not-full, no overflow will happen. So we have
     * nothing to return.
     *
     * @param dst_node the target not-full node, that is the type is either
     * 2-node or 3-node, but not 4-node
     * @param node the source node we will merge from, type must be 2-node
     */
    void MergeNodeNotFull(Node *dst_node, Node *node);

    /**
     * @brief Split a 4-node to 1 parent and 2 children, and return the parent
     * node
     * @param node the node to split, it must be a 4-node
     * @return split parent node
     */
    Node *SplitNode(Node *node);

    /**
     * @brief Get the max item of the tree
     * @param tree the tree we will get item from
     * @return max item of the tree
     */
    int64_t GetTreeMaxItem(Node *tree);

    /**
     * @brief Get the min item of the tree
     * @param tree the tree we will get item from
     * @return min item of the tree
     */
    int64_t GetTreeMinItem(Node *tree);

    /**
     * @brief A handy function to try if we can do a left rotate to the target
     * node
     *
     * Given two node, the parent and the target child, the left rotate
     * operation is uniquely identified. The source node must be the right
     * sibling of the target child. The operation can be successfully done if
     * the to_child has a right sibling and its right sibling is not 2-node.
     *
     * @param parent the parent node in this left rotate operation
     * @param to_child the target child of this left rotate operation. In our
     * case, this node is always 2-node
     * @return true if we successfully do the rotate. false if the
     * requirements are not fulfilled.
     */
    bool TryLeftRotate(Node *parent, Node *to_child);

    /**
     * @brief A handy function to try if we can do a right rotate to the target
     * node
     *
     * Given two node, the parent and the target child, the right rotate
     * operation is uniquely identified. The source node must be the left
     * sibling of the target child. The operation can be successfully done if
     * the to_child has a left sibling and its left sibling is not 2-node.
     *
     * @param parent the parent node in this right rotate operation
     * @param to_child the target child of this right rotate operation. In our
     * case, it is always 2-node
     * @return true if we successfully do the rotate. false if the
     * requirements are not fulfilled.
     */
    bool TryRightRotate(Node *parent, Node *to_child);

    /**
     * @brief Do the actual right rotate operation
     *
     * Given parent node, and the pivot item index, the right rotate operation
     * is uniquely identified. The function assume the requirements are
     * fulfilled and won't do any extra check. This function is call by
     * TryRightRotate(), and the condition checking should be done before call
     * it.
     *
     * @param parent the parent node in this right rotate operation
     * @param index the pivot item index of this right rotate operation.
     */
    void RightRotate(Node *parent, int8_t index);

    /**
     * @brief Do the actual left rotate operation
     *
     * Given parent node, and the pivot item index, the left rotate operation is
     * uniquely identified. The function assume the requirements are fulfilled
     * and won't do any extra check. This function is call by TryLeftRotate(),
     * and the condition checking should be done before call it.
     *
     * @param parent the parent node in this right rotate operation
     * @param index the pivot item index of this right rotate operation.
     */
    void LeftRotate(Node *parent, int8_t index);

    /**
     * @brief Main function implement the pre-merge remove operation
     * @param node the tree to remove item from
     * @param item item to remove
     * @return true if remove success, false otherwise
     * */
    bool RemovePreMerge(Node *node, int64_t item);

    /**
     * @brief Merge the item at index of the parent node, and its left and right
     * child
     *
     * the left and right child node must be 2-node. The 3 items will be merged
     * into a 4-node. In our case the parent can be a 2-node iff it is the root.
     * Otherwise, it must be 3-node or 4-node.
     *
     * @param parent the parent node in the merging operation
     * @param index the item index of the parent node that involved in the
     * merging
     * @return the merged 4-node
     */
    Node *Merge(Node *parent, int8_t index);

    /**
     * @brief Recursive release the tree
     * @param tree root node of the tree to delete
     */
    void DeleteNode(Node *tree);

    /**
     * @brief In-order traverse the tree, print items
     * @param tree tree to traverse
     */
    void Traverse(Node *tree);

    /**
     * @brief Print the tree to a dot file. You can convert it to picture with
     * graphviz
     * @param ofs output file stream to print to
     * @param node current node to print
     * @param parent_index current node's parent node index, this is used to
     * draw the link from parent to current node
     * @param index current node's index of level order which is used to name
     * the node in dot file
     * @param parent_child_index the index that current node in parent's
     * children array, range in [0,4), help to locate the start position of the
     * link between nodes
     */
    void PrintNode(std::ofstream &ofs, Node *node, int64_t parent_index,
                   int64_t index, int8_t parent_child_index);

    Node *root_{nullptr};  ///< root node of the tree
};

Tree234::~Tree234() { DeleteNode(root_); }

/**
 * @brief Recursive release the tree
 * @param tree root node of the tree to delete
 */
void Tree234::DeleteNode(Node *tree) {
    if (!tree) {
        return;
    }
    for (int8_t i = 0; i <= tree->GetCount(); i++) {
        DeleteNode(tree->GetChild(i));
    }

    delete tree;
}

/**
 * @brief In-order traverse the tree, print items
 * @param tree tree to traverse
 */
void Tree234::Traverse() {
    Traverse(root_);
    std::cout << std::endl;
}

void Tree234::Traverse(Node *node) {
    if (!node) {
        return;
    }

    int8_t i = 0;
    for (i = 0; i < node->GetCount(); i++) {
        Traverse(node->GetChild(i));
        std::cout << node->GetItem(i) << ", ";
    }

    Traverse(node->GetChild(i));
}

/**
 * @brief A insert implementation of pre-split
 * @param item item to insert
 */
void Tree234::InsertPreSplit(int64_t item) {
    if (!root_) {
        root_ = new Node(item);
        return;
    }

    Node *parent = nullptr;
    Node *node = root_;

    while (true) {
        if (!node) {
            std::unique_ptr<Node> tmp(new Node(item));
            MergeNodeNotFull(parent, tmp.get());
            return;
        }

        if (node->Contains(item)) {
            return;
        }

        if (node->IsFull()) {
            node = SplitNode(node);

            Node *cur_node = nullptr;

            if (item < node->GetItem(0)) {
                cur_node = node->GetChild(0);
            } else {
                cur_node = node->GetChild(1);
            }

            if (!parent) {
                // for the root node parent is nullptr, we simply assign the
                // split parent to root_
                root_ = node;
            } else {
                // merge the split parent to its origin parent
                MergeNodeNotFull(parent, node);
            }

            node = cur_node;
        }

        parent = node;
        node = parent->GetNextPossibleChild(item);
    }
}

/**
 * @brief A insert implementation of post-merge
 * @param item item to insert
 */
void Tree234::InsertPostMerge(int64_t item) {
    if (!root_) {
        root_ = new Node(item);
        return;
    }

    Node *split_node = Insert(root_, item);

    // if root has split, then update root_
    if (split_node) {
        root_ = split_node;
    }
}

/**
 * @brief Insert item to tree
 * @param item item to insert
 */
void Tree234::Insert(int64_t item) { InsertPreSplit(item); }

/**
 * @brief A helper function used by post-merge insert
 * @param tree tree where to insert item
 * @param item item to insert
 * @return the node that split as the parent when overflow happen
 */
Node *Tree234::Insert(Node *tree, int64_t item) {
    assert(tree != nullptr);

    std::unique_ptr<Node> split_node;

    if (tree->Contains(item)) {
        // return nullptr indicate current node not overflow
        return nullptr;
    }

    Node *next_node = tree->GetNextPossibleChild(item);
    if (next_node) {
        split_node.reset(Insert(next_node, item));
    } else {
        split_node.reset(new Node(item));
    }

    if (split_node) {
        return MergeNode(tree, split_node.get());
    }

    return nullptr;
}

/**
 * @brief A helper function used during post-merge insert
 *
 * When the inserting leads to overflow, it will split the node to 1 parent
 * and 2 children. The parent will be merged to its origin parent after
 * that. This is the function to complete this task. So the param node is
 * always a 2-node.
 *
 * @param dst_node the target node we will merge node to, can be type of
 * 2-node, 3-node or 4-node
 * @param node the source node we will merge from, type must be 2-node
 * @return overflow node of this level
 */
Node *Tree234::MergeNode(Node *dst_node, Node *node) {
    assert(dst_node != nullptr && node != nullptr);

    if (!dst_node->IsFull()) {
        MergeNodeNotFull(dst_node, node);
        return nullptr;
    }

    dst_node = SplitNode(dst_node);

    if (node->GetItem(0) < dst_node->GetItem(0)) {
        MergeNodeNotFull(dst_node->GetChild(0), node);

    } else {
        MergeNodeNotFull(dst_node->GetChild(1), node);
    }

    return dst_node;
}

/**
 * @brief Merge node to a not-full target node
 *
 * Since the target node is not-full, no overflow will happen. So we have
 * nothing to return.
 *
 * @param dst_node the target not-full node, that is the type is either
 * 2-node or 3-node, but not 4-node
 * @param node the source node we will merge from, type must be 2-node
 */
void Tree234::MergeNodeNotFull(Node *dst_node, Node *node) {
    assert(dst_node && node && !dst_node->IsFull() && node->Is2Node());

    int8_t i = dst_node->InsertItem(node->GetItem(0));

    dst_node->SetChild(i, node->GetChild(0));
    dst_node->SetChild(i + 1, node->GetChild(1));
}

/**
 * @brief Split a 4-node to 1 parent and 2 children, and return the parent
 * node
 * @param node the node to split, it must be a 4-node
 * @return split parent node
 */
Node *Tree234::SplitNode(Node *node) {
    assert(node->GetCount() == 3);

    Node *left = node;

    Node *right = new Node(node->GetItem(2));
    right->SetChild(0, node->GetChild(2));
    right->SetChild(1, node->GetChild(3));

    Node *parent = new Node(node->GetItem(1));
    parent->SetChild(0, left);
    parent->SetChild(1, right);

    left->SetCount(1);

    return parent;
}

/**
 * @brief A handy function to try if we can do a left rotate to the target
 * node
 *
 * Given two node, the parent and the target child, the left rotate
 * operation is uniquely identified. The source node must be the right
 * sibling of the target child. The operation can be successfully done if
 * the to_child has a right sibling and its right sibling is not 2-node.
 *
 * @param parent the parent node in this left rotate operation
 * @param to_child the target child of this left rotate operation. In our
 * case, this node is always 2-node
 * @return true if we successfully do the rotate. false if the
 * requirements are not fulfilled.
 */
bool Tree234::TryLeftRotate(Node *parent, Node *to_child) {
    int to_child_index = parent->GetChildIndex(to_child);

    // child is right most, can not do left rotate to it
    if (to_child_index >= parent->GetCount()) {
        return false;
    }

    Node *right_sibling = parent->GetChild(to_child_index + 1);

    // right sibling is 2-node. can not do left rotate.
    if (right_sibling->Is2Node()) {
        return false;
    }

    LeftRotate(parent, to_child_index);

    return true;
}

/**
 * @brief A handy function to try if we can do a right rotate to the target
 * node
 *
 * Given two node, the parent and the target child, the right rotate
 * operation is uniquely identified. The source node must be the left
 * sibling of the target child. The operation can be successfully done if
 * the to_child has a left sibling and its left sibling is not 2-node.
 *
 * @param parent the parent node in this right rotate operation
 * @param to_child the target child of this right rotate operation. In our
 * case, it is always 2-node
 * @return true if we successfully do the rotate. false if the
 * requirements are not fulfilled.
 */
bool Tree234::TryRightRotate(Node *parent, Node *to_child) {
    int8_t to_child_index = parent->GetChildIndex(to_child);

    // child is left most, can not do right rotate to it
    if (to_child_index <= 0) {
        return false;
    }

    Node *left_sibling = parent->GetChild(to_child_index - 1);

    // right sibling is 2-node. can not do left rotate.
    if (left_sibling->Is2Node()) {
        return false;
    }

    RightRotate(parent, to_child_index - 1);

    return true;
}

/**
 * @brief Do the actual right rotate operation
 *
 * Given parent node, and the pivot item index, the right rotate operation
 * is uniquely identified. The function assume the requirements are
 * fulfilled and won't do any extra check. This function is call by
 * TryRightRotate(), and the condition checking should be done before call
 * it.
 *
 * @param parent the parent node in this right rotate operation
 * @param index the pivot item index of this right rotate operation.
 */
void Tree234::RightRotate(Node *parent, int8_t index) {
    Node *left = parent->GetItemLeftChild(index);
    Node *right = parent->GetItemRightChild(index);

    assert(left && left->Is34Node());
    assert(right && right->Is2Node());

    right->InsertItemByIndex(0, parent->GetItem(index),
                             left->GetRightmostChild(), true);
    parent->SetItem(index, left->GetMaxItem());
    left->RemoveItemByIndex(left->GetCount() - 1, true);
}

/**
 * @brief Do the actual left rotate operation
 *
 * Given parent node, and the pivot item index, the left rotate operation is
 * uniquely identified. The function assume the requirements are fulfilled
 * and won't do any extra check. This function is call by TryLeftRotate(),
 * and the condition checking should be done before call it.
 *
 * @param parent the parent node in this right rotate operation
 * @param index the pivot item index of this right rotate operation.
 */
void Tree234::LeftRotate(Node *parent, int8_t index) {
    Node *left = parent->GetItemLeftChild(index);
    Node *right = parent->GetItemRightChild(index);

    assert(right && right->Is34Node());
    assert(left && left->Is2Node());

    left->InsertItemByIndex(left->GetCount(), parent->GetItem(index),
                            right->GetLeftmostChild(), false);
    parent->SetItem(index, right->GetMinItem());
    right->RemoveItemByIndex(0, false);
}

/**
 * @brief Merge the item at index of the parent node, and its left and right
 * child
 *
 * the left and right child node must be 2-node. The 3 items will be merged
 * into a 4-node. In our case the parent can be a 2-node iff it is the root.
 * Otherwise, it must be 3-node or 4-node.
 *
 * @param parent the parent node in the merging operation
 * @param index the item index of the parent node that involved in the
 * merging
 * @return the merged 4-node
 */
Node *Tree234::Merge(Node *parent, int8_t index) {
    assert(parent);

    // bool is_parent_2node = parent->Is2Node();

    Node *left_child = parent->GetItemLeftChild(index);
    Node *right_child = parent->GetItemRightChild(index);

    assert(left_child->Is2Node() && right_child->Is2Node());

    int64_t item = parent->GetItem(index);

    // 1. merge parent's item and right child to left child
    left_child->SetItem(1, item);
    left_child->SetItem(2, right_child->GetItem(0));
    left_child->SetChild(2, right_child->GetChild(0));
    left_child->SetChild(3, right_child->GetChild(1));

    left_child->SetCount(3);

    // 2. remove the parent's item
    parent->RemoveItemByIndex(index, true);

    // 3. delete the unused right child
    delete right_child;

    return left_child;
}

/**
 * @brief Remove item from tree
 * @param item item to remove
 * @return true if item found and removed, false otherwise
 */
bool Tree234::Remove(int64_t item) { return RemovePreMerge(root_, item); }

/**
 * @brief Main function implement the pre-merge remove operation
 * @param node the tree to remove item from
 * @param item item to remove
 * @return true if remove success, false otherwise
 */
bool Tree234::RemovePreMerge(Node *node, int64_t item) {
    while (node) {
        if (node->IsLeaf()) {
            if (node->Contains(item)) {
                if (node->Is2Node()) {
                    // node must be root
                    delete node;
                    root_ = nullptr;
                } else {
                    node->RemoveItemByIndex(node->GetItemIndex(item), true);
                }
                return true;
            }
            return false;
        }

        // node is internal
        if (node->Contains(item)) {
            int8_t index = node->GetItemIndex(item);

            // Here is important!!! What we do next depend on its children's
            // state. Why?
            Node *left_child = node->GetItemLeftChild(index);
            Node *right_child = node->GetItemRightChild(index);
            assert(left_child && right_child);

            if (left_child->Is2Node() && right_child->Is2Node()) {
                // both left and right child are 2-node,we should not modify
                // current node in this situation. Because we are going to do
                // merge with its children which will move target item to next
                // layer. so if we replace the item with successor or
                // predecessor now, when we do the recursive remove with
                // successor or predecessor, we will result in removing the just
                // replaced one in the merged node. That's not what we want.

                // we need to convert the child 2-node to 3-node or 4-node
                // first. First we try to see if any of them can convert to
                // 3-node by rotate. By using rotate we keep the empty house for
                // the future insertion which will be more efficient than merge.
                //
                //            | ? | node | ? |
                //           /    |      |    \
                //          /     |      |     \
                //         /      |      |      \
                //        /       |      |       \
                //       /        |      |        \
                //      /         |      |         \
                //     ?  left_child  right_child   ?
                //

                // node must be the root
                if (node->Is2Node()) {
                    // this means we can't avoid merging the target item into
                    // next layer, and this will cause us do different process
                    // compared with other cases
                    Node *new_root = Merge(node, index);
                    delete root_;
                    root_ = new_root;
                    node = root_;

                    // now node point to the
                    continue;
                }

                // here means we can avoid merging the target item into next
                // layer. So we convert one of its left or right child to 3-node
                // and then do the successor or predecessor swap and recursive
                // remove the next layer will successor or predecessor.
                do {
                    if (index > 0) {
                        // left_child has left-sibling, we check if we can do a
                        // rotate
                        Node *left_sibling = node->GetItemLeftChild(index - 1);
                        if (left_sibling->Is34Node()) {
                            RightRotate(node, index - 1);
                            break;
                        }
                    }

                    if (index < node->GetCount() - 1) {
                        // right_child has right-sibling, we check if we can do
                        // a rotate
                        Node *right_sibling =
                            node->GetItemRightChild(index + 1);
                        if (right_sibling->Is34Node()) {
                            LeftRotate(node, index + 1);
                            break;
                        }
                    }

                    // we do a merge. We avoid merging the target item, which
                    // may trigger another merge in the recursion process.
                    if (index > 0) {
                        Merge(node, index - 1);
                        break;
                    }

                    Merge(node, index + 1);

                } while (false);
            }

            // refresh the left_child and right_child since they may be invalid
            // because of merge
            left_child = node->GetItemLeftChild(index);
            right_child = node->GetItemRightChild(index);

            if (left_child->Is34Node()) {
                int64_t predecessor_item = GetTreeMaxItem(left_child);
                node->SetItem(node->GetItemIndex(item), predecessor_item);

                node = left_child;
                item = predecessor_item;
                continue;
            }

            if (right_child->Is34Node()) {
                int64_t successor_item = GetTreeMinItem(right_child);
                node->SetItem(node->GetItemIndex(item), successor_item);
                node = right_child;
                item = successor_item;
                continue;
            }
        }

        Node *next_node = node->GetNextPossibleChild(item);

        if (next_node->Is34Node()) {
            node = next_node;
            continue;
        }

        if (TryRightRotate(node, next_node)) {
            node = next_node;
            continue;
        }

        if (TryLeftRotate(node, next_node)) {
            node = next_node;
            continue;
        }

        // get here means both left sibling and right sibling of next_node is
        // 2-node, so we do merge
        int8_t child_index = node->GetChildIndex(next_node);
        if (child_index > 0) {
            node = Merge(node, child_index - 1);
        } else {
            node = Merge(node, child_index);
        }

    }  // while

    return false;
}

/**
 * @brief Get the max item of the tree
 * @param tree the tree we will get item from
 * @return max item of the tree
 */
int64_t Tree234::GetTreeMaxItem(Node *tree) {
    assert(tree);
    int64_t max = 0;

    while (tree) {
        max = tree->GetMaxItem();
        tree = tree->GetRightmostChild();
    }

    return max;
}

/**
 * @brief Get the min item of the tree
 * @param tree the tree we will get item from
 * @return min item of the tree
 */
int64_t Tree234::GetTreeMinItem(Node *tree) {
    assert(tree);
    int64_t min = 0;

    while (tree) {
        min = tree->GetMinItem();
        tree = tree->GetLeftmostChild();
    }

    return min;
}

/**
 * @brief Print tree into a dot file
 * @param file_name output file name, if nullptr then use "out.dot" as default
 */
void Tree234::Print(const char *file_name) {
    if (!file_name) {
        file_name = "out.dot";
    }

    std::ofstream ofs;

    ofs.open(file_name);
    if (!ofs) {
        std::cout << "create tree dot file failed, " << file_name << std::endl;
        return;
    }

    ofs << "digraph G {\n";
    ofs << "node [shape=record]\n";

    int64_t index = 0;

    /** @brief This is a helper structure to do a level order traversal to print
     * the tree. */
    struct NodeInfo {
        Node *node;     ///< tree node
        int64_t index;  ///< node index of level order that used when draw the
                        ///< link between child and parent
    };

    std::queue<NodeInfo> q;

    if (root_) {
        // print root node
        PrintNode(ofs, root_, -1, index, 0);

        NodeInfo ni{};
        ni.node = root_;
        ni.index = index;

        q.push(ni);

        while (!q.empty()) {
            NodeInfo node_info = q.front();
            q.pop();

            assert(node_info.node->GetCount() > 0);

            if (!node_info.node->IsLeaf()) {
                if (node_info.node->GetCount() > 0) {
                    PrintNode(ofs, node_info.node->GetChild(0), node_info.index,
                              ++index, 0);
                    ni.node = node_info.node->GetChild(0);
                    ni.index = index;
                    q.push(ni);

                    PrintNode(ofs, node_info.node->GetChild(1), node_info.index,
                              ++index, 1);
                    ni.node = node_info.node->GetChild(1);
                    ni.index = index;
                    q.push(ni);
                }

                if (node_info.node->GetCount() > 1) {
                    PrintNode(ofs, node_info.node->GetChild(2), node_info.index,
                              ++index, 2);
                    ni.node = node_info.node->GetChild(2);
                    ni.index = index;
                    q.push(ni);
                }

                if (node_info.node->GetCount() > 2) {
                    PrintNode(ofs, node_info.node->GetChild(3), node_info.index,
                              ++index, 3);
                    ni.node = node_info.node->GetChild(3);
                    ni.index = index;
                    q.push(ni);
                }
            }
        }
    }

    ofs << "}\n";
    ofs.close();
}

/**
 * @brief Print the tree to a dot file. You can convert it to picture with
 * graphviz
 * @param ofs output file stream to print to
 * @param node current node to print
 * @param parent_index current node's parent node index, this is used to draw
 * the link from parent to current node
 * @param index current node's index of level order which is used to name the
 * node in dot file
 * @param parent_child_index the index that current node in parent's children
 * array, range in [0,4), help to locate the start position of the link between
 * nodes
 */
void Tree234::PrintNode(std::ofstream &ofs, Node *node, int64_t parent_index,
                        int64_t index, int8_t parent_child_index) {
    assert(node);

    switch (node->GetCount()) {
        case 1:
            ofs << "node_" << index << " [label=\"<f0> " << node->GetItem(0)
                << "\"]\n";
            break;
        case 2:
            ofs << "node_" << index << " [label=\"<f0> " << node->GetItem(0)
                << " | <f1> " << node->GetItem(1) << "\"]\n";
            break;
        case 3:
            ofs << "node_" << index << " [label=\"<f0> " << node->GetItem(0)
                << " | <f1> " << node->GetItem(1) << "| <f2> "
                << node->GetItem(2) << "\"]\n";
            break;

        default:
            break;
    }

    // draw the edge
    if (parent_index >= 0) {
        ofs << "node_" << parent_index << ":f"
            << (parent_child_index == 0 ? 0 : parent_child_index - 1) << ":"
            << (parent_child_index == 0 ? "sw" : "se") << " -> node_" << index
            << "\n";
    }
}
}  // namespace tree_234
}  // namespace data_structures


/** @brief simple test to insert a given array and delete some item, and print
 * the tree*/
static void test1() {
    std::array<int16_t, 13> arr = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6, 16, 13, 14};
    data_structures::tree_234::Tree234 tree;

    for (auto i : arr) {
        tree.Insert(i);
    }

    // tree.Remove(10);
    tree.Remove(5);
    tree.Print();
}

/**
 * @brief simple test to insert continuous number of range [0, n), and print
 * the tree
 * @param n upper bound of the range number to insert
 */
static void test2(int64_t n) {
    data_structures::tree_234::Tree234 tree;

    for (int64_t i = 0; i < n; i++) {
        tree.Insert(i);
    }

    tree.Traverse();
    tree.Print((std::to_string(n) + ".dot").c_str());
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        test1();  // execute 1st test
    } else {
        test2(std::stoi(argv[1]));  // execute 2nd test
    }

    return 0;
}
