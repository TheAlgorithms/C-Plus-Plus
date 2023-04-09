/**
 * @file avltree_map.hpp
 * @brief An [AVLTree](https://en.wikipedia.org/wiki/AVL_tree)-based
 *  map implementation
 * @details The map is sorted according to the natural ordering of its
 *  keys or by a {@code Compare} function provided; This implementation
 *  provides guaranteed log(n) time cost for the contains, get, insert
 *  and remove operations.
 * @author [r.ivance](https://github.com/RIvance)
 */

#ifndef AVLTREE_MAP_HPP
#define AVLTREE_MAP_HPP

#include <cstdint>      /// for standard integer definitions
#include <cstddef>      /// for standard definitions like `std::size_t`
#include <cassert>      /// for assert
#include <memory>       /// for smart pointers
#include <functional>   /// for functional programming
#include <stack>        /// for `std::stack`
#include <vector>       /// for `std::vector`

/**
 * @brief An AVLTree-based map implementation
 *  https://en.wikipedia.org/wiki/AVL_tree
 * @tparam Key the type of keys maintained by this map
 * @tparam Value the type of mapped values
 * @tparam Compare the comparator function
 */
template <
    typename Key, typename Value,
    typename Compare = std::less<Key>
>
class AvlTreeMap
{
  private:

    using USize = size_t;           ///< size type alias
    using Factor = int64_t;         ///< int64_t as the balance factor

    Compare compare = Compare();    ///< the comparator

  public:

    /**
     * @brief The key-value entry type
     */
    struct Entry
    {
        Key key;        ///< the key of the entry
        Value value;    ///< the value of the entry

        bool operator==(const Entry & rhs) const noexcept
        {
            return this->key == rhs.key && this->value == rhs.value;
        }

        bool operator!=(const Entry & rhs) const noexcept
        {
            return this->key != rhs.key || this->value != rhs.value;
        }
    };

  private:

    struct Node
    {
        using Ptr = std::shared_ptr<Node>;                          ///< node pointer type
        using Provider = const std::function<Ptr(void)> &;          ///< node provider function type
        using Consumer = const std::function<void(const Ptr &)> &;  ///< node consumer function type

        Key key;                ///< the key of the node, used for ordering
        Value value {};         ///< the value of the node

        Ptr left = nullptr;     ///< the left child
        Ptr right = nullptr;    ///< the right child

        /**
         * @brief The height of the node from the leaves
         * @details The height of a node is the number of nodes
         *  on the longest path from the node to a leaf.
         *  The height of a leaf is 1.
         */
        USize height = 1;

        explicit Node(Key k) : key(std::move(k)) {}
        explicit Node(Key k, Value v) : key(std::move(k)), value(std::move(v)) {}
        
        Node(const Node& other) = default;
        Node(Node&& other) noexcept = default;
        
        Node& operator=(const Node& other) = default;
        Node& operator=(Node&& other) noexcept = default;

        ~Node() = default;

        /**
         * @brief Recursively clone the subtree rooted at this node
         * @return Node::Ptr the root of the cloned subtree
         */
        Ptr clone() const
        {
            Ptr node = std::make_shared<Node>(Node(this->key, this->value));
            if (this->left != nullptr) {
                node->left = this->left->clone();
            }
            if (this->right != nullptr) {
                node->right = this->right->clone();
            }
            return node;
        }

        inline bool isLeaf() const noexcept
        {
            return this->left == nullptr && this->right == nullptr;
        }

        /**
         * @brief Update the height of this node according to its children
         * @returns void
         */
        inline void updateHeight() noexcept
        {
            if (this->isLeaf()) {
                this->height = 1;
            } else if (this->left == nullptr) {
                this->height = this->right->height + 1;
            } else if (this->right == nullptr) {
                this->height = this->left->height + 1;
            } else {
                this->height = std::max(left->height, right->height) + 1;
            }
        }

