/**
 * @file
 * @author [@Arctic2333](https://github.com/Arctic2333)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Implementation of [Trie](https://en.wikipedia.org/wiki/Trie) data
 * structure for English alphabets in small characters.
 * @see trie_modern.cpp
 */
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

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

    /**
     * @brief Check if this node has any children
     * @returns `true` if at least one child exists
     * @returns `false` if no children exist
     */
    bool hasChildren() const {
        for (int i = 0; i < NUM_CHARS << 1; i++) {
            if (arr[i]) {
                return true;
            }
        }
        return false;
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
     * @brief Removes the string from the trie.
     * If the string is a prefix of another word, only unmarks the end
     * of word flag. Nodes are only pruned when they have no children
     * and are not the end of another word.
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
            return true;
        }
        int j = char_to_int(str[index]);
        if (!arr[j]) {
            return false;
        }
        bool var = arr[j]->deleteString(str, index + 1);
        if (var) {
            // Only remove the child node if it has no children
            // and is not the end of another word
            if (!arr[j]->isEndofWord && !arr[j]->hasChildren()) {
                arr[j].reset();
            }
            if (isEndofWord) {
                return false;
            } else {
                return !hasChildren();
            }
        }
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

    // Test fix: deleting "Hello" should not delete "Hell"
    data_structures::trie root2;
    root2.insert("Hell");
    root2.insert("Hello");

    assert(root2.search("Hell", 0));
    assert(root2.search("Hello", 0));
    std::cout << "Before delete - Hell: " << root2.search("Hell", 0)
              << ", Hello: " << root2.search("Hello", 0) << "\n";

    root2.deleteString("Hello", 0);

    assert(root2.search("Hell", 0));   // Hell must still exist
    assert(!root2.search("Hello", 0)); // Hello must be gone
    std::cout << "After delete  - Hell: " << root2.search("Hell", 0)
              << ", Hello: " << root2.search("Hello", 0) << "\n";

    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    test();
    return 0;
}