/**
 * @file
 * @brief An implementation of
 * [LRU
 * Cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)).
 * Lru is a part of cache algorithms (also frequently called cache replacement
 * algorithms or cache replacement policies).
 *
 * ### Logic
 *      * Discards the least recently used items first.
 *      * This algorithm requires keeping track of what was used when, which is
 * expensive if one wants to make sure the algorithm always discards the least
 * recently used item.
 *      * General implementations of this technique require keeping "age bits"
 * for cache-lines and track the "Least Recently Used" cache-line based on
 * age-bits.
 *      * In such an implementation, every time a cache-line is used, the age of
 * all other cache-lines changes
 *
 * ### Algorithm explanation
 *      For a cache of page frame x:
 *          * Check if the page is present in cache.
 *          * If not present, then check is the cache is full or not:
 *          * If the cache is full, REMOVE the last element from the cache.
 *          * If the element is present in cache, then shift that element to
 * first position in cache from its original position.
 *              * This way you can keep the least recently used elements in the
 * last and most recently used in front of the cache.
 *
 *  Every time a requested page is  not found in cache, that is a miss or page
 * fault, and if the page is present in cache, then its a hit.
 *
 * ## Data Structure used
 *  * In the algorithm below we used two different data structure, one is linked
 * list and other one is a hash map
 *  * The linked list is used to contain the pages and the hash map contains the
 * pages and their address.
 *  * Every time a new page is requested, we first check in the hash map if the
 * page is present or not.
 *  * If not present, and the cache is full, we simply delete the last entry in
 * the cache.
 *  * If present, we shift that page from its current location to beginning of
 * the cache and update the address in hash map for that page.
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 * */

#include <cassert>        /// for assert
#include <iostream>       /// for IO Operations
#include <list>           /// for std::list
#include <unordered_map>  /// for std::unordered_map

/**
 * @namespace others
 * @brief Other algorithms
 */
namespace others {
/**
 * @namespace lru_cache
 * @brief Implementation of the [LRU caching
 * algorithm](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU))
 */
namespace lru_cache {
/**
 * @brief LRU cache class
 */
class LRUCache {
    uint64_t pageFrame;         ///< Page frame, or total size of the cache.
    std::list<uint64_t> cache;  ///< Cache linked list (using the STL)
    std::unordered_map<uint64_t, std::list<uint64_t>::iterator>
        pageMap;  ///< Hash map containing pages and their addresses

    uint64_t hits =
        0;  ///< Total number of hits, or total number of times a page
    ///< was found in cache.
    uint64_t pageFault = 0;  ///< Total number of miss/page fault, or total
                             ///< number of times a page was not found in cache

 public:
    /**
     * @brief Constructor, Initialize thee LRU class with page frame.
     * @param pf Page frame or total size of cache.
     * */
    explicit LRUCache(uint64_t pf) { pageFrame = pf; }

    /**
     * @brief Refer to a page, or request a page from memory.
     * @param page The page that you are referring to.
     * @returns void
     * */
    void refer(uint64_t page) {
        // If the page requested not in cache.
        if (pageMap.find(page) == pageMap.end()) {
            pageFault++;  ///< Increase the page fault by one.

            // Check if the cache is full
            if (cache.size() == pageFrame) {
                // delete the last page from cache
                uint64_t lastPage = cache.back();
                cache.pop_back();
                pageMap.erase(lastPage);
            }
        }
        // The requested page is in the cache
        else {
            hits++;
            // present in cache, erase from current position to bring in front
            cache.erase(pageMap[page]);
        }
        // Push it in the front of the cache and update the page reference in
        // page map.
        cache.push_front(page);
        pageMap[page] = cache.begin();
    }

    /**
     * @brief A function to display the current cache
     * @returns Void
     * */
    void display() {
        for (uint64_t &it : cache) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
    /**
     * @brief A function to get page hits
     * @returns int
     * */
    uint64_t getHits() const { return hits; }
    /**
     * @brief A function to get page fault
     * @returns int
     * */
    uint64_t getPageFault() const { return pageFault; }
};

}  // namespace lru_cache
}  // namespace others

namespace lru_tests {
/**
 * @brief A function to print given message on console.
 * @tparam T Type of the given message.
 * @returns void
 * */
template <typename T>
void log(T msg) {
    // It's just to avoid writing cout and endl
    std::cout << "[TESTS] : ---> " << msg << std::endl;
}

/**
 * @brief A simple test case
 * The assert statement will check expected hist and miss to resultant hits and
 * miss
 * @returns void
 * */
static void test_1() {
    uint64_t expected_hits = 2;
    uint64_t expected_pageFault = 4;

    log("Running Test-1...");

    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(5);
    cache.refer(1);
    cache.refer(4);
    cache.refer(5);

    log("Checking assert statement...");
    assert(cache.getHits() == expected_hits &&
           cache.getPageFault() == expected_pageFault);
    log("Assert successful!");
    log("Test-1 complete!");
}

/**
 * @brief A test case contains hits more than cache size
 * The assert statement will check expected hist and miss to resultant hits and
 * miss
 * @returns void
 * */
static void test_2() {
    uint64_t expected_hits = 4;
    uint64_t expected_pageFault = 2;

    log("Running Test-2...");

    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(1);
    cache.refer(1);
    cache.refer(1);
    cache.refer(1);
    cache.refer(5);

    log("Checking assert statement...");
    assert(cache.getHits() == expected_hits &&
           cache.getPageFault() == expected_pageFault);
    log("Assert successful!");
    log("Test-2 complete!");
}

/**
 * @brief A simple test case
 * The assert statement will check expected hist and miss to resultant hits and
 * miss
 * @returns void
 * */
static void test_3() {
    uint64_t expected_hits = 1;
    uint64_t expected_pageFault = 5;

    log("Running Test-3...");

    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(4);
    cache.refer(5);
    cache.refer(5);

    log("Checking assert statement...");
    assert(cache.getHits() == expected_hits &&
           cache.getPageFault() == expected_pageFault);
    log("Assert successful!");
    log("Test-3 complete!");
}

/**
 * @brief A function to invoke all test cases
 * @returns void
 * */
static void run_tests() {
    test_1();
    test_2();
    test_3();
    log("");
    log("TESTS COMPLETED!");
}
}  // namespace lru_tests

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    lru_tests::run_tests();

    // Usage
    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(4);
    cache.refer(5);
    cache.refer(5);

    cache.display();

    std::cout << "Hits: " << cache.getHits()
              << " Miss: " << cache.getPageFault() << std::endl;
    return 0;
}