        /**
         * @brief Get the balance factor of this node
         * @return Factor the balance factor
         */
        inline Factor factor() const noexcept
        {
            if (this->isLeaf()) {
                return 0;
            } else if (this->left == nullptr) {
                return static_cast<Factor>(this->right->height);
            } else if (this->right == nullptr) {
                return static_cast<Factor>(-this->left->height);
            } else {
                return static_cast<Factor>(this->right->height - this->left->height);
            }
        }

        /**
         * @brief Convert this node to an entry
         * @return Entry
         */
        inline Entry entry() const
        {
            return Entry { key, value };
        }

        /**
         * @brief Construct a node from a given key
         * @param k key
         * @return Node::Ptr
         */
        static Ptr from(const Key & k)
        {
            return std::make_shared<Node>(Node(k));
        }

        /**
         * @brief Construct a node from a given pair of key and value
         * @param k key
         * @param v value
         * @return Node::Ptr
         */
        static Ptr from(const Key & k, const Value& v)
        {
            return std::make_shared<Node>(Node(k, v));
        }
    };

    using NodePtr = typename Node::Ptr;             ///< node pointer type
    using ConstNodePtr = const NodePtr&;            ///< const node pointer type
    using NodeProvider = typename Node::Provider;   ///< node provider function type
    using NodeConsumer = typename Node::Consumer;   ///< node consumer function type

    NodePtr root = nullptr;     ///< the root node of the tree
    USize count = 0;            ///< the number of nodes(entries) in the tree map

    using K = const Key&;       ///< constant key parameter type alias
    using V = const Value&;     ///< constant value parameter type alias

  public:

    using EntryList = std::vector<Entry>;            ///< vector of entries
    using KeyValueConsumer = const std::function<void(K, V)> &;          ///< key-value consumer function type
    using MutKeyValueConsumer = const std::function<void(K, Value&)> &; ///< mutable key-value consumer function type
    using KeyValueFilter = const std::function<bool(K, V)> &;            ///< key-value filter function type

    /**
     * @brief Exception thrown when a mapping is not found
     */
    class NoSuchMappingException : protected std::exception
    {
      private:

        const char* message;

      public:

        explicit NoSuchMappingException(const char* msg) : message(msg) {}
        const char* what() const noexcept override { return message; }
    };

    AvlTreeMap() noexcept = default;

    /**
     * @brief Clone constructor
     * @param other the other map to clone
     */
    AvlTreeMap(const AvlTreeMap & other) noexcept
    {
        this->root = other.root->clone();
        this->count = other.count;
    }
    
    AvlTreeMap(AvlTreeMap && other) noexcept = default;
    
    /**
     * @brief Copy assignment operator
     * @param other the other map to copy
     * @return AvlTreeMap&
     */
    AvlTreeMap& operator=(const AvlTreeMap & other) noexcept
    {
        this->root = other.root->clone();
        this->count = other.count;
        return *this;
    }
    
    AvlTreeMap& operator=(AvlTreeMap && other) noexcept = default;
    
    ~AvlTreeMap() noexcept = default;

    /**
     * @brief Returns the number of entries in this map.
     * @return size_t
     */
    inline USize size() const noexcept
    {
        return this->count;
    }

    /**
     * @brief Returns true if this collection contains no elements.
     * @return bool
     */
    inline bool empty() const noexcept
    {
        return this->count == 0;
    }

    /**
     * @brief Removes all of the elements from this map.
     * @returns void
     */
    void clear() noexcept
    {
        this->root = nullptr;
        this->count = 0;
    }

    /**
     * @brief Returns the value to which the specified key is mapped; If this map
     *  contains no mapping for the key, a {@code NoSuchMappingException} will
     *  be thrown.
     * @param key the key whose associated value is to be returned
     * @return AvlTreeMap<Key, Value>::Value
     * @throws NoSuchMappingException
     */
    Value get(K key) const
    {
        if (this->root == nullptr) {
            throw NoSuchMappingException("Invalid key");
        } else {
            NodePtr node = this->getNode(this->root, key);
            if (node != nullptr) {
                return node->value;
            } else {
                throw NoSuchMappingException("Invalid key");
            }
        }
    }

