/**
 * @file
 * @author [Venkata Bharath](https://github.com/bharath000)
 * @brief Implementation of [Trie](https://en.wikipedia.org/wiki/Trie) data
 * structure using HashMap for different characters and method for predicting
 * words based on prefix.
 * @details The Trie data structure is implemented using unordered map to use
 * memory optimally, predict_words method is developed to recommend words based
 * on a given prefix along with other methods insert, delete, search, startwith
 * in trie.
 * @see trie_modern.cpp for difference
 */
#include <cassert>        /// for assert
#include <iostream>       /// for IO operations
#include <memory>         /// for std::shared_ptr
#include <stack>          /// for std::stack
#include <unordered_map>  /// for std::unordered_map
#include <vector>         /// for std::vector

/**
 * @namespace data_structures
 * @brief Data structures algorithms
 */
namespace data_structures {

/**
 * @namespace trie_using_hashmap
 * @brief Functions for [Trie](https://en.wikipedia.org/wiki/Trie) data
 * structure using hashmap implementation
 */
namespace trie_using_hashmap {

/**
 * @brief Trie class, implementation of trie using hashmap in each trie node
 * for all the characters of char16_t(UTF-16)type with methods to insert,
 * delete, search, start with and to recommend words based on a given
 * prefix.
 */
class Trie {
 private:
    /**
     * @brief struct representing a trie node.
     */
    struct Node {
        std::unordered_map<char16_t, std::shared_ptr<Node>>
            children;  ///< unordered map with key type char16_t and value is a
                       ///< shared pointer type of Node
        bool word_end = false;  ///< boolean variable to represent the node end
    };

    std::shared_ptr<Node> root_node =
        std::make_shared<Node>();  ///< declaring root node of trie

 public:
    ///< Constructor
    Trie() = default;

    /**
     * @brief insert the string into the trie
     * @param word string to insert in the trie
     */
    void insert(const std::string& word) {
        std::shared_ptr<Node> curr = root_node;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                curr->children[ch] = std::make_shared<Node>();
            }
            curr = curr->children[ch];
        }

        if (!curr->word_end && curr != root_node) {
            curr->word_end = true;
        }
    }

