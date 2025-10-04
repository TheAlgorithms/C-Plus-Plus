/**
 * @file
 * @brief Aho-Corasick Algorithm[](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick) - Multi-pattern string search.
 * @details Builds a trie + failure links for O(n + m + z) multi-pattern matching. Inspired by GFG/LeetCode #30.
 * @author [Your Name](https://github.com/yourhandle)
 */
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace strings { namespace aho_corasick {
    // Trie node struct
    struct TrieNode {
        std::unordered_map<char, int> children;
        int fail = 0;
        std::vector<int> output;  // Pattern indices ending here
    };

    // Build trie + failure links
    std::vector<TrieNode> buildTrie(const std::vector<std::string>& patterns) {
        // ... (implement: insert patterns, BFS for fails)
    }

    // Search function
    std::vector<std::pair<size_t, size_t>> search(const std::string& text, const std::vector<std::string>& patterns) {
        // ... (implement: traverse text, collect matches via output links)
        return {};  // vector of (text_pos, pattern_index)
    }
} }  // namespace

static void test() {
    std::vector<std::string> pats = {"he", "she", "his", "hers"};
    std::string text = "ushers";
    auto matches = strings::aho_corasick::search(text, pats);
    assert(matches.size() == 3);  // Expected: (0,"ushe"), etc. — adjust asserts
    // More tests: empty, no-match, overlaps.
    std::cout << "All tests passed!\n";
}

int main() { test(); return 0; }