    /**
     * @brief Returns the value to which the specified key is mapped; If this map
     *  contains no mapping for the key, a new mapping with a default value
     *  will be inserted.
     * @param key the key whose associated value is to be returned
     * @return AvlTreeMap<Key, Value>::Value&
     */
    Value& getOrDefault(K key)
    {
        if (this->root == nullptr) {
            this->root = Node::from(key);
            this->count += 1;
            return this->root->value;
        } else {
            return this->getNodeOrProvide(this->root, key, [&key]() {
                return Node::from(key);
            })->value;
        }
    }

    /**
     * @brief Returns true if this map contains a mapping for the specified key.
     * @param key the key whose presence in this map is to be tested
     * @return bool
     */
    bool contains(K key) const
    {
        return this->getNode(this->root, key) != nullptr;
    }

    /**
     * @brief Associates the specified value with the specified key in this map.
     * @param key the key of the mapping
     * @param value the value to be associated with the key
     * @returns void
     */
    void insert(K key, V value)
    {
        if (this->root == nullptr) {
            this->root = Node::from(key, value);
            this->count += 1;
        } else {
            this->insert(this->root, key, value);
        }
    }

    /**
     * @brief If the specified key is not already associated with a value,
     *  associates it with the given value and returns true, else returns false.
     * @param key the key of the mapping
     * @param value the value to be associated with the key
     * @return bool true if the key is not already associated with a value
     */
    bool insertIfAbsent(K key, V value)
    {
        USize sizeBeforeInsertion = this->size();
        if (this->root == nullptr) {
            this->root = Node::from(key, value);
            this->count += 1;
        } else {
            this->insert(this->root, key, value, false);
        }
        return this->size() > sizeBeforeInsertion;
    }

    /**
     * @brief If the specified key is not already associated with a value, associates
     *  it with the given value and returns the value, else returns the associated
     *  value.
     * @param key the key of the mapping
     * @param value the value to be associated with the key
     * @return Value& the mutable value reference associated with the key
     */
    Value& getOrInsert(K key, V value)
    {
        if (this->root == nullptr) {
            this->root = Node::from(key, value);
            this->count += 1;
            return root->value;
        } else {
            NodePtr node = getNodeOrProvide(this->root, key, [&]() {
                return Node::from(key, value);
            });
            return node->value;
        }
    }

    /**
     * @brief Gets the value associated with the specified key
     * @param key the key of the mapping
     * @return Value the value associated with the key
     */
    Value operator[](K key) const
    {
        return this->get(key);
    }

    /**
     * @brief Gets the value associated with the specified key
     *  as a mutable reference
     * @param key the key of the mapping
     * @return Value& the mutable value reference associated with the key
     */
    Value& operator[](K key)
    {
        return this->getOrDefault(key);
    }

    /**
     * Removes the mapping for a key from this map if it is present;
     * Returns true if the mapping is present else returns false
     * @param key the key of the mapping
     * @return bool true if the mapping is present else returns false
     */
    bool remove(K key)
    {
        if (this->root == nullptr) {
            return false;
        } else {
            return this->remove(this->root, key, [](ConstNodePtr) {});
        }
    }

    /**
     * @brief Removes the mapping for a key from this map if it is present and returns
     *  the value which is mapped to the key; If this map contains no mapping for the key,
     *  a {@code NoSuchMappingException} will be thrown.
     * @param key
     * @return AvlTreeMap<Key, Value>::Value
     * @throws NoSuchMappingException
     */
    Value getAndRemove(K key)
    {
        Value result;
        NodeConsumer action = [&](ConstNodePtr node) {
            result = node->value;
        };

        if (root == nullptr) {
            throw NoSuchMappingException("Invalid key");
        } else {
            if (remove(this->root, key, action)) {
                return result;
            } else {
                throw NoSuchMappingException("Invalid key");
            }
        }
    }

