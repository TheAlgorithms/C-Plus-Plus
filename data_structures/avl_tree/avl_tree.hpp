/**
 * @file avl_tree.hpp
 * @author Bertrand Awenze (https://github.com/bertrand-awz)
 * @brief Implementation of an AVL Tree data structure.
 *
 * @details This implementation is a self-balancing binary search tree that
 * maintains its height to be logarithmic in the number of nodes, ensuring
 * efficient operations. \n The AVL Tree supports insertion, deletion, and
 * search operations in O(log n) time. It automatically balances itself after
 * insertions and deletions to maintain optimal performance. The tree can be
 * displayed in a structured format in terminal, and it provides methods to
 * check for emptiness, size, and height.
 *
 * @note This implementation try to resolve the issue mentioned in the following
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

#ifndef AVL_TREE_AVL_TREE_HPP
#define AVL_TREE_AVL_TREE_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
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

#endif  // AVL_TREE_AVL_TREE_HPP