    /**
     * @brief search a word/string inside the trie
     * @param word string to search for
     * @returns `true` if found
     * @returns `false` if not found
     */
    bool search(const std::string& word) {
        std::shared_ptr<Node> curr = root_node;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                return false;
            }
            curr = curr->children[ch];
            if (!curr) {
                return false;
            }
        }

        if (curr->word_end) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief search a word/string that starts with a given prefix
     * @param prefix string to search for
     * @returns `true` if found
     * @returns `false` if not found
     */
    bool startwith(const std::string& prefix) {
        std::shared_ptr<Node> curr = root_node;
        for (char ch : prefix) {
            if (curr->children.find(ch) == curr->children.end()) {
                return false;
            }
            curr = curr->children[ch];
        }
        return true;
    }

    /**
     * @brief delete a word/string from a trie
     * @param word string to delete from trie
     */
    void delete_word(std::string word) {
        std::shared_ptr<Node> curr = root_node;
        std::stack<std::shared_ptr<Node>> nodes;
        int cnt = 0;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                return;
            }
            if (curr->word_end) {
                cnt++;
            }

            nodes.push(curr->children[ch]);
            curr = curr->children[ch];
        }
        // Delete only when it's a word, and it has children after
        // or prefix in the line
        if (nodes.top()->word_end) {
            nodes.top()->word_end = false;
        }
        // Delete only when it has no children after
        // and also no prefix in the line
        while (!(nodes.top()->word_end) && nodes.top()->children.empty()) {
            nodes.pop();
            nodes.top()->children.erase(word.back());
            word.pop_back();
        }
    }

    /**
     * @brief helper function to predict/recommend words that starts with a
     * given prefix from the end of prefix's node iterate through all the child
     * nodes by recursively appending all the possible words below the trie
     * @param prefix string to recommend the words
     * @param element node at the end of the given prefix
     * @param results list to store the all possible words
     * @returns list of recommended words
     */
    std::vector<std::string> get_all_words(std::vector<std::string> results,
                                           const std::shared_ptr<Node>& element,
                                           std::string prefix) {
        if (element->word_end) {
            results.push_back(prefix);
        }
        if (element->children.empty()) {
            return results;
        }
        for (auto const& x : element->children) {
            std::string key = "";
            key = x.first;
            prefix += key;

            results =
                get_all_words(results, element->children[x.first], prefix);

            prefix.pop_back();
        }

        return results;
    }

    /**
     * @brief predict/recommend a word that starts with a given prefix
     * @param prefix string to search for
     * @returns list of recommended words
     */
    std::vector<std::string> predict_words(const std::string& prefix) {
        std::vector<std::string> result;
        std::shared_ptr<Node> curr = root_node;
        // traversing until the end of the given prefix in trie

        for (char ch : prefix) {
            if (curr->children.find(ch) == curr->children.end()) {
                return result;
            }

            curr = curr->children[ch];
        }

        // if the given prefix is the only word without children
        if (curr->word_end && curr->children.empty()) {
            result.push_back(prefix);
            return result;
        }

        result = get_all_words(
            result, curr,
            prefix);  ///< iteratively and recursively get the recommended words

        return result;
    }
};
}  // namespace trie_using_hashmap
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::trie_using_hashmap::Trie obj;
    // Inserting data into trie using the insert
    // method and testing it with search method
    obj.insert("app");
    obj.insert("abscond");
    obj.insert("about");
    obj.insert("apps");
    obj.insert("apen");
    obj.insert("apples");
    obj.insert("apple");
    obj.insert("approach");
    obj.insert("bus");
    obj.insert("buses");
    obj.insert("Apple");
    obj.insert("Bounce");

    assert(!obj.search("appy"));
    std::cout << "appy is not a word in trie" << std::endl;

    assert(!obj.search("car"));
    std::cout << "car is not a word in trie" << std::endl;
    assert(obj.search("app"));
    assert(obj.search("apple"));
    assert(obj.search("apples"));
    assert(obj.search("apps"));
    assert(obj.search("apen"));
    assert(obj.search("approach"));
    assert(obj.search("about"));
    assert(obj.search("abscond"));
    assert(obj.search("bus"));
    assert(obj.search("buses"));
    assert(obj.search("Bounce"));
    assert(obj.search("Apple"));

    std::cout << "All the Inserted words are present in the trie" << std::endl;

    // test for startwith prefix method
    assert(!obj.startwith("approachs"));
    assert(obj.startwith("approach"));
    assert(obj.startwith("about"));
    assert(!obj.startwith("appy"));
    assert(obj.startwith("abscond"));
    assert(obj.startwith("bus"));
    assert(obj.startwith("buses"));
    assert(obj.startwith("Bounce"));
    assert(obj.startwith("Apple"));
    assert(obj.startwith("abs"));
    assert(obj.startwith("b"));
    assert(obj.startwith("bus"));
    assert(obj.startwith("Bo"));
    assert(obj.startwith("A"));
    assert(!obj.startwith("Ca"));

    assert(!obj.startwith("C"));

    std::cout << "All the tests passed for startwith method" << std::endl;

    // test for predict_words/recommendation of words based on a given prefix

    std::vector<std::string> pred_words = obj.predict_words("a");

    for (const std::string& str : obj.predict_words("a")) {
        std::cout << str << std::endl;
    }
    assert(pred_words.size() == 8);
    std::cout << "Returned all words that start with prefix a " << std::endl;
    pred_words = obj.predict_words("app");

    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 5);
    std::cout << "Returned all words that start with prefix app " << std::endl;
    pred_words = obj.predict_words("A");

    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 1);
    std::cout << "Returned all words that start with prefix A " << std::endl;
    pred_words = obj.predict_words("bu");

    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 2);
    std::cout << "Returned all words that start with prefix bu " << std::endl;

    // tests for delete method

    obj.delete_word("app");
    assert(!obj.search("app"));
    std::cout << "word app is deleted sucessful" << std::endl;

    pred_words = obj.predict_words("app");
    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }
    assert(pred_words.size() == 4);
    std::cout << "app is deleted sucessful" << std::endl;

    // test case for Chinese language

    obj.insert("苹果");
    assert(obj.startwith("苹"));
    pred_words = obj.predict_words("h");

    assert(pred_words.size() == 0);
    std::cout << "No word starts with prefix h in trie" << std::endl;

    std::cout << "All tests passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementaions
    return 0;
}