    /**
     * @brief Gets the entry corresponding to the specified key; if no such entry
     *  exists, returns the entry for the least key greater than the specified
     *  key; if no such entry exists (i.e., the greatest key in the Tree is less
     *  than the specified key), a {@code NoSuchMappingException} will be thrown.
     * @param key
     * @return AvlTreeMap<Key, Value>::Entry
     * @throws NoSuchMappingException
     */
    Entry getCeilingEntry(K key) const
    {
        if (this->root == nullptr) {
            throw NoSuchMappingException("No ceiling entry in this map");
        }

        NodePtr node = this->root;
        std::stack<NodePtr> ancestors;

        while (node != nullptr) {
            if (key == node->key) {
                return node->entry();
            }

            if (compare(key, node->key)) {
                /* key < node->key */
                if (node->left != nullptr) {
                    ancestors.push(node);
                    node = node->left;
                } else {
                    return node->entry();
                }
            } else {
                /* key > node->key */
                if (node->right != nullptr) {
                    ancestors.push(node);
                    node = node->right;
                } else {

                    if (ancestors.empty()) {
                        throw NoSuchMappingException("No ceiling entry in this map");
                    }

                    NodePtr parent = ancestors.top();
                    ancestors.pop();

                    while (node == parent->right) {
                        node = parent;
                        if (!ancestors.empty()) {
                            parent = ancestors.top();
                            ancestors.pop();
                        } else {
                            throw NoSuchMappingException("No ceiling entry in this map");
                        }
                    }

                    return parent->entry();
                }
            }
        }

        throw NoSuchMappingException("No ceiling entry in this map");
    }

    /**
     * @brief Gets the entry corresponding to the specified key; if no such entry
     *  exists, returns the entry for the greatest key less than the specified key;
     *  if no such entry exists, a {@code NoSuchMappingException} will be thrown.
     * @param key
     * @return AvlTreeMap<Key, Value>::Entry
     * @throws NoSuchMappingException
     */
    Entry getFloorEntry(K key) const
    {
        if (this->root == nullptr) {
            throw NoSuchMappingException("No floor entry exists in this map");
        }

        NodePtr node = this->root;
        std::stack<NodePtr> ancestors;

        while (node != nullptr) {
            if (key == node->key) {
                return node->entry();
            }

            if (compare(key, node->key)) {
                /* key < node->key */
                if (node->left != nullptr) {
                    ancestors.push(node);
                    node = node->left;
                } else {

                    if (ancestors.empty()) {
                        throw NoSuchMappingException("No floor entry exists in this map");
                    }

                    NodePtr parent = ancestors.top();
                    ancestors.pop();

                    while (node == parent->left) {
                        node = parent;
                        if (!ancestors.empty()) {
                            parent = ancestors.top();
                            ancestors.pop();
                        } else {
                            throw NoSuchMappingException("No floor entry exists in this map");
                        }
                    }

                    return parent->entry();
                }
            } else {
                /* key > node->key */
                if (node->right != nullptr) {
                    ancestors.push(node);
                    node = node->right;
                } else {
                    return node->entry();
                }
            }
        }

        throw NoSuchMappingException("No floor entry exists in this map");
    }

    /**
     * @brief Gets the entry for the least key greater than the specified
     *  key; if no such entry exists, returns the entry for the least
     *  key greater than the specified key; if no such entry exists,
     *  a {@code NoSuchMappingException} will be thrown.
     * @param key
     * @return AvlTreeMap<Key, Value>::Entry
     * @throws NoSuchMappingException
     */
    Entry getHigherEntry(K key) const
    {
        if (this->root == nullptr) {
            throw NoSuchMappingException("No higher entry exists in this map");
        }

        NodePtr node = this->root;
        std::stack<NodePtr> ancestors;

        while (node != nullptr) {

            if (compare(key, node->key)) {
                /* key < node->key */
                if (node->left != nullptr) {
                    ancestors.push(node);
                    node = node->left;
                } else {
                    return node->entry();
                }
            } else {
                /* key >= node->key */
                if (node->right != nullptr) {
                    ancestors.push(node);
                    node = node->right;
                } else {

                    if (ancestors.empty()) {
                        throw NoSuchMappingException("No higher entry exists in this map");
                    }

                    NodePtr parent = ancestors.top();
                    ancestors.pop();

                    while (node == parent->right) {
                        node = parent;
                        if (!ancestors.empty()) {
                            parent = ancestors.top();
                            ancestors.pop();
                        } else {
                            throw NoSuchMappingException("No higher entry exists in this map");
                        }
                    }

                    return parent->entry();
                }
            }
        }

        throw NoSuchMappingException("No higher entry exists in this map");
    }

