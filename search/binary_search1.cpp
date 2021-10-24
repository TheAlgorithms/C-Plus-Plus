/**
 * @file
 * @brief Implementation of the [Binary
 * Search](https://en.wikipedia.org/wiki/Binary_search_algorithm) Binary search
 * algorithm is an efficient algorithm to find the index of a key in a sorted
 * array. It works by repeatedly comparing the key with the middle element of
 * the array and narrowing down the range based on the result of comparison. If
 * the given key is less than the middle element, search repeats with the left
 * part of the array and vice versa. The running time of the algorithm in worst
 * case is logarithmic.
 * @author [Mohammad Golzar](https://github.com/m-golzar)
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <string>    /// for std::string
#include <vector>    /// for std::vector

/**
 * @namespace search
 * @brief Searching algorithms
 */
namespace search {
/**
 * @namespace binary_search
 * @brief Functions for the [Binary
 * Search](https://en.wikipedia.org/wiki/Binary_search_algorithm) implementation
 */
namespace binary_search {

/** binary_search function
 * \tparam Container type of a container to search, Container must support ([])
 * operator and size() method.
 * \tparam Key the key type, Key must support (== && <) operators.
 * \param container a container to search in it's elements.
 * \param key a key to search for
 * \returns -1 if there is no matched key in the container or
 * index of the key in the container if found.
 */
template <typename Container, typename Key>
size_t binary_search(const Container& container, const Key& key) {
    size_t right_limit = container.size() - 1;
    size_t left_limit = 0;
    while (left_limit <= right_limit) {
        // calculate middle index of the range in current iteration.
        size_t middle = left_limit + (right_limit - left_limit) / 2;
        // in case we have found the key, just return the index.
        if (key == container[middle]) {
            return middle;
        }
        // if desired key is less than the key at the middle index, it should
        // be located in left side of the middle index so adjust the range
        // right limit to search left side in the next iteration.
        else if (key < container[middle]) {
            right_limit = middle - 1;
        }
        // if desired key is greater than the key at the middle index, it should
        // be located in right side of the middle index so adjust the range
        // left limit to search right side in the next iteration.
        else {
            left_limit = middle + 1;
        }
    }
    // return -1 in case we did not find the key.
    return -1;
}
}  // namespace binary_search
}  // namespace search

/**
 * @namespace test_classes
 * @brief classes for testing the binary_search<> function
 * implementation
 */
namespace binary_search_test {

/**
 * @brief sample class implemented to show the usage of the algorithm with user
 *defined types.
 *
 * ContainerClass class is a simple user defined container to show the usage of
 * binary_search algorithm. please note that ContainerClass class is implemented
 * just for test purposes.
 */
template <typename T>
class ContainerClass {
 public:
    explicit ContainerClass() = default;
    ;
    void push_back(const T& element) { m_elements.push_back(element); }
    size_t size() const { return m_elements.size(); }
    T& operator[](size_t index) { return m_elements[index]; }
    const T& operator[](size_t index) const { return m_elements[index]; }

 private:
    std::vector<T> m_elements{};
};

/**
 *@brief sample class implemented to show the usage of algorithm with user
 *defined types.
 *
 * KeyClass class is a simple user defined data type to show the usage of
 *binary_search algorithm. please note that KeyClass class is implemented just
 *for test purposes.
 */
class KeyClass {
    friend std::ostream& operator<<(const KeyClass& key, std::ostream& rhs);
    friend bool operator==(const KeyClass& lhs, const KeyClass& rhs);
    friend bool operator<(const KeyClass& lhs, const KeyClass& rhs);

 public:
    explicit KeyClass(int value = 0) : m_value(value){};
    int get() const { return m_value; }

 private:
    int m_value = 0;
};

/** operator << implementation for class [KeyClass]
 */
std::ostream& operator<<(const KeyClass& key, std::ostream& rhs) {
    return rhs << key.get();
}

/** operator == implementation for class [KeyClass]
 */
bool operator==(const KeyClass& lhs, const KeyClass& rhs) {
    return (lhs.get() == rhs.get());
}

/** operator < implementation for class [KeyClass]
 */
bool operator<(const KeyClass& lhs, const KeyClass& rhs) {
    return (lhs.get() < rhs.get());
}

/**
 *@brief this class is implemented to encapsulate sample test cases
 */
class TestCases {
 private:
    void log(const std::string& msg) { std::cout << msg << std::endl; }

 public:
    /**
     *@brief running test cases one by one
     */
    void run_tests() {
        test_case1();
        test_case2();
        test_case3();
        test_case4();
    }
    /**
     *@brief test case for running the binary_search algorithm on 'std::array'
     *with integer keys
     */
    void test_case1() {
        using Array = std::array<int, 10>;
        Array array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 5;
        size_t result =
            search::binary_search::binary_search<Array, int>(array, key);
        log("Checking assert expression...");
        assert(result == 4);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 1_1 PASS!");
        key = 20;
        result = search::binary_search::binary_search<Array, int>(array, key);
        log("Checking assert expression...");
        assert(result == -1);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 1_2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
    /**
     *@brief test case for running the binary_search algorithm on 'std::vector'
     *with integer keys
     */
    void test_case2() {
        using Vector = std::vector<int>;
        Vector vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 5;
        size_t result =
            search::binary_search::binary_search<Vector, int>(vec, key);
        log("Checking assert expression...");
        assert(result == 4);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 2_1 PASS!");
        key = 20;
        result = search::binary_search::binary_search<Vector, int>(vec, key);
        log("Checking assert expression...");
        assert(result == -1);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 2_2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
    /**
     *@brief test case for running the binary_search algorithm on 'std::vector'
     *with user defined KeyClass keys
     */
    void test_case3() {
        using Vector = std::vector<KeyClass>;
        Vector vec;
        for (int i = 1; i < 11; ++i) {
            vec.push_back(KeyClass(i));
        }
        KeyClass key(5);
        size_t result =
            search::binary_search::binary_search<Vector, KeyClass>(vec, key);
        log("Checking assert expression...");
        assert(result == 4);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 3_1 PASS!");
        key = KeyClass(20);
        result =
            search::binary_search::binary_search<Vector, KeyClass>(vec, key);
        log("Checking assert expression...");
        assert(result == -1);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 3_2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }

    /**
     *@brief test case for running the binary_search algorithm on user defined
     *ContainerClasss container with 'std::string' keys
     */
    void test_case4() {
        using Container = ContainerClass<std::string>;
        std::vector<std::string> strings{"A", "B", "C", "D", "E",
                                         "F", "G", "H", "I", "J"};
        Container container;
        for (const auto& str : strings) {
            container.push_back(str);
        }
        std::string key = "E";
        int result =
            search::binary_search::binary_search<Container, std::string>(
                container, key);
        log("Checking assert expression...");
        assert(result == 4);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 4_1 PASS!");
        key = "O";
        result = search::binary_search::binary_search<Container, std::string>(
            container, key);
        log("Checking assert expression...");
        assert(result == -1);
        log("Assertion check passed!");
        log("[PASS] : TEST CASE 4_2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
};

}  // namespace binary_search_test

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char const* argv[]) {
    binary_search_test::TestCases test;
    test.run_tests();  // run self-test implementations
    return 0;
}
