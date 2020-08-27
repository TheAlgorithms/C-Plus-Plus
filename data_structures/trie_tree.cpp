/**
 * @file
 * @author [@Arctic2333](https://github.com/Arctic2333)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Implementation of [Trie](https://en.wikipedia.org/wiki/Trie) data
 * structure for English alphabets in small characters.
 * @note the function ::trie::deleteString might be erroneous
 */
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/** \namespace data_structure
 * \brief Data-structure algorithms
 */
namespace data_structure {
static constexpr uint8_t NUM_CHARS = 26;  ///< Number of characters

/**
 * @brief Trie tree implementation for small-case English alphabets `a-z`
 * @note the function ::trie::deleteString might be erroneous
 * @todo review the function ::trie::deleteString and the commented lines
 */
class trie {
 private:
    /** Recursive tree nodes as an array of shared-pointers */
    std::array<std::shared_ptr<trie>, NUM_CHARS> arr;
    bool isEndofWord = false;  ///< identifier if a node is terminal node

    /** search a string exists inside a given root trie
     * @param str string to search for
     * @param index start index to search from
     * @returns `tre` if found
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
        int j = str[index] - 'a';
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
            int j = ch - 'a';
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
     * @returns `tre` if found
     * @returns `false` if not found
     */
    bool search(const std::string& str, int index) {
        if (index == str.length()) {
            if (!isEndofWord) {
                return false;
            }
            return true;
        }
        int j = str[index] - 'a';
        if (!arr[j]) {
            return false;
        }
        return search(arr[j], str, index + 1);
    }

    /**
     * removes the string if it is not a prefix of any  other
     * string, if it is then just sets the ::isEndofWord to false, else removes
     * the given string
     * @param str string to remove
     * @param index index to remove from
     * @returns `true` if successful
     * @returns `false` if unsuccessful
     */
    bool deleteString(const std::string& str, int index) {
        // std::shared_ptr<trie> root (nullptr);

        if (index == str.length()) {
            if (!isEndofWord) {
                return false;
            }
            isEndofWord = false;
            // for (int i = 0; i < NUM_CHARS; i++)
            //     if (root->arr[i])
            //         return false;
            return true;
        }
        int j = str[index] - 'a';
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
}  // namespace data_structure

/**
 * @brief Testing function
 * @returns void
 */
static void test() {
    data_structure::trie root;
    root.insert("hello");
    root.insert("world");

    assert(root.search("hello", 0));
    std::cout << "hello - " << root.search("hello", 0) << "\n";

    assert(!root.search("word", 0));
    std::cout << "word - " << root.search("word", 0) << "\n";

    assert(root.search("world", 0));
    std::cout << "world - " << root.search("world", 0) << "\n";
}

int main() {
    test();

    return 0;
}
