/**
 * @file
 * @brief Aho-Corasick Algorithm for multi-pattern string searching.
 * @details
 * This algorithm builds a finite state machine from the given patterns and 
 * allows efficient searching for all occurrences of those patterns in a text.
 * 
 * Reference: https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm
 * 
 * @author [Your Name](https://github.com/your_handle)
 * @see other_related_file.cpp, another_file.cpp
 */

#include <iostream>   /// for std::cout
#include <vector>    /// for std::vector
#include <string>    /// for std::string
#include <queue>     /// for std::queue
#include <unordered_map> /// for std::unordered_map
#include <cassert>   /// for assert

/**
 * @namespace
 * @brief Aho-Corasick algorithm namespace
 */
namespace AhoCorasick {

/**
 * @brief Trie node structure
 */
struct TrieNode {
    std::unordered_map<char, TrieNode*> children; ///< Child nodes
    TrieNode* fail;                                 ///< Failure link
    std::vector<int> output;                        ///< Output patterns

    TrieNode() : fail(nullptr) {}
};

/**
 * @brief Aho-Corasick class for multi-pattern matching
 */
class AhoCorasick {
 private:
    TrieNode* root; ///< Root of the trie

 public:
    AhoCorasick() {
        root = new TrieNode();
    }

    /**
     * @brief Insert a pattern into the trie
     * @param pattern The pattern to insert
     */
    void insert(const std::string& pattern) {
        TrieNode* current = root;
        for (char ch : pattern) {
            if (!current->children.count(ch)) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->output.push_back(pattern.length());
    }

    /**
     * @brief Build the Aho-Corasick automaton
     */
    void build() {
        std::queue<TrieNode*> q;
        root->fail = root; // Failure link for root points to itself

        for (const auto& pair : root->children) {
            pair.second->fail = root;
            q.push(pair.second);
        }

        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();

            for (const auto& pair : current->children) {
                char ch = pair.first;
                TrieNode* child = pair.second;
                TrieNode* failNode = current->fail;

                while (failNode != root && !failNode->children.count(ch)) {
                    failNode = failNode->fail;
                }

                if (failNode->children.count(ch)) {
                    child->fail = failNode->children[ch];
                } else {
                    child->fail = root;
                }

                child->output.insert(child->output.end(),
                                     child->fail->output.begin(),
                                     child->fail->output.end());
                q.push(child);
            }
        }
    }

    /**
     * @brief Search for patterns in the given text
     * @param text The text to search
     * @returns A vector of occurrences of patterns
     */
    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> results; // (index, pattern_length)
        TrieNode* current = root;

        for (int i = 0; i < text.length(); ++i) {
            char ch = text[i];

            while (current != root && !current->children.count(ch)) {
                current = current->fail;
            }

            if (current->children.count(ch)) {
                current = current->children[ch];
            }

            for (int len : current->output) {
                results.emplace_back(i - len + 1, len);
            }
        }

        return results;
    }

    ~AhoCorasick() {
        // Destructor to free allocated memory (not implemented here)
    }
};

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    AhoCorasick ac;
    ac.insert("he");
    ac.insert("she");
    ac.insert("his");
    ac.insert("hers");
    ac.build();

    std::string text = "ahishers";
    auto results = ac.search(text);

    // Check results
    assert(results.size() == 4); // Expected matches: "he", "she", "his", "hers"

    for (const auto& res : results) {
        std::cout << "Pattern found at index: " << res.first << " with length: " << res.second << "\n";
    }

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
