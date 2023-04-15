/**
 * @file
 * @brief Unit testings for `AvlTreeMap<K, V>`
 * @details This file contains the unit testings for `AvlTreeMap<K, V>`
 *  including insertions, deletions and queries. These tests cover all
 *  the code that contains the main algorithmic logic.
 *  If a unit test succeeds, it will print "testName: success",
 *  otherwise, it will print "testName: failed `[reason]`".
 * @author [r.ivance](https://github.com/RIvance)
 * @see avltree_map.hpp
 */

#include "avltree_map.hpp"  /// for `AvlTreeMap<K, V>`

#include <iostream>         /// for IO operations
#include <set>              /// for `std::set`

/**
 * @brief The exception thrown when an assertion failed
 */
struct AssertionFailed : public std::exception
{
    const char* reason;
    explicit AssertionFailed(const char* reason) : reason(reason) {}
    const char* what() const noexcept override { return reason; }
};

/**
 * @brief Assert that two values are equal
 */
#define ASSERT_EQUAL(actual, ...) do { \
    if (!((actual) == (typeof(actual))(__VA_ARGS__))) throw AssertionFailed(#actual" != "#__VA_ARGS__); \
} while (false)

/**
 * @brief Assert if the code throws an exception
 */
#define ASSERT_THROW(code, Ex) do { \
    try { code; } \
    catch (Ex & e) { break; } \
    throw AssertionFailed(#Ex" is not thrown"); \
} while (false)

/**
 * @brief Run a test
 */
