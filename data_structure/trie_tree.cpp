#include <iostream>
#include <memory>
#include <string>

class Trie {
private:
    static constexpr size_t ALPHABETS = 26;

    // Structure of trie node
    struct TrieNode {
        std::shared_ptr<TrieNode> character[ALPHABETS]{nullptr};
        bool isEndOfWord{false};
    };

    // Function to check if a node has some children which can form words.
    inline static bool hasChildren(std::shared_ptr<TrieNode> node) {
        for (size_t i = 0; i < ALPHABETS; i++) {
            if (node->character[i]) {
                return true;
            }
        }
        return false;
    }

    // Helper function to remove a word. The nodes are deleted only when the
    // string is not a prefix of any other string, else isEndOfWord is set to
    // false.
    std::shared_ptr<TrieNode> removeWordHelper(const std::string& word,
                                               std::shared_ptr<TrieNode> curr,
                                               size_t index) {
        if (word.size() == index) {
            if (curr->isEndOfWord) {
                curr->isEndOfWord = false;
            }
            if (hasChildren(curr)) {
                return curr;
            }
            return nullptr;
        }

        size_t idx = word[index] - 'a';
        // Throw a runtime error in case the user enters a word which is not
        // present in the trie.
        if (!curr->character[idx]) {
            throw std::runtime_error(std::move(std::string("Word not found.")));
        }

        curr->character[idx] =
            removeWordHelper(word, curr->character[idx], index + 1);
        if (curr->character[idx] || hasChildren(curr)) {
            return curr;
        }
        return nullptr;
    }

public:
    // constructor to initialise the root of the trie.
    Trie() : m_root(std::make_shared<TrieNode>()){};

    // Insert string into the trie.
    void insert(const std::string& word) {
        auto curr = m_root;
        for (char ch : word) {
            size_t index = ch - 'a';
            // if a node for current word is not already preset in trie, create
            // a new node for it.
            if (!curr->character[index]) {
                curr->character[index] = std::make_shared<TrieNode>();
            }

            curr = curr->character[index];
        }
        curr->isEndOfWord = true;
    }

    // Search if a word is present in trie or not.
    bool search(const std::string& word) {
        auto curr = m_root;
        for (char ch : word) {
            size_t index = ch - 'a';
            // if any node for a character is not found, then return that the
            // word cannot be formed.
            if (!curr->character[index]) {
                return false;
            }
            curr = curr->character[index];
        }
        return curr->isEndOfWord;
    }

    // Main function to remove the word which calls the helper function.
    void removeWord(const std::string& word) {
        m_root = removeWordHelper(word, m_root, 0);
    }

private:
    std::shared_ptr<TrieNode> m_root;
};

int main() {
    Trie trie;
    trie.insert("hel");
    trie.insert("hello");
    trie.removeWord("hel");
    std::cout << trie.search("hello") << '\n';

    return 0;
}
