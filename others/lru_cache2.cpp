/**
 * @file
 * @brief Implementation for [LRU Cache]
 * (https://en.wikipedia.org/wiki/Cache_replacement_policies#:~:text=Least%20Recently%20Used%20(LRU))
 *
 * @details
 * LRU discards the least recently used value.
 * Data structures used - doubly linked list and unordered_map
 *
 * unordered_map maps the key to the address of the node of the linked list.
 * If the element is accessed, the element is moved to the beginning of the
 * linked list.
 *
 * When the cache is full, the last element in the linked list is popped.
 *
 * @author [Karan Sharma](https://github.com/deDSeC00720)
 */

#include <cassert>        // for assert
#include <cstdint>        // for std::uint32_t
#include <iostream>       // for std::cout
#include <unordered_map>  // for std::unordered_map

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
 * @tparam T type of the data of the node
 */
template <typename T>
class D_Node {
 public:
    T data;           ///< data of the node
    D_Node<T> *prev;  ///< previous node in the doubly linked list
    D_Node<T> *next;  ///< next node in the doubly linked list

    explicit D_Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename K, typename V>
using CacheNode = D_Node<std::pair<K, V>>;

/**
 * @class
 * @brief LRUCache
 * @tparam K type of key in the LRU
 * @tparam V type of value in the LRU
 */
template <typename K, typename V>
class LRUCache {
    CacheNode<K, V> *head;    ///< head of the doubly linked list
    CacheNode<K, V> *tail;    ///< tail of the doubly linked list
    std::uint32_t _capacity;  ///< maximum capacity of the cache

    std::unordered_map<K, CacheNode<K, V> *>
        node_map;  ///< maps the key to the node address

 public:
    /**
     * @brief Constructor, Initialize the head and tail pointers to nullptr and
     * initialize the _capacity of the cache
     * @param _capacity Total capacity of the cache
     */
    explicit LRUCache(int _capacity)
        : head(nullptr), tail(nullptr), _capacity(_capacity) {}

 private:
    /**
     * @brief push the node to the front of the linked list.
     * @param node_ptr the node to be pushed
     */
    void push_front(CacheNode<K, V> *node_ptr) {
        if (!head) {
            head = node_ptr;
            tail = node_ptr;
            return;
        }

        node_ptr->next = head;
        head->prev = node_ptr;
        head = node_ptr;
    }

    /**
     * @brief move the existing node in the list to the beginning of the list.
     * @param node_ptr node to be moved to the beginning.
     */
    void make_recent(CacheNode<K, V> *node_ptr) {
        if (head == node_ptr) {
            return;
        }

        CacheNode<K, V> *prev = node_ptr->prev;
        CacheNode<K, V> *next = node_ptr->next;

        prev->next = next;
        if (next) {
            next->prev = prev;
        } else {
            tail = prev;
        }

        node_ptr->prev = nullptr;
        node_ptr->next = nullptr;
        push_front(node_ptr);
    }

    /**
     * @brief pop the last node in the linked list.
     */
    void pop_back() {
        if (!head) {
            return;
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        CacheNode<K, V> *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
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
            node_map[key]->data.second = value;
            make_recent(node_map[key]);
            return;
        }

        // if the cache is full
        // remove the least recently used item
        if (node_map.size() == _capacity) {
            node_map.erase(tail->data.first);
            pop_back();
        }

        CacheNode<K, V> *newNode = new CacheNode<K, V>({key, value});

        node_map[key] = newNode;
        push_front(newNode);
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

        // move node to the beginning of the list
        V value = node_map[key]->data.second;
        make_recent(node_map[key]);
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
     * @brief returns whether the cache is empty or not
     * @return true if the cache is empty, false otherwise.
     */
    bool empty() const { return node_map.empty(); }

    /**
     * @brief destructs the cache, iterates on the map and deletes every node
     * present in the cache.
     */
    ~LRUCache() {
        auto it = node_map.begin();
        while (it != node_map.end()) {
            delete it->second;
            ++it;
        }
    }
};
}  // namespace Cache
}  // namespace others

/**
 * @brief self test implementations
 * @return void
 */
static void test() {
    others::Cache::LRUCache<int, int> cache(5);

    // test the initial state of the cache
    assert(cache.size() == 0);
    assert(cache.capacity() == 5);
    assert(cache.empty());

    // test insertion in the cache
    cache.put(1, 10);
    cache.put(-2, 20);

    // test the state of cache after inserting some items
    assert(cache.size() == 2);
    assert(cache.capacity() == 5);
    assert(!cache.empty());

    // test getting items from the cache
    assert(cache.get(1) == 10);
    assert(cache.get(-2) == 20);

    cache.put(-3, -30);
    cache.put(4, 40);
    cache.put(5, -50);
    cache.put(6, 60);

    // test the state after inserting more items than the capacity
    assert(cache.size() == 5);
    assert(cache.capacity() == 5);
    assert(!cache.empty());

    // fetching 1 throws runtime_error
    // as 1 was evicted being the least recently used
    // when 6 was added
    try {
        cache.get(1);
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) == "key is not present in the cache");
    }

    // test retrieval of all items in the cache
    assert(cache.get(-2) == 20);
    assert(cache.get(-3) == -30);
    assert(cache.get(4) == 40);
    assert(cache.get(5) == -50);
    assert(cache.get(6) == 60);

    std::cout << "test - passed\n";
}

/**
 * @brief main function
 * @return 0 on exit
 */
int main() {
    test();  // run the self test implementation
    return 0;
}
