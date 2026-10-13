/**
 * @file avltree.cpp
 * @author Bertrand Awenze (https://github.com/bertrand-awz)
 * @brief Implementation and self-tests of an AVL Tree data structure.
 *
 * @details This implementation is a self-balancing binary search tree that
 * maintains its height to be logarithmic in the number of nodes, ensuring
 * efficient operations. The AVL Tree supports insertion, deletion, and
 * search operations in O(log n) time. It automatically balances itself after
 * insertions and deletions to maintain optimal performance. The tree can be
 * displayed in a structured format in terminal, and it provides methods to
 * check for emptiness, size, and height.
 *
 * @note This implementation resolves the issue mentioned in the following
 * link: https://thealgorithms.github.io/C-Plus-Plus/d8/dee/avltree_8cpp.html
 *
 * @note This implementation uses C++17 features and requires the type T to be
 * comparable (i.e., support == and < operators).
 *
 * @version 0.1
 * @date 2026-09-14
 *
 * @copyright MIT License (c) 2026
 *
 */

// Keep assertions active when this executable is built in Release mode.
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace avltree_requirements {

template <typename T, typename = void>
struct IsComparable : std::false_type {};

template <typename T>
struct IsComparable<
    T, std::void_t<decltype(static_cast<bool>(std::declval<const T&>() ==
                                            std::declval<const T&>())),
                   decltype(static_cast<bool>(std::declval<const T&>() <
                                            std::declval<const T&>()))>>
    : std::conjunction<std::is_convertible<decltype(std::declval<const T&>() ==
                                                  std::declval<const T&>()),
                                          bool>,
                       std::is_convertible<decltype(std::declval<const T&>() <
                                                  std::declval<const T&>()),
                                           bool>> {};

}  // namespace avltree_requirements

template <typename T>
inline constexpr bool Comparable = avltree_requirements::IsComparable<T>::value;

template <typename T>
/**
 * @brief AVL Tree implementation
 * @requires T to be comparable (i.e., support == and < operators)
 *
 */
// Copy-and-swap assignment handles both copy and move assignment.
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class AvlTree {
    static_assert(Comparable<T>,
                  "AvlTree<T> requires == and < on const T&, with results "
                  "convertible to bool");

 public:
    /**
     * @brief Construct a new Avl Tree object
     *
     */
    AvlTree() = default;

    /**
     * @brief Construct a new Avl Tree object by initializing it with a list of
     * items
     *
     * @param items
     */
    AvlTree(std::initializer_list<T> items);

    /**
     * @brief Construct a new Avl Tree object by copying another AvlTree
     *
     * @param other
     */
    AvlTree(const AvlTree& other);

    /**
     * @brief Construct a new Avl Tree object by moving another AvlTree
     *
     * @param other
     */
    AvlTree(AvlTree&& other) noexcept;

    /**
     * @brief Assign the contents of another AvlTree to this one
     *
     * @param other
     * @return AvlTree&
     */
    AvlTree& operator=(AvlTree other) noexcept;

    /**
     * @brief Destroy the Avl Tree object
     *
     */
    ~AvlTree() = default;

    /**
     * @brief Insert an item into the AVL tree
     *
     * @param item
     */
    void insert(const T& item);

    /**
     * @brief Remove an item from the AVL tree
     *
     * @param item
     */
    void remove(const T& item);

    /**
     * @brief Remove all items and reset the AVL tree to an empty state
     */
    void clear() noexcept;

    /**
     * @brief Display AVL Tree's contents with the root above its children with
     * diagonal arrows
     *
     * @param out Output stream, defaults to the terminal
     * @requires T to support insertion into std::ostream when display is used
     * @note Layout assumes single-line ASCII values and a UTF-8 terminal.
     */
    void display(std::ostream& out = std::cout) const;

    /**
     * @brief Check if the AVL tree is empty
     *
     * @return true if the tree is empty, false otherwise
     */
    [[nodiscard]] bool isEmpty() const noexcept;

    /**
     * @brief Check if the AVL tree contains a specific item
     *
     * @param item
     * @return true if the tree contains the item, false otherwise
     */
    [[nodiscard]] bool hasItem(const T& item) const;

    /**
     * @brief Return the height of the AVL tree
     *
     * @return int
     */
    [[nodiscard]] int height() const noexcept;

    /**
     * @brief Return the number of items in the AVL tree
     *
     * @return int
     */
    [[nodiscard]] int size() const noexcept;

    /**
     * @brief Swap the contents of this AVL tree with another AVL tree
     *
     * @param other
     */
    void swap(AvlTree& other) noexcept;
    friend void swap(AvlTree& lhs, AvlTree& rhs) noexcept { lhs.swap(rhs); }

 private:
    struct Node {
        // Accept copyable values even when their move constructor is deleted.
        // NOLINTNEXTLINE(modernize-pass-by-value)
        explicit Node(const T& value) : item(value) {}

        T item;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int height = 0;
    };

    using NodePtr = std::unique_ptr<Node>;

    NodePtr root;
    int itemCount = 0;

    void insert(NodePtr& node, const T& item);
    void remove(NodePtr& node, const T& item);
    static const Node* find(const Node* node, const T& item);

    /** @brief Text block with the column of its root, used to join subtrees. */
    struct DisplayLayout {
        std::vector<std::string> lines;
        std::size_t width = 0;
        std::size_t rootColumn = 0;
    };

    static DisplayLayout makeDisplayLayout(const Node* node,
                                           const std::ostream& format);

    static NodePtr clone(const Node* node);
    static NodePtr detachMinimalNode(NodePtr& node) noexcept;
    static int getHeight(const Node* node) noexcept;
    static void updateHeight(Node* node) noexcept;
    static int balanceFactor(const Node* node) noexcept;
    static void rebalance(NodePtr& node) noexcept;
    static void rotateLeft(NodePtr& node) noexcept;
    static void rotateRight(NodePtr& node) noexcept;
};