    /**
     * @brief Returns the entry for the greatest key less than the specified key;
     *  if no such entry exists (i.e., the least key in the Tree is greater than
     *  the specified key), a {@code NoSuchMappingException} will be thrown.
     * @param key
     * @return AvlTreeMap<Key, Value>::Entry
     * @throws NoSuchMappingException
     */
    Entry getLowerEntry(K key) const
    {
        if (this->root == nullptr) {
            throw NoSuchMappingException("No lower entry exists in this map");
        }

        NodePtr node = this->root;
        std::stack<NodePtr> ancestors;

        while (node != nullptr) {
            if (compare(key, node->key) || key == node->key) {
                /* key <= node->key */
                if (node->left != nullptr) {
                    ancestors.push(node);
                    node = node->left;
                } else {

                    if (ancestors.empty()) {
                        throw NoSuchMappingException("No lower entry exists in this map");
                    }

                    NodePtr parent = ancestors.top();
                    ancestors.pop();

                    while (node == parent->left) {
                        node = parent;
                        if (!ancestors.empty()) {
                            parent = ancestors.top();
                            ancestors.pop();
                        } else {
                            throw NoSuchMappingException("No lower entry exists in this map");
                        }
                    }

                    return parent->entry();
                }
            } else {
                /* key > node->key */
                if (node->right != nullptr) {
                    ancestors.push(node);
                    node = node->right;
                } else {
                    return node->entry();
                }
            }
        }

        throw NoSuchMappingException("No lower entry exists in this map");
    }

    /**
     * @brief Remove all entries that satisfy the filter condition.
     * @param filter A function that takes a pair of key and value 
     *  as parameters and returns a boolean.
     * @returns void
     */
    void removeAll(KeyValueFilter filter)
    {
        std::vector<Key> keys;
        this->inorderTraversal([&](ConstNodePtr node) {
            if (filter(node->key, node->value)) {
                keys.push_back(node->key);
            }
        });
        for (const Key & key : keys) {
            this->remove(key);
        }
    }

    /**
     * @brief Performs the given action for each key and value entry in this map.
     *  The value is immutable for the action.
     * @param action A function that takes a pair of key and value as parameters.
     * @returns void
     */
    void forEach(KeyValueConsumer action) const
    {
        this->inorderTraversal([&](ConstNodePtr node) {
            action(node->key, node->value);
        });
    }

    /**
     * @brief Performs the given action for each key and value entry in this map.
     *  The value is mutable for the action.
     * @param action A function that takes a pair of key and value as parameters.
     * @returns void
     */
    void forEachMut(MutKeyValueConsumer action)
    {
        this->inorderTraversal([&](ConstNodePtr node) {
            action(node->key, node->value);
        });
    }

    /**
     * @brief Returns a list containing all of the entries in this map.
     * @return AvlTreeMap<Key, Value>::EntryList
     */
    EntryList toEntryList() const
    {
        EntryList entryList;
        this->inorderTraversal([&](ConstNodePtr node) {
            entryList.push_back(node->entry());
        });
        return entryList;
    }

  private:

    /**
     * @brief Left rotation, used to reduce the height of a subtree.
     * @param node the node to be rotated.
     * @return AvlTreeMap<Key, Value>::NodePtr the new root of the subtree.
     */
    static NodePtr rotateLeft(ConstNodePtr node)
    {
        //     |                       |
        //     N                       S
        //    / \     l-rotate(N)     / \
        //   L   S    ==========>    N   R
        //      / \                 / \
        //     M   R               L   M
        NodePtr successor = node->right;
        node->right = successor->left;
        successor->left = node;

        node->updateHeight();
        successor->updateHeight();

        return successor;
    }

