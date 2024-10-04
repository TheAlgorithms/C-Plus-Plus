/**
 * @file
 * @brief Implementation for [LFU Cache]
 * (https://en.wikipedia.org/wiki/Least_frequently_used)
 *
 * LFU discards the least frequently used value. if there are multiple items
 * with the same minimum frequency then, the least recently used among them is
 * discarded. Data structures used - doubly linked list and unordered_map(hash
 * map).
 *
 * Hashmap maps the key to the address of the node of the linked list and its
 * current usage frequency. If the element is accessed the element is removed
 * from the linked list of the current frequency and added to the linked list of
 * incremented frequency.
 *
 * When the cache is full, the last element in the minimum frequency linked list
 * is popped.
 *
 * @author [Karan Sharma](https://github.com/deDSeC00720)
 */

#include <iostream>
#include <unordered_map>

namespace Cache {

template <typename T>
class D_Node {
 public:
    T data;
    D_Node<T> *prev;
    D_Node<T> *next;

    D_Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename K, typename V>
using CacheNode = D_Node<std::pair<K, V>>;

template <typename K, typename V>
class LFUCache {
    std::unordered_map<K, std::pair<CacheNode<K, V> *, int>>
        node_map;  // maps the key to the node address and frequency
    std::unordered_map<int, std::pair<CacheNode<K, V> *, CacheNode<K, V> *>>
        freq_map;  // maps the frequency to doubly linked list

    int minFreq;    // minimum frequency in the cache
    int _capacity;  // maximum capacity of the cache

 public:
    /**
     * @brief Constructor, Initialize with minFreq and _capacity.
     * @param _capacity Total capacity of the cache.
     */
    explicit LFUCache(int _capacity) : minFreq(0), _capacity(_capacity) {}

 private:
    /**
     * @brief push the node at first position in the linked list of given
     * frequency
     * @param freq the frequency mapping to the linked list where node should be
     * pushed.
     * @param node node to be pushed to the linked list.
     */
    void push(int freq, CacheNode<K, V> *node) {
        // if freq is not present, then make a new list with node as the head as
        // well as tail.
        if (!freq_map.count(key)) {
            freq_map[freq] = {node, node};
        }

        std::pair<CacheNode<K, V> *, CacheNode<K, V> *> &p = freq_map[freq];

        // insert the node at the beginning of the linked list and update the
        // head.
        p.first->prev = node;
        node->next = p.first;
        p.first = node;
    }

    /**
     * @brief increase the frequency of node and push it in the respective list.
     * @param p_node the node to be updated
     */
    void inc_freq(std::pair<CacheNode<K, V> *, int> &p_node) {
        CacheNode<K, V> *node = p_node.first;
        int freq = p_node.second;

        std::pair<CacheNode<K, V> *, CacheNode<K, V> *> &p = freq_map[freq];

        // if the given node is the only node in the list,
        // then erase the frequency from map
        // and increase minFreq by 1.
        if (p.first == node && p.second == node) {
            freq_map.erase(freq);
            if (minFreq == freq) {
                minFreq = freq + 1;
            }
        } else {
            // remove the given node from current freq linked list
            CacheNode<K, V> *prev = node->prev;
            CacheNode<K, V> *next = node->next;
            node->prev = nullptr;
            node->next = nullptr;

            if (prev) {
                prev->next = next;
            } else {
                p.first = next;
            }

            if (next) {
                next->prev = prev;
            } else {
                p.second = prev;
            }
        }
        push(freq + 1, node);
        p_node.second++;
    }

    /**
     * @brief pop the last node in the least frequently used linked list
     */
    void pop() {
        std::pair<CacheNode<K, V> *, CacheNode<K, V> *> &p = freq_map[minFreq];

        // if there is only one node
        // remove the node and erase
        // the frequency from freq_map
        if (p.first == p.second) {
            delete p.first;
            freq_map.erase(minFreq);
            return;
        }

        // remove the last node in the linked list
        CacheNode<K, V> *temp = p.second;
        p.second = temp->prev;
        p.second->next = nullptr;
        delete temp;
    }

 public:
    /**
     * @brief upsert a key-value pair
     * @param key key of the key-value pair
     * @param value value of the key-value pair
     */
    void put(K key, V value) {
        // update the value if key already exists
        if (node_map.count(key)) {
            node_map[key].first->data.second = value;
            inc_freq(node_map[key]);
            return;
        }

        // if the cache is full
        // remove the least frequently used item
        if (node_map.size() == _capacity) {
            node_map.erase(freq_map[minFreq].second->data.first);
            pop();
        }

        // insert the new node and set minFreq to 1
        CacheNode<K, V> *node = new CacheNode<K, V>({key, value});
        node_map[key] = {node, 1};
        minFreq = 1;
        push(1, node);
    }

    /**
     * @brief get the value of the key-value pair if exists
     * @param key key of the key-value pair
     * @return the value mapped to the given key
     * @exception exception is thrown if the key is not present in the cache
     */
    V get(K key) {
        if (!node_map.count(key)) {
            throw std::exception("key is not present in the cache");
        }

        // increase the frequency and return the value
        V value = node_map[key].first->data.second;
        inc_freq(node_map[key]);
        return value;
    }

    /**
     * @brief Returns the number of items present in the cache.
     * @return number of items in the cache
     */
    int size() { return node_map.size(); }

    /**
     * @brief Returns the total capacity of the cache
     * @return Total capacity of the cache
     */
    int capacity() { return _capacity; }

    /**
     * @brief returns true if the cache is empty, false otherwise.
     * @return true if the cache is empty, false otherwise.
     */
    bool empty() { return node_map.size() == 0; }

    /**
     * @brief destructs the cache, iterates on the map and deletes every node
     * present in the cache.
     */
    ~LFUCache() {
        auto it = node_map.begin();
        while (it != node_map.end()) {
            delete it->second.first;
            it++;
        }
    }
};
}  // namespace Cache