template <typename T>
AvlTree<T>::AvlTree(std::initializer_list<T> items) {
    for (const auto& item : items) {
        insert(item);
    }
}

template <typename T>
AvlTree<T>::AvlTree(const AvlTree& other)
    : root(clone(other.root.get())), itemCount(other.itemCount) {}

template <typename T>
AvlTree<T>::AvlTree(AvlTree&& other) noexcept
    : root(std::move(other.root)),
      itemCount(std::exchange(other.itemCount, 0)) {}

template <typename T>
AvlTree<T>& AvlTree<T>::operator=(AvlTree other) noexcept {
    swap(other);
    return *this;
}

template <typename T>
void AvlTree<T>::swap(AvlTree& other) noexcept {
    root.swap(other.root);
    std::swap(itemCount, other.itemCount);
}

template <typename T>
void AvlTree<T>::insert(const T& item) {
    insert(root, item);
}

template <typename T>
void AvlTree<T>::insert(NodePtr& node, const T& item) {
    if (!node) {
        node = std::make_unique<Node>(item);
        ++itemCount;
        return;
    }

    if (item == node->item) {
        return;
    }

    if (item < node->item) {
        insert(node->left, item);
    } else {
        insert(node->right, item);
    }

    rebalance(node);
}

template <typename T>
void AvlTree<T>::remove(const T& item) {
    remove(root, item);
}

template <typename T>
void AvlTree<T>::remove(NodePtr& node, const T& item) {
    if (!node) {
        return;
    }

    if (item == node->item) {
        auto oldNode = std::move(node);
        if (!oldNode->left) {
            node = std::move(oldNode->right);
        } else if (!oldNode->right) {
            node = std::move(oldNode->left);
        } else {
            auto successor = detachMinimalNode(oldNode->right);
            successor->left = std::move(oldNode->left);
            successor->right = std::move(oldNode->right);
            node = std::move(successor);
        }
        --itemCount;
    } else if (item < node->item) {
        remove(node->left, item);
    } else {
        remove(node->right, item);
    }

    rebalance(node);
}

template <typename T>
void AvlTree<T>::clear() noexcept {
    root.reset();
    itemCount = 0;
}

template <typename T>
void AvlTree<T>::display(std::ostream& out) const {
    if (!root) {
        out << "(empty)\n";
        return;
    }

    const auto layout = makeDisplayLayout(root.get(), out);
    for (std::size_t row = 0; row < layout.lines.size(); ++row) {
        const auto& line = layout.lines[row];
        const auto end = line.find_last_not_of(' ');
        if (end != std::string::npos) {
            for (std::size_t column = 0; column <= end; ++column) {
                if (row % 2 == 1 && line[column] == '/') {
                    out << "\u2199";
                } else if (row % 2 == 1 && line[column] == '\\') {
                    out << "\u2198";
                } else {
                    out << line[column];
                }
            }
        }
        out << '\n';
    }
}