    /**
     * @brief Right rotation, used to reduce the height of a subtree.
     * @param node the node to be rotated.
     * @return AvlTreeMap<Key, Value>::NodePtr the new root of the subtree.
     */
    static NodePtr rotateRight(ConstNodePtr node)
    {
        //       |                   |
        //       N                   S
        //      / \   r-rotate(N)   / \
        //     S   R  ==========>  L   N
        //    / \                     / \
        //   L   M                   M   R
        NodePtr successor = node->left;
        node->left = successor->right;
        successor->right = node;

        node->updateHeight();
        successor->updateHeight();

        return successor;
    }

    /**
     * @brief Swap the key and value of two nodes.
     * @param lhs
     * @param rhs
     * @returns void
     */
    static void swapNode(NodePtr & lhs, NodePtr & rhs)
    {
        std::swap(lhs->key, rhs->key);
        std::swap(lhs->value, rhs->value);
        std::swap(lhs, rhs);
    }

    /**
     * @brief Recursively maintain the balance of the tree with rotations.
     * @param node the node to be fixed.
     * @returns void
     */
    static void fixBalance(NodePtr & node)
    {
        if (node->factor() < -1) {
            if (node->left->factor() < 0) {
                //  Left-Left Case
                //       |
                //       C                 |
                //      /   r-rotate(C)    B
                //     B    ==========>   / \
                //    /                  A   C
                //   A
                node = rotateRight(node);
            } else {
                //  Left-Right Case
                //     |                   |
                //     C                   C                 |
                //    /   l-rotate(A)     /   r-rotate(C)    B
                //   A    ==========>    B    ==========>   / \
                //    \                 /                  A   C
                //     B               A
                node->left = rotateLeft(node->left);
                node = rotateRight(node);
            }
        } else if (node->factor() > 1) {
            if (node->right->factor() > 0) {
                //  Right-Right Case
                //   |
                //   C                     |
                //    \     l-rotate(C)    B
                //     B    ==========>   / \
                //      \                A   C
                //       A
                node = rotateLeft(node);
            } else {
                //  Right-Left Case
                //   |                 |
                //   A                 A                     |
                //    \   r-rotate(C)   \     l-rotate(A)    B
                //     C  ==========>    B    ==========>   / \
                //    /                   \                A   C
                //   B                     C
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
            }
        }
    }

    /**
     * @brief Get the node with the given key, or insert a new provided node.
     * @param node the root node of the subtree
     * @param key the key to search for
     * @param provide the function to provide a new node
     * @return NodePtr the node with the given key
     */
    NodePtr getNodeOrProvide(NodePtr & node, K key, NodeProvider provide)
    {
        assert(node != nullptr);

        if (key == node->key) {
            return node;
        }

        assert(key != node->key);

        NodePtr result;

        if (compare(key, node->key)) {
            /* key < node->key */
            if (node->left == nullptr) {
                result = node->left = provide();
                this->count += 1;
                node->updateHeight();
            } else {
                result = getNodeOrProvide(node->left, key, provide);
                node->updateHeight();
                fixBalance(node);
            }
        } else {
            /* key > node->key */
            if (node->right == nullptr) {
                result = node->right = provide();
                this->count += 1;
                node->updateHeight();
            } else {
                result = getNodeOrProvide(node->right, key, provide);
                node->updateHeight();
                fixBalance(node);
            }
        }

        return result;
    }

    /**
     * @brief Get the node with the given key.
     * @param node the root node of the subtree
     * @param key the key to search for
     * @return NodePtr the node with the given key
     */
    NodePtr getNode(ConstNodePtr node, K key) const
    {
        assert(node != nullptr);

        if (key == node->key) {
            return node;
        }

        if (compare(key, node->key)) {
            /* key < node->key */
            return node->left == nullptr ? nullptr : getNode(node->left, key);
        } else {
            /* key > node->key */
            return node->right == nullptr ? nullptr : getNode(node->right, key);
        }
    }

