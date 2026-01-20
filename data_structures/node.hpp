/**
 * @file
 * @brief  Provides Node class and related utilities
 **/
#ifndef DATA_STRUCTURES_NODE_HPP_
#define DATA_STRUCTURES_NODE_HPP_

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

template <typename Node, typename Action>
void traverse(const Node* const inNode, const Action& action) {
    if (inNode) {
        action(*inNode);
        traverse(inNode->next.get(), action);
    }
}

template <typename Node>
void display_all(const Node* const inNode) {
    traverse(inNode,
             [](const Node& curNode) { std::cout << curNode.data << " "; });
}

template <typename Node>
std::vector<typename Node::value_type> push_all_to_vector(
    const Node* const inNode, const std::size_t expected_size = 0) {
    std::vector<typename Node::value_type> res;
    res.reserve(expected_size);
    traverse(inNode,
             [&res](const Node& curNode) { res.push_back(curNode.data); });
    return res;
}

#endif  // DATA_STRUCTURES_NODE_HPP_
