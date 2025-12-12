/**
 * @file
 * @brief Implementation of the [Aho-Corasick](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm) algorithm.
 * @details
 * The Aho-Corasick algorithm is a string searching algorithm invented by Alfred V. Aho and Margaret J. Corasick in 1975.
 * It is a kind of dictionary-matching algorithm that locates elements of a finite set of strings (the "dictionary")
 * within an input text. It matches all strings simultaneously.
 *
 * Running Time Complexity: O(N + L + Z), where N is the length of the text, L is the total length of the patterns,
 * and Z is the number of reporting matches.
 * Space Complexity: O(L * sigma), where sigma is the alphabet size.
 *
 * @author [Kurt Denver Chavez](https://github.com/denver2714)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <cassert>


/**
 * @namespace strings
 * @brief String algorithms
 */
namespace strings {
/**
 * @namespace aho_corasick
 * @brief Functions for Aho-Corasick algorithm
 */
namespace aho_corasick {

/**
 * @brief Trie Node structure for the Aho-Corasick automaton
 */
struct Node {
    std::map<char, int> children; ///< Map to store children nodes
    int failure_link = 0;         ///< Failure link to the longest proper suffix
    std::vector<int> output;      ///< Indices of patterns that end at this node
    int id;                       ///< Unique ID for the node

    explicit Node(int id) : id(id) {}
};

/**
 * @brief Aho-Corasick Automaton class
 */
class AhoCorasick {
private:
    std::vector<Node> trie;           ///< The trie structure
    std::vector<std::string> patterns;///< Store original patterns 

public:
    /**
     * @brief Constructor
     */
    AhoCorasick() {
        // Initialize root node
        trie.emplace_back(0);
    }

    /**
     * @brief Insert a pattern into the trie
     * @param pattern The string pattern to insert
     */
    void insert(const std::string& pattern) {
        int current_node = 0;
        for (char c : pattern) {
            if (trie[current_node].children.find(c) == trie[current_node].children.end()) {
                trie[current_node].children[c] = trie.size();
                trie.emplace_back(trie.size());
            }
            current_node = trie[current_node].children[c];
        }
        trie[current_node].output.push_back(patterns.size());
        patterns.push_back(pattern);
    }

    /**
     * @brief Build failure links for the automaton
     * @details Uses BFS to set failure links for all nodes
     */
    void build_failure_links() {
        std::queue<int> q;

        // Initialize queue with children of root
        for (auto const& [key, next_node] : trie[0].children) {
            q.push(next_node);
            trie[next_node].failure_link = 0; // Failure link of depth 1 is root
        }

        while (!q.empty()) {
            int current_node = q.front();
            q.pop();

            for (auto const& [key, next_node] : trie[current_node].children) {
                int failure = trie[current_node].failure_link;

                // Follow failure links until a matching transition is found
                while (failure != 0 && trie[failure].children.find(key) == trie[failure].children.end()) {
                    failure = trie[failure].failure_link;
                }

                if (trie[failure].children.find(key) != trie[failure].children.end()) {
                    failure = trie[failure].children[key];
                }

                trie[next_node].failure_link = failure;
                
                // Merge output from failure link
                trie[next_node].output.insert(
                    trie[next_node].output.end(),
                    trie[failure].output.begin(),
                    trie[failure].output.end()
                );

                q.push(next_node);
            }
        }
    }

    /**
     * @brief Search for all patterns in the given text
     * @param text The text to search in
     * @return A map where key is the pattern index and value is a vector of start positions in the text
     */
    std::map<std::string, std::vector<int>> search(const std::string& text) {
        std::map<std::string, std::vector<int>> results;
        int current_node = 0;

        for (int i = 0; i < text.length(); ++i) {
            char c = text[i];
            
            // Follow failure links if no transition exists
            while (current_node != 0 && trie[current_node].children.find(c) == trie[current_node].children.end()) {
                current_node = trie[current_node].failure_link;
            }

            if (trie[current_node].children.find(c) != trie[current_node].children.end()) {
                current_node = trie[current_node].children[c];
            }

            // Collect matches found at this state
            for (int pattern_index : trie[current_node].output) {
                // Determine start position of the match
                int start_pos = i - patterns[pattern_index].length() + 1;
                results[patterns[pattern_index]].push_back(start_pos);
            }
        }
        return results;
    }
};

} // namespace aho_corasick
} // namespace strings

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using namespace strings::aho_corasick;

    // Test Case 1: Standard example
    {
        AhoCorasick ac;
        ac.insert("he");
        ac.insert("she");
        ac.insert("his");
        ac.insert("hers");
        ac.build_failure_links();

        std::string text = "ushers";
        auto results = ac.search(text);

        assert(results["he"].size() == 1);
        assert(results["he"][0] == 2); // us(he)rs

        assert(results["she"].size() == 1);
        assert(results["she"][0] == 1); // u(she)rs

        assert(results["hers"].size() == 1);
        assert(results["hers"][0] == 2); // us(hers)
        
        assert(results.find("his") == results.end());
        
        std::cout << "Test 1 passed." << std::endl;
    }

    // Test Case 2: Overlapping patterns
    {
        AhoCorasick ac;
        ac.insert("a");
        ac.insert("ab");
        ac.insert("bab");
        ac.insert("bc");
        ac.insert("bca");
        ac.insert("c");
        ac.insert("caa");
        ac.build_failure_links();

        std::string text = "abccab";
        auto results = ac.search(text);

        // Expected matches:
        // 'a' at 0, 4
        // 'ab' at 0, 4
        // 'bc' at 1
        // 'c' at 2, 3
        // 'caa' at none
        
        assert(results["a"].size() == 2 && results["a"][0] == 0 && results["a"][1] == 4);
        assert(results["ab"].size() == 2 && results["ab"][0] == 0 && results["ab"][1] == 4);
        assert(results["bc"].size() == 1 && results["bc"][0] == 1);
        assert(results["c"].size() == 2 && results["c"][0] == 2 && results["c"][1] == 3);
        
        std::cout << "Test 2 passed." << std::endl;
    }

    // Test Case 3: No matches
    {
        AhoCorasick ac;
        ac.insert("foo");
        ac.insert("bar");
        ac.build_failure_links();

        std::string text = "coding";
        auto results = ac.search(text);

        assert(results.empty());
        std::cout << "Test 3 passed." << std::endl;
    }
    
    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test(); // run self-test implementations
    return 0;
}