#define RUN_TEST(test) do { \
    try { test(); std::cout << #test":\tsucceeded" << std::endl; } \
    catch (std::exception & ex) { std::cout << #test":\tfailed `" << ex.what() << "`" << std::endl; } \
} while (false)

/**
 * @brief Test if two vectors are equal
 * @tparam T the type of the elements in the vectors
 * @param actual
 * @param expected
 * @returns true if the two vectors are equal, false otherwise
 */
template <typename T>
bool operator==(const std::vector<T> & actual, const std::vector<T> & expected)
{
    if (actual.size() != expected.size()) return false;
    for (int i = 0; i < actual.size(); i++) {
        if (actual[i] != expected[i]) {
            return false;
        }
    }
    return true;
}

using TestMap = AvlTreeMap<int, int>;   ///< The type of the map used in the tests

/**
 * @brief Initialize a map with the given keys
 * @param keys
 * @returns void
 */
TestMap initWithKeys(const std::vector<int> & keys)
{
    TestMap map;
    for (const auto & key : keys) {
        map.insert(key, key);
    }
    return map;
}

/**
 * @brief Test AvlTreeMap<K, V>::insert
 * @returns void
 */
void testInsert()
{
    TestMap map;
    std::vector<int> keys = { 3, 7, 5, 0, 9, 4, 6, 2, 1, 8 };
    for (const auto & key : keys) {
        map.insert(key, key);
    }
    ASSERT_EQUAL(map.toEntryList(), TestMap::EntryList({
        {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4},
        {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9},
    }));
}

/**
 * @brief Test AvlTreeMap<K, V>::operator[]
 */
void testAssign()
{
    TestMap map;
    std::vector<int> keys = { 3, 7, 5, 0, 9, 4, 6, 2, 1, 8 };
    for (const auto & key : keys) {
        map[key] = key;
    }
    map[6] = 60;
    map[2] = 20;
    map[5] = 50;
    map[4] = 40;
    ASSERT_EQUAL(map.toEntryList(), TestMap::EntryList({
        {0, 0}, {1, 1}, {2, 20}, {3, 3}, {4, 40},
        {5, 50}, {6, 60}, {7, 7}, {8, 8}, {9, 9},
    }));
}

/**
 * @brief Test AvlTreeMap<K, V>::remove
 * @returns void
 */
void testRemove()
{
    TestMap map = initWithKeys({ 1, 5, 9, 7, 2, 3, 8, 4, 0, 6 });
    std::vector<int> removes = { 2, 8, 0, 4, 6 };
    for (const auto & item: removes) {
        map.remove(item);
    }
    auto result = AvlTreeMap<int, int>::EntryList();
    ASSERT_EQUAL(map.toEntryList(), TestMap::EntryList({
        {1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9}
    }));
}

/**
 * @brief Test AvlTreeMap<K, V>::get
 * @returns void
 */
void testGet()
{
    TestMap map = initWithKeys({ 3, 7, 5, 0, 9, 4, 6, 2, 1, 8 });
    using NoSuchMappingException = AvlTreeMap<int, int>::NoSuchMappingException;
    ASSERT_EQUAL(map.get(8), 8);
    ASSERT_EQUAL(map.get(4), 4);
    ASSERT_EQUAL(map.get(9), 9);
    ASSERT_EQUAL(map.get(3), 3);
    ASSERT_THROW(map.get(10), NoSuchMappingException);
    ASSERT_THROW(map.get(-1), NoSuchMappingException);
    ASSERT_THROW(map.get(256), NoSuchMappingException);
}

/**
 * @brief Test AvlTreeMap<K, V>::getOrInsert
 * @returns void
 */
void testGetOrInsert()
{
    TestMap map = initWithKeys({ 9, 3, 7, 1, 2, 8 });
    ASSERT_EQUAL(map.getOrInsert(2, -2), 2);
    ASSERT_EQUAL(map.getOrInsert(8, -8), 8);
    ASSERT_EQUAL(map.getOrInsert(5, -5), -5);
    ASSERT_EQUAL(map.getOrInsert(6, -6), -6);
}

/**
 * @brief Test AvlTreeMap<K, V>::size
 * @returns void
 */
void testSize()
{
    TestMap map = initWithKeys({ 3, 7, 5, 0, 9, 4, 6, 2, 1, 8 });
    map.remove(8);
    map.remove(9);
    map.remove(0);
    ASSERT_EQUAL(map.empty(), false);
    ASSERT_EQUAL(map.size(), 7);
}

/**
 * @brief Test AvlTreeMap<K, V>::clear
 * @returns void
 */
void testClear()
{
    TestMap map = initWithKeys({ 3, 7, 5, 0, 9, 4, 6, 2, 1, 8 });
    map.clear();
    ASSERT_EQUAL(map.empty(), true);
}

/**
 * @brief Test AvlTreeMap<K, V>::getAndRemove
 * @returns void
 */
void testGetAndRemove()
{
    TestMap map = initWithKeys({ 3, 7, 5, 0, 9, 4, 6, 2, 1, 8 });
    std::vector<int> removes = { 7, 0, 3, 5, 1 };
    for (const auto & item: removes) {
        ASSERT_EQUAL(map.getAndRemove(item), item);
    }
    auto result = AvlTreeMap<int, int>::EntryList();
    ASSERT_EQUAL(map.toEntryList(), TestMap::EntryList({
        {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9}
    }));
}

/**
 * @brief Test AvlTreeMap<K, V>::removeAll
 * @returns void
 */
void testRemoveAll()
{
    TestMap map = initWithKeys({ 3, 7, 5, 0, 9, 4, 6, 2, 1, 8 });
    map.removeAll([](int k, int v) -> bool {
        return k % 2 != 0;
    });
    auto result = AvlTreeMap<int, int>::EntryList();
    ASSERT_EQUAL(map.toEntryList(), TestMap::EntryList({
        {0, 0}, {2, 2}, {4, 4}, {6, 6}, {8, 8}
    }));
}

/**
 * @brief Test AvlTreeMap<K, V>::getCeilingEntry
 * @returns void
 */
void testGetCeilingEntry()
{
    TestMap map = initWithKeys({ 1, 5, 9, 4, 0, 6 });
    ASSERT_EQUAL(map.getCeilingEntry(5).key, 5);
    ASSERT_EQUAL(map.getCeilingEntry(6).key, 6);
    ASSERT_EQUAL(map.getCeilingEntry(2).key, 4);
    ASSERT_EQUAL(map.getCeilingEntry(7).key, 9);
    ASSERT_EQUAL(map.getCeilingEntry(-1).key, 0);
    ASSERT_THROW(map.getCeilingEntry(100), TestMap::NoSuchMappingException);
}

/**
 * @brief Test AvlTreeMap<K, V>::getFloorEntry
 * @returns void
 */
void testGetFloorEntry()
{
    TestMap map = initWithKeys({ 1, 5, 9, 4, 0, 6 });
    ASSERT_EQUAL(map.getFloorEntry(5).key, 5);
    ASSERT_EQUAL(map.getFloorEntry(6).key, 6);
    ASSERT_EQUAL(map.getFloorEntry(2).key, 1);
    ASSERT_EQUAL(map.getFloorEntry(7).key, 6);
    ASSERT_EQUAL(map.getFloorEntry(100).key, 9);
    ASSERT_THROW(map.getFloorEntry(-1), TestMap::NoSuchMappingException);
}

/**
 * @brief Test AvlTreeMap<K, V>::getHeigherEntry
 * @returns void
 */
void testGetHigherEntry()
{
    TestMap map = initWithKeys({ 1, 5, 9, 4, 0, 6 });
    ASSERT_EQUAL(map.getHigherEntry(5).key, 6);
    ASSERT_EQUAL(map.getHigherEntry(6).key, 9);
    ASSERT_EQUAL(map.getHigherEntry(2).key, 4);
    ASSERT_EQUAL(map.getHigherEntry(7).key, 9);
    ASSERT_EQUAL(map.getHigherEntry(-1).key, 0);
    ASSERT_THROW(map.getHigherEntry(100), TestMap::NoSuchMappingException);
}

/**
 * @brief Test AvlTreeMap<K, V>::getLowerEntry
 * @returns void
 */
void testGetLowerEntry()
{
    TestMap map = initWithKeys({ 1, 5, 9, 4, 0, 6 });
    ASSERT_EQUAL(map.getLowerEntry(5).key, 4);
    ASSERT_EQUAL(map.getLowerEntry(6).key, 5);
    ASSERT_EQUAL(map.getLowerEntry(2).key, 1);
    ASSERT_EQUAL(map.getLowerEntry(7).key, 6);
    ASSERT_EQUAL(map.getLowerEntry(100).key, 9);
    ASSERT_THROW(map.getLowerEntry(-1), TestMap::NoSuchMappingException);
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main()
{
    RUN_TEST(testInsert);
    RUN_TEST(testAssign);
    RUN_TEST(testRemove);
    RUN_TEST(testGet);
    RUN_TEST(testSize);
    RUN_TEST(testClear);
    RUN_TEST(testGetOrInsert);
    RUN_TEST(testGetAndRemove);
    RUN_TEST(testRemoveAll);
    RUN_TEST(testGetCeilingEntry);
    RUN_TEST(testGetFloorEntry);
    RUN_TEST(testGetHigherEntry);
    RUN_TEST(testGetLowerEntry);
}