    /**
     * @brief Insert a new node with the given key and value.
     * @param node the root node of the subtree
     * @param key the key to insert
     * @param value the value to insert
     * @param replace whether to replace the value if the key already exists
     * @returns void
     */
    void insert(NodePtr & node, K key, V value, bool replace = true)
    {
        assert(node != nullptr);

        if (key == node->key) {
            if (replace) {
                node->value = value;
            }
            return;
        }

        assert(key != node->key);

        if (compare(key, node->key)) {
            /* key < node->key */
            if (node->left == nullptr) {
                node->left = Node::from(key, value);
                this->count += 1;
                node->updateHeight();
            } else {
                insert(node->left, key, value, replace);
                node->updateHeight();
                fixBalance(node);
            }
        } else {
            /* key > node->key */
            if (node->right == nullptr) {
                node->right = Node::from(key, value);
                this->count += 1;
                node->updateHeight();
            } else {
                insert(node->right, key, value, replace);
                node->updateHeight();
                fixBalance(node);
            }
        }
    }

    /**
     * @brief Remove the node with the given key.
     * @param node the root node of the subtree
     * @param key the key to search for
     * @param action the function to perform on the node
     * @return bool whether the node was removed
     */
    bool remove(NodePtr & node, K key, NodeConsumer action)
    {
        assert(node != nullptr);

        if (key != node->key) {
            if (compare(key, node->key)) {
                /* key < node->key */
                NodePtr & left = node->left;
                if (left != nullptr && remove(left, key, action)) {
                    node->updateHeight();
                    fixBalance(node);
                    return true;
                } else {
                    return false;
                }
            } else {
                /* key > node->key */
                NodePtr & right = node->right;
                if (right != nullptr && remove(right, key, action)) {
                    node->updateHeight();
                    fixBalance(node);
                    return true;
                } else {
                    return false;
                }
            }
        }

        assert(key == node->key);
        action(node);

        if (node->isLeaf()) {
            // Case 1: no child
            node = nullptr;
        } else if (node->right == nullptr) {
            // Case 2: left child only
            //     P
            //     |  remove(N)  P
            //     N  ========>  |
            //    /              L
            //   L
            node = node->left;
            node->updateHeight();
        } else if (node->left == nullptr) {
            // Case 3: right child only
            //   P
            //   |    remove(N)  P
            //   N    ========>  |
            //    \              R
            //     R
            node = node->right;
            node->updateHeight();
        } else if (node->right->left == nullptr) {
            // Case 4: both left and right child, right child has no left child
            //    |                 |
            //    N    remove(N)    R
            //   / \   ========>   /
            //  L   R             L
            NodePtr right = node->right;
            swapNode(node, right);
            right->right = node->right;
            node = right;
            node->updateHeight();
            fixBalance(node);
        } else {
            // Case 5: both left and right child, right child is not a leaf
            //   Step 1. find the node N with the smallest key
            //           and its parent P on the right subtree
            //   Step 2. swap S and N
            //   Step 3. remove node N like Case 1 or Case 3
            //   Step 4. update height for P
            //     |                  |
            //     N                  S                 |
            //    / \                / \                S
            //   L  ..  swap(N, S)  L  ..  remove(N)   / \
            //       |  =========>      |  ========>  L  ..
            //       P                  P                 |
            //      / \                / \                P
            //     S  ..              N  ..              / \
            //      \                  \                R  ..
            //       R                  R

            // Step 1
            NodePtr successor = node->right;
            NodePtr parent = node;
            while (successor->left != nullptr) {
                parent = successor;
                successor = parent->left;
            }
            // Step 2
            swapNode(node, successor);
            // Step 3
            parent->left = node->right;
            // Restore node
            node = successor;
            // Step 4
            parent->updateHeight();
        }

        this->count -= 1;
        return true;
    }

    /**
     * @brief Inorder traversal of the tree.
     * @param action the function to perform on each node
     * @returns void
     */
    void inorderTraversal(NodeConsumer action) const
    {
        if (this->root == nullptr) {
            return;
        }

        std::stack<NodePtr> stack;
        NodePtr node = this->root;

        while (node != nullptr || !stack.empty()) {
            while (node != nullptr) {
                stack.push(node);
                node = node->left;
            }
            if (!stack.empty()) {
                node = stack.top();
                stack.pop();
                action(node);
                node = node->right;
            }
        }
    }
};

#endif // AVLTREE_MAP_HPP
