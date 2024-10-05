/**
 * @file
 * @brief Implementation for [LFU Cache]
 * (https://en.wikipedia.org/wiki/Least_frequently_used)
 *
 * @details
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

#include <cassert>        // for assert
#include <iostream>       // for IO operations
#include <unordered_map>  // for hash map

/**
 * @namespace
 * @brief Other algorithms
 */
namespace others {

/**
 * @namespace
 * @brief Cache algorithm
 */
namespace Cache {

/**
 * @class
 * @brief Node for a doubly linked list with data, prev and next pointers
 */
template <typename T>
class D_Node {
 public:
    T data;
    D_Node<T> *prev;
    D_Node<T> *next;

    explicit D_Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename K, typename V>
using CacheNode = D_Node<std::pair<K, V>>;

/**
 * @class
 * @brief LFUCache
 */
template <typename K, typename V>
class LFUCache {
    std::unordered_map<K, std::pair<CacheNode<K, V> *, int>>
        node_map;  ///< maps the key to the node address and frequency
    std::unordered_map<int, std::pair<CacheNode<K, V> *, CacheNode<K, V> *>>
        freq_map;  ///< maps the frequency to doubly linked list

    int minFreq;    ///< minimum frequency in the cache
    int _capacity;  ///< maximum capacity of the cache

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
        if (!freq_map.count(freq)) {
            freq_map[freq] = {node, node};
            return;
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
        ++p_node.second;
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
            throw std::runtime_error("key is not present in the cache");
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
    int size() const { return node_map.size(); }

    /**
     * @brief Returns the total capacity of the cache
     * @return Total capacity of the cache
     */
    int capacity() const { return _capacity; }

    /**
     * @brief returns true if the cache is empty, false otherwise.
     * @return true if the cache is empty, false otherwise.
     */
    bool empty() const { return node_map.empty(); }

    /**
     * @brief destructs the cache, iterates on the map and deletes every node
     * present in the cache.
     */
    ~LFUCache() {
        auto it = node_map.begin();
        while (it != node_map.end()) {
            delete it->second.first;
            ++it;
        }
    }
};
}  // namespace Cache
}  // namespace others

/**
 * @brief A simple test case
 * @return void
 */
void test1() {
    others::Cache::LFUCache<int, int> cache(5);
    assert(cache.size() == 0);
    assert(cache.capacity() == 5);
    assert(cache.empty());
    cache.put(1, 10);
    cache.put(-2, 20);

    assert(cache.size() == 2);
    assert(cache.capacity() == 5);
    assert(!cache.empty());

    cache.put(3, -30);
    cache.put(4, 40);
    cache.put(5, 50);
    cache.put(6, 60);

    assert(cache.size() == 5);
    assert(cache.capacity() == 5);
    assert(!cache.empty());

    std::cout << "test1 - passed\n";
}

/**
 * @brief A simple test case
 * @return void
 */
void test2() {
    others::Cache::LFUCache<int, int> cache(5);
    cache.put(-1, -10);
    cache.put(2, 20);
    cache.put(3, 30);

    assert(cache.get(-1) == -10);
    cache.get(2);
    cache.get(3);

    cache.put(4, 40);
    cache.put(5, 50);
    cache.put(6, 60);

    assert(cache.get(5) == 50);

    std::cout << "test2 - passed\n";
}

/**
 * @brief test method with 2 tests
 * @return void
 */
void test() {
    test1();
    test2();
}

/**
 * @brief main function
 * @return 0 on exit
 */
int main() {
    test();
    return 0;
}
