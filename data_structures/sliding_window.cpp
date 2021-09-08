/*
 * @brief Sliding window implementation
 *
 * @details A sliding window is a fixed-size FIFO data structure.
 *         This implementation uses the vector class of the standard library.
 *
 *
 * @author [Jxtopher](https://github.com/Jxtopher)
 */

#include <algorithm>  /// for std::count
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {

template <typename T>
class Sliding_window : private std::vector<T> {
 public:
    explicit Sliding_window(unsigned int window_size)
        : m_window_size(window_size) {}

    /**
     * @brief add item
     */
    void add_item(T item) {
        if (this->size() >= m_window_size) {
            this->pop_back();
        }

        this->insert(this->begin(), item);
    }

    /**
     * @brief get the last added object
     */
    T get_item() const { return (*this->begin()); }

    /**
     * @brief returns an iterator to the end
     */
    typename Sliding_window::const_iterator cend() const {
        return this->std::vector<T>::cend();
    }

    /**
     * @brief returns an iterator to the end
     */
    typename Sliding_window::const_iterator end() const {
        return this->std::vector<T>::end();
    }

    /**
     * @brief returns an iterator to the end
     */
    typename Sliding_window::iterator end() {
        return this->std::vector<T>::end();
    }

    /**
     * @brief returns an iterator to the beginning
     */
    typename Sliding_window::const_iterator cbegin() const {
        return this->std::vector<T>::cbegin();
    }

    /**
     * @brief returns an iterator to the beginning
     */
    typename Sliding_window::iterator begin() {
        return this->std::vector<T>::begin();
    }

    /**
     * @brief returns an iterator to the beginning
     */
    typename Sliding_window::const_iterator begin() const {
        return this->std::vector<T>::begin();
    }

    /**
     * @brief displays the contents of the sliding window
     */
    friend std::ostream& operator<<(std::ostream& out,
                                    const Sliding_window<T>& sliding_window) {
        for (const auto& item : sliding_window) out << item << " ";
        return out;
    }

    /**
     * @brief returns the number of elements
     */
    unsigned int size() const { return this->std::vector<T>::size(); }

    /**
     * @brief checks whether the container is empty
     */
    bool empty() const { return this->std::vector<T>::empty(); }

    /**
     * @brief clears the contents
     */
    void clear() const { this->std::vector<T>::clear(); }

 private:
    unsigned int m_window_size;
};  // class Sliding_window
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::Sliding_window<int> sliding_window(5);
    sliding_window.add_item(5);
    sliding_window.add_item(45);
    sliding_window.add_item(28);
    sliding_window.add_item(85);
    sliding_window.add_item(68);
    sliding_window.add_item(21);
    sliding_window.add_item(68);
    sliding_window.add_item(2);
    sliding_window.add_item(4);
    assert(sliding_window.get_item() == 4);
    assert(sliding_window.size() == 5);

    // Sum of sliding window elements
    int sum = 0;
    for (const auto& item : sliding_window) sum += item;
    assert(sum = 163);
}

/**
 * @brief Main function
 * @returns EXIT_SUCCESS on exit
 */
int main() {
    test();  // run self-test implementations

    data_structures::Sliding_window<int> sliding_window(5);
    sliding_window.add_item(68);
    sliding_window.add_item(2);
    sliding_window.add_item(4);
    sliding_window.add_item(5);
    sliding_window.add_item(45);
    sliding_window.add_item(28);
    sliding_window.add_item(85);
    std::cout << "Contents of the sliding window : " << sliding_window
              << std::endl;

    return EXIT_SUCCESS;
}
