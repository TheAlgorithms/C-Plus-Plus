/**
 * @file
 * @author [@Arctic2333](https://github.com/Arctic2333)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Implementation of [Trie](https://en.wikipedia.org/wiki/Trie) data
 * structure for English alphabets in small characters.
 * @note the function ::data_structure::trie::deleteString might be erroneous
 * @see trie_modern.cpp
 */
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/** \namespace data_structures
 * \brief Data-structure algorithms
 */
namespace data_structures {
/**
 * @brief [Trie](https://en.wikipedia.org/wiki/Trie) implementation for
 * small-case English alphabets `a-z`
 */
class trie {
 private:
    static constexpr uint8_t NUM_CHARS = 26;  ///< Number of alphabets
    /** @brief Recursive tree nodes as an array of shared-pointers */
    std::array<std::shared_ptr<trie>, NUM_CHARS << 1> arr;
    bool isEndofWord = false;  ///< identifier if a node is terminal node

    /**
     * @brief Convert a character to integer for indexing
     *
     * @param ch character to index
     * @return unsigned integer index
     */
    uint8_t char_to_int(const char& ch) const {
        if (ch >= 'A' && ch <= 'Z') {
            return ch - 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            return ch - 'a' + NUM_CHARS;
        }

        std::cerr << "Invalid character present. Exiting...";
        std::exit(EXIT_FAILURE);
        return 0;
    }

    /** search a string exists inside a given root trie
     * @param str string to search for
     * @param index start index to search from
     * @returns `true` if found
     * @returns `false` if not found
     */
    bool search(const std::shared_ptr<trie>& root, const std::string& str,
                int index) {
        if (index == str.length()) {
            if (!root->isEndofWord) {
                return false;
            }
            return true;
        }
        int j = char_to_int(str[index]);
        if (!root->arr[j]) {
            return false;
        }
        return search(root->arr[j], str, index + 1);
    }

 public:
    trie() = default;  ///< Class default constructor

    /** insert string into the trie
     * @param str String to insert in the tree
     */
    void insert(const std::string& str) {
        std::shared_ptr<trie> root(nullptr);

        for (const char& ch : str) {
            int j = char_to_int(ch);
            if (root) {
                if (root->arr[j]) {
                    root = root->arr[j];
                } else {
                    std::shared_ptr<trie> temp(new trie());
                    root->arr[j] = temp;
                    root = temp;
                }
            } else if (arr[j]) {
                root = arr[j];
            } else {
                std::shared_ptr<trie> temp(new trie());
                arr[j] = temp;
                root = temp;
            }
        }
        root->isEndofWord = true;
    }

    /** search a string exists inside the trie
     * @param str string to search for
     * @param index start index to search from
     * @returns `true` if found
     * @returns `false` if not found
     */
    bool search(const std::string& str, int index) {
        if (index == str.length()) {
            if (!isEndofWord) {
                return false;
            }
            return true;
        }
        int j = char_to_int(str[index]);
        if (!arr[j]) {
            return false;
        }
        return search(arr[j], str, index + 1);
    }

    /**
     * removes the string if it is not a prefix of any  other
     * string, if it is then just sets the ::data_structure::trie::isEndofWord
     * to false, else removes the given string
     * @note the function ::data_structure::trie::deleteString might be
     * erroneous
     * @todo review the function ::data_structure::trie::deleteString and the
     * commented lines
     * @param str string to remove
     * @param index index to remove from
     * @returns `true` if successful
     * @returns `false` if unsuccessful
     */
    bool deleteString(const std::string& str, int index) {
        if (index == str.length()) {
            if (!isEndofWord) {
                return false;
            }
            isEndofWord = false;
            // following lines - possible source of error?
            // for (int i = 0; i < NUM_CHARS; i++)
            //     if (!arr[i])
            //         return false;
            return true;
        }
        int j = char_to_int(str[index]);
        if (!arr[j]) {
            return false;
        }
        bool var = deleteString(str, index + 1);
        if (var) {
            arr[j].reset();
            if (isEndofWord) {
                return false;
            } else {
                int i = 0;
                for (i = 0; i < NUM_CHARS; i++) {
                    if (arr[i]) {
                        return false;
                    }
                }
                return true;
            }
        }

        /* should not return here */
        std::cout << __func__ << ":" << __LINE__
                  << "Should not reach this line\n";
        return false;
    }
};
}  // namespace data_structures

/**
 * @brief Testing function
 * @returns void
 */
static void test() {
    data_structures::trie root;
    root.insert("Hello");
    root.insert("World");

    assert(!root.search("hello", 0));
    std::cout << "hello - " << root.search("hello", 0) << "\n";

    assert(root.search("Hello", 0));
    std::cout << "Hello - " << root.search("Hello", 0) << "\n";

    assert(!root.search("Word", 0));
    std::cout << "Word - " << root.search("Word", 0) << "\n";

    assert(root.search("World", 0));
    std::cout << "World - " << root.search("World", 0) << "\n";

    // Following lines of code give erroneous output
    // root.deleteString("hello", 0);
    // assert(!root.search("hello", 0));
    // std::cout << "hello - " << root.search("world", 0) << "\n";
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    test();

    return 0;
}
