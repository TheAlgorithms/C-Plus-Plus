/**
 * @file
 * @brief  Provides Node class and related utilities
 **/
#ifndef DATA_STRUCTURES_NODE_HPP_
#define DATA_STRUCTURES_NODE_HPP_

#include <functional>
#include <iostream>  /// for std::cout
#include <memory>    /// for std::shared_ptr
#include <vector>    /// for std::vector

/** Definition of the node as a linked-list
 * \tparam ValueType type of data nodes of the linked list should contain
 */
template <class ValueType>
struct Node {
    using value_type = ValueType;
    ValueType data = {};
    std::shared_ptr<Node<ValueType>> next = {};
};

template <typename ValueType>
void traverse(const Node<ValueType>* const inNode,
              const std::function<void(Node<ValueType>)>& action) {
    if (inNode) {
        action(*inNode);
        traverse(inNode->next.get(), action);
    }
}

template <typename ValueType>
void display_all(const Node<ValueType>* const inNode) {
    traverse<ValueType>(inNode, [](const Node<ValueType>& curNode) {
        std::cout << curNode.data << " ";
    });
}

template <typename ValueType>
std::vector<ValueType> push_all_to_vector(const Node<ValueType>* const inNode,
                                          const std::size_t expected_size = 0) {
    std::vector<ValueType> res;
    res.reserve(expected_size);
    traverse<ValueType>(inNode, [&res](const Node<ValueType>& curNode) {
        res.push_back(curNode.data);
    });
    return res;
}

#endif  // DATA_STRUCTURES_NODE_HPP_
