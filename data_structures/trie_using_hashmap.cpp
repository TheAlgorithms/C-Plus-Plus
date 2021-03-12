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
#include <iostream>       /// for iostream
#include <memory>         /// for shared pointer
#include <stack>          /// for stack
#include <unordered_map>  /// for unordered map
#include <vector>         /// for vector

/**
 * @namespace data_structures
 */

namespace data_structures {
/**
 * Class documentation
 */
class Trie {
 private:
    struct Node {
        /** @brief trie nodes as key value pairs, value is a shared_pointer of
         * Node */
        std::unordered_map<char16_t, std::shared_ptr<Node>> children;
        bool word_end = false;  /// boolean variable to represent the node end
    };

    std::shared_ptr<Node> root_node;  ///< declaring root node of trie

 public:
    ///< Constructor
    Trie() {
        root_node = std::make_shared<Node>();  ///< intializing root node
    }
    ///< Destructor
    virtual ~Trie() { root_node; }

    /** insert string into the trie
     * @param word string to insert in the tree
     */
    void insert(std::string word) {
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

    /** search a word/string exists inside the trie
     * @param word string to search for
     * @returns `true` if found
     * @returns `false` if not found
     */

    bool search(std::string word) {
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

    /** search a word/string that starts with a given prefix
     * @param prefix string to search for
     * @returns `true` if found
     * @returns `false` if not found
     */

    bool startwith(std::string prefix) {
        std::shared_ptr<Node> curr = root_node;
        for (char ch : prefix) {
            if (curr->children.find(ch) == curr->children.end()) {
                return false;
            }
            curr = curr->children[ch];
        }
        return true;
    }

    /** Delete a word/string from a trie
     * @param word string to delete fromm trie
     */
    void delete_word(std::string word) {
        std::shared_ptr<Node> curr = root_node;
        std::stack<std::shared_ptr<Node>> nodes;
        int cnt = 0;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                std::cout << "the word doesn't exit" << std::endl;

                return;
            }
            if (curr->word_end) {
                cnt++;
            }

            nodes.push(curr->children[ch]);
            curr = curr->children[ch];
        }
        /*delete only when its a word and it has no children after and also no
         * prefix in the line*/
        if (nodes.top()->word_end) {
            nodes.top()->word_end = false;
        }
        while (!(nodes.top()->word_end) && nodes.top()->children.empty()) {
            /* code */
            nodes.pop();
            nodes.top()->children.erase(word.back());
            word.pop_back();
        }
    }

    /** helper function to predict/recommend words that starts with a given
     * prefix from the end of prefix's node iterate through all the child nodes
     * by recursively appending  all the possible words below the trie
     * @param prefix string to recommend the words
     * @param element node at the end of given prefix
     * @param results list to store the all possible words
     * @returns list of recommended words
     */
    std::vector<std::string> get_all_words(std::vector<std::string> results,
                                           std::shared_ptr<Node> element,
                                           std::string prefix) {
        if (element->word_end) {
            results.push_back(prefix);
        }
        if (element->children.empty()) {
            return results;
        }
        for (auto const &x : element->children) {
            std::string key = "";
            key = x.first;
            prefix += key;

            results =
                get_all_words(results, element->children[x.first], prefix);

            prefix.pop_back();
        }

        return results;
    }

    /** predict/recommend a words that starts with a given prefix
     * @param prefix string to search for
     * @returns list of recommended words
     */

    std::vector<std::string> predict_words(std::string prefix) {
        std::vector<std::string> result;
        std::shared_ptr<Node> curr = root_node;
        /* treversing till the end of given prefix in trie*/

        for (char ch : prefix) {
            if (curr->children.find(ch) == curr->children.end()) {
                std::cout << "word with prefix dosen't exit" << std::endl;
                return result;
            }

            curr = curr->children[ch];
        }

        /* if given prefix is the only word without children */
        if (curr->word_end && curr->children.empty()) {
            result.push_back(prefix);
            return result;
        }

        std::string pd_word = "";
        result = get_all_words(
            result, curr,
            prefix);  ///< iteratively and recursively get the recommended words

        return result;
    }
};

}  // namespace data_structures

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    data_structures::Trie *obj = new data_structures::Trie();
    /* Inserting data into trie using insert method and testing it with search
     * method */
    obj->insert("app");
    obj->insert("abscond");
    obj->insert("about");
    obj->insert("apps");
    obj->insert("apen");
    obj->insert("apples");
    obj->insert("apple");
    obj->insert("approach");
    obj->insert("bus");
    obj->insert("buses");
    obj->insert("Apple");
    obj->insert("Bounce");

    assert(!obj->search("appy"));
    std::cout << "appy is not a word in trie" << std::endl;

    assert(!obj->search("car"));
    std::cout << "car is not a word in trie" << std::endl;
    assert(obj->search("app"));
    assert(obj->search("apple"));
    assert(obj->search("apples"));
    assert(obj->search("apps"));
    assert(obj->search("apen"));
    assert(obj->search("approach"));
    assert(obj->search("about"));
    assert(obj->search("abscond"));
    assert(obj->search("bus"));
    assert(obj->search("buses"));
    assert(obj->search("Bounce"));
    assert(obj->search("Apple"));

    std::cout << "All the Inserted words are present in the trie" << std::endl;

    /*test for startwith prefix method*/
    assert(!obj->startwith("approachs"));
    assert(obj->startwith("approach"));
    assert(obj->startwith("about"));
    assert(!obj->startwith("appy"));
    assert(obj->startwith("abscond"));
    assert(obj->startwith("bus"));
    assert(obj->startwith("buses"));
    assert(obj->startwith("Bounce"));
    assert(obj->startwith("Apple"));
    assert(obj->startwith("abs"));
    assert(obj->startwith("b"));
    assert(obj->startwith("bus"));
    assert(obj->startwith("Bo"));
    assert(obj->startwith("A"));
    assert(!obj->startwith("Ca"));

    assert(!obj->startwith("C"));

    std::cout << "All the tests passed for startwith method" << std::endl;

    /*test for predict_words/recommendation of words based on a given prefix*/

    std::vector<std::string> pred_words = obj->predict_words("a");

    for (std::string str : pred_words) {
        std::cout << str << std::endl;
    }
    assert(pred_words.size() == 8);
    std::cout << "Returned all words that start with prefix a " << std::endl;
    pred_words = obj->predict_words("app");

    for (std::string str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 5);
    std::cout << "Returned all words that start with prefix app " << std::endl;
    pred_words = obj->predict_words("A");

    for (std::string str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 1);
    std::cout << "Returned all words that start with prefix A " << std::endl;
    pred_words = obj->predict_words("bu");

    for (std::string str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 2);
    std::cout << "Returned all words that start with prefix bu " << std::endl;

    /*tests for delete method */

    obj->delete_word("app");
    assert(!obj->search("app"));
    std::cout << "word app is deleted sucessful" << std::endl;

    pred_words = obj->predict_words("app");
    for (std::string str : pred_words) {
        std::cout << str << std::endl;
    }
    assert(pred_words.size() == 4);
    std::cout << "app is deleted sucessful" << std::endl;

    /*test case for chinese language*/

    obj->insert("苹果");
    assert(obj->startwith("苹"));
    pred_words = obj->predict_words("h");
    for (std::string str : pred_words) {
        std::cout << str << std::endl;
    }

    std::cout << "All tests passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
    test();

    return 0;
}