template <typename T>
typename AvlTree<T>::DisplayLayout AvlTree<T>::makeDisplayLayout(
    const Node* node, const std::ostream& format) {
    if (!node) {
        return {};
    }

    std::ostringstream value;
    value.copyfmt(format);
    value << node->item;
    const std::string label = value.str().empty() ? "\"\"" : value.str();
    const auto left = makeDisplayLayout(node->left.get(), format);
    const auto right = makeDisplayLayout(node->right.get(), format);
    if (!node->left && !node->right) {
        return {{label}, label.size(), label.size() / 2};
    }

    std::size_t leftOffset = 0;
    std::size_t rightOffset = 0;
    std::size_t center = 0;
    if (node->left && node->right) {
        // Leave a gap between the complete subtree blocks to prevent overlaps.
        rightOffset = left.width + 3;
        center = (left.rootColumn + rightOffset + right.rootColumn) / 2;
    } else if (node->left) {
        center = left.rootColumn + 2;
    } else {
        rightOffset = 2;
        center = right.rootColumn;
    }

    // A wide parent label may extend past the left edge of its children.
    const auto padding =
        center < label.size() / 2 ? label.size() / 2 - center : 0;
    center += padding;
    leftOffset += padding;
    rightOffset += padding;
    const auto labelStart = center - label.size() / 2;
    const auto width =
        std::max({labelStart + label.size(), leftOffset + left.width,
                  rightOffset + right.width});
    const auto rows = 2 + std::max(left.lines.size(), right.lines.size());
    DisplayLayout layout{
        std::vector<std::string>(rows, std::string(width, ' ')), width, center};
    layout.lines[0].replace(labelStart, label.size(), label);

    if (node->left) {
        layout.lines[1][(leftOffset + left.rootColumn + center) / 2] = '/';
    }
    if (node->right) {
        layout.lines[1][(rightOffset + right.rootColumn + center + 1) / 2] =
            '\\';
    }
    for (std::size_t row = 0; row < left.lines.size(); ++row) {
        layout.lines[row + 2].replace(leftOffset, left.width, left.lines[row]);
    }
    for (std::size_t row = 0; row < right.lines.size(); ++row) {
        layout.lines[row + 2].replace(rightOffset, right.width,
                                      right.lines[row]);
    }
    return layout;
}

template <typename T>
bool AvlTree<T>::isEmpty() const noexcept {
    return !root;
}

template <typename T>
bool AvlTree<T>::hasItem(const T& item) const {
    return find(root.get(), item) != nullptr;
}

template <typename T>
int AvlTree<T>::height() const noexcept {
    return getHeight(root.get());
}

template <typename T>
int AvlTree<T>::size() const noexcept {
    return itemCount;
}

template <typename T>
typename AvlTree<T>::NodePtr AvlTree<T>::clone(const Node* node) {
    if (!node) {
        return nullptr;
    }

    auto copy = std::make_unique<Node>(node->item);
    copy->left = clone(node->left.get());
    copy->right = clone(node->right.get());
    copy->height = node->height;
    return copy;
}

template <typename T>
typename AvlTree<T>::NodePtr AvlTree<T>::detachMinimalNode(
    NodePtr& node) noexcept {
    if (!node->left) {
        auto minimum = std::move(node);
        node = std::move(minimum->right);
        return minimum;
    }

    auto minimum = detachMinimalNode(node->left);
    rebalance(node);
    return minimum;
}

template <typename T>
const typename AvlTree<T>::Node* AvlTree<T>::find(const Node* node,
                                                  const T& item) {
    while (node) {
        if (item == node->item) {
            return node;
        }

        if (item < node->item) {
            node = node->left.get();
        } else {
            node = node->right.get();
        }
    }

    return nullptr;
}

template <typename T>
int AvlTree<T>::getHeight(const Node* node) noexcept {
    return node ? node->height : -1;
}

template <typename T>
void AvlTree<T>::updateHeight(Node* node) noexcept {
    if (node) {
        node->height = std::max(getHeight(node->left.get()),
                                getHeight(node->right.get())) +
                       1;
    }
}

template <typename T>
int AvlTree<T>::balanceFactor(const Node* node) noexcept {
    return node ? getHeight(node->left.get()) - getHeight(node->right.get())
                : 0;
}

template <typename T>
void AvlTree<T>::rebalance(NodePtr& node) noexcept {
    if (!node) {
        return;
    }

    updateHeight(node.get());
    const int balance = balanceFactor(node.get());

    if (balance > 1) {
        if (balanceFactor(node->left.get()) < 0) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    } else if (balance < -1) {
        if (balanceFactor(node->right.get()) > 0) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
}

template <typename T>
void AvlTree<T>::rotateLeft(NodePtr& node) noexcept {
    auto newRoot = std::move(node->right);
    node->right = std::move(newRoot->left);
    updateHeight(node.get());

    newRoot->left = std::move(node);
    updateHeight(newRoot.get());
    node = std::move(newRoot);
}

template <typename T>
void AvlTree<T>::rotateRight(NodePtr& node) noexcept {
    auto newRoot = std::move(node->left);
    node->left = std::move(newRoot->right);
    updateHeight(node.get());

    newRoot->right = std::move(node);
    updateHeight(newRoot.get());
    node = std::move(newRoot);
}

/**
 * @brief Self-tests of the AVL tree public interface.
 * @returns void
 */
static void tests() {
    const auto assert_items = [](const AvlTree<int>& tree,
                                 std::initializer_list<int> items) {
        assert(tree.size() == static_cast<int>(items.size()));
        assert(tree.isEmpty() == (items.size() == 0));
        for (int item : items) {
            assert(tree.hasItem(item));
        }
    };

    // Empty operations, repeated clearing, and reuse.
    {
        AvlTree<int> tree;
        assert_items(tree, {});
        assert(tree.height() == -1);
        assert(!tree.hasItem(42));
        tree.remove(42);
        tree.clear();
        assert_items(tree, {});
        assert(tree.height() == -1);

        tree = AvlTree<int>{5, 3, 8, 1, 4, 7, 9};
        tree.clear();
        assert_items(tree, {});
        assert(tree.height() == -1);
        assert(!tree.hasItem(5));
        tree.clear();
        tree.insert(42);
        assert_items(tree, {42});
        assert(tree.height() == 0);
    }

    // Initializer lists, duplicate values, and all four insertion rotations.
    {
        AvlTree<int> tree{5, 3, 8, 1, 4, 7, 9, 5};
        assert_items(tree, {1, 3, 4, 5, 7, 8, 9});
        assert(tree.height() == 2);
        tree.insert(3);
        assert_items(tree, {1, 3, 4, 5, 7, 8, 9});
        assert(!tree.hasItem(6));

        const std::array<std::initializer_list<int>, 4> rotations{{
            {3, 2, 1},  // Left-left: rotate right.
            {1, 2, 3},  // Right-right: rotate left.
            {3, 1, 2},  // Left-right: double rotation.
            {1, 3, 2}   // Right-left: double rotation.
        }};
        for (const auto& items : rotations) {
            const AvlTree<int> rotated(items);
            assert_items(rotated, {1, 2, 3});
            assert(rotated.height() == 1);
        }
    }

    // Leaf, single-child, and two-child deletion, including the root.
    {
        AvlTree<int> tree{2, 1, 3};
        tree.remove(99);
        assert_items(tree, {1, 2, 3});
        tree.remove(1);  // Leaf.
        assert_items(tree, {2, 3});
        tree.remove(2);  // Root with one child.
        assert_items(tree, {3});
        assert(tree.height() == 0);
        tree.remove(3);  // Last node.
        assert_items(tree, {});
        assert(tree.height() == -1);

        tree = AvlTree<int>{4, 2, 6, 1};
        tree.remove(2);  // Non-root node with one child.
        assert_items(tree, {1, 4, 6});
        assert(tree.height() == 1);
        tree.remove(4);  // Successor is the immediate right child.
        assert_items(tree, {1, 6});

        tree = AvlTree<int>{20, 10, 40, 5, 15, 30, 50, 35};
        // Successor 30 has a right child that must be preserved.
        tree.remove(20);
        assert_items(tree, {5, 10, 15, 30, 35, 40, 50});
        assert(!tree.hasItem(20));
        assert(tree.height() == 2);
    }

    // All four deletion rotations leave three nodes of height one.
    {
        const std::array<std::pair<std::array<int, 4>, int>, 4>
            rotations{{
                {{3, 2, 4, 1}, 4},  // Left-left.
                {{2, 1, 3, 4}, 1},  // Right-right.
                {{3, 1, 4, 2}, 4},  // Left-right.
                {{2, 1, 4, 3}, 1}   // Right-left.
            }};
        for (const auto& rotation : rotations) {
            AvlTree<int> tree;
            for (int item : rotation.first) {
                tree.insert(item);
            }
            tree.remove(rotation.second);
            assert(tree.size() == 3);
            assert(tree.height() == 1);
            for (int item : rotation.first) {
                assert(tree.hasItem(item) == (item != rotation.second));
            }
        }
    }

    // Independent copies and reusable moved-from trees.
    {
        AvlTree<int> original{2, 1, 3};
        AvlTree<int> copied(original);
        copied.remove(1);
        assert_items(original, {1, 2, 3});
        assert_items(copied, {2, 3});

        AvlTree<int> assigned{99};
        assigned = original;
        original.clear();
        assert_items(assigned, {1, 2, 3});
        assert(assigned.height() == 1);

        AvlTree<int> moved(std::move(copied));
        assert_items(moved, {2, 3});
        assert_items(copied, {});
        // AvlTree guarantees that moved-from trees are empty and usable.
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move)
        assert(copied.height() == -1);
        copied.insert(42);
        assert_items(copied, {42});

        assigned = std::move(moved);
        assert_items(assigned, {2, 3});
        assert(!assigned.hasItem(1));
        assert_items(moved, {});
        // Check the same guarantee after move assignment.
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move)
        assert(moved.height() == -1);
        moved.insert(7);
        swap(assigned, moved);
        assert_items(assigned, {7});
        assert_items(moved, {2, 3});
        assert(assigned.height() == 0);
        assert(moved.height() == 1);
    }

    // Non-integer values.
    {
        AvlTree<std::string> tree{"pear", "apple", "orange", "pear"};
        assert(tree.size() == 3);
        assert(tree.height() == 1);
        tree.remove("orange");
        assert(!tree.hasItem("orange"));
        assert(tree.hasItem("apple"));
        assert(tree.hasItem("pear"));
        assert(tree.size() == 2);
    }

    // Terminal output through a stream.
    {
        std::ostringstream empty;
        AvlTree<int>{}.display(empty);
        assert(empty.str() == "(empty)\n");

        std::ostringstream singleton;
        AvlTree<int>{500}.display(singleton);
        assert(singleton.str() == "500\n");

        std::ostringstream left;
        AvlTree<int>{2, 1}.display(left);
        assert(left.str() == "  2\n \u2199\n1\n");
        std::ostringstream right;
        AvlTree<int>{1, 2}.display(right);
        assert(right.str() == "1\n \u2198\n  2\n");

        const AvlTree<int> tree{2, 1, 3};
        std::ostringstream output;
        tree.display(output);
        assert(output.str() == "  2\n \u2199 \u2198\n1   3\n");
        assert_items(tree, {1, 2, 3});
        assert(tree.height() == 1);
    }

    // Mixed operations compared with std::set using a fixed random seed.
    {
        AvlTree<int> tree;
        std::set<int> expected;
        std::mt19937 generator(42);
        std::uniform_int_distribution<int> value(-50, 50);
        std::bernoulli_distribution insert(0.5);

        for (int step = 0; step < 2000; ++step) {
            const int item = value(generator);
            if (insert(generator)) {
                tree.insert(item);
                expected.insert(item);
            } else {
                tree.remove(item);
                expected.erase(item);
            }
            assert(tree.size() == static_cast<int>(expected.size()));
            assert(tree.isEmpty() == expected.empty());
            for (int candidate = -50; candidate <= 50; ++candidate) {
                assert(tree.hasItem(candidate) ==
                       (expected.count(candidate) != 0));
            }

            // An AVL of height h needs at least 1 + N(h-1) + N(h-2) nodes.
            int previous = 0;
            int minimum_nodes = 1;
            int maximum_height = -1;
            while (minimum_nodes <= static_cast<int>(expected.size())) {
                const int next = 1 + minimum_nodes + previous;
                previous = minimum_nodes;
                minimum_nodes = next;
                ++maximum_height;
            }
            assert(tree.height() >= (expected.empty() ? -1 : 0));
            assert(tree.height() <= maximum_height);
        }
    }

    std::cout << "All AVL tree tests passed!\n";
}

/**
 * @brief Run the self-tests and display an example tree.
 * @returns 0 on exit
 */
int main() {
    tests();
    AvlTree<int> tree{5, 3, 8, 1, 4, 7, 500};
    tree.display();
    tree.clear();
    std::cout << tree.isEmpty() << '\n';
    return 0;
}
