/**
 * Copyright 2020 @author Anmol3299
 * @file
 *
 * A basic implementation of trie class to store only lower-case strings.
 */
#include <iostream>  // for io operations
#include <memory>    // for std::shared_ptr<>
#include <string>    // for std::string class

/**
 * A basic implementation of trie class to store only lower-case strings.
 * You can extend the implementation to all the ASCII characters by changing the
 * value of @ ALPHABETS to 128.
 */
class Trie {
 private:
    static constexpr size_t ALPHABETS = 26;

    /**
     * Structure of trie node.
     * This struct doesn't need a constructor as we are initializing using
     * intializer list which is more efficient than if we had done so with
     * constructor.
     */
    struct TrieNode {
        // An array of pointers of size 26 which tells if a character of word is
        // present or not.
        std::shared_ptr<TrieNode> character[ALPHABETS]{nullptr};

        bool isEndOfWord{false};
    };

    /**
     * Function to check if a node has some children which can form words.
     * @param node whose character array of pointers need to be checked for
     * children.
     * @return if a child is found, it returns @ true, else it returns @ false.
     */
    inline static bool hasChildren(std::shared_ptr<TrieNode> node) {
        for (size_t i = 0; i < ALPHABETS; i++) {
            if (node->character[i]) {
                return true;
            }
        }
        return false;
    }

    /**
     * A recursive helper function to remove a word from the trie. First, it
     * recursively traverses to the location of last character of word in the
     * trie. However, if the word is not found, the function returns a runtime
     * error. Upon successfully reaching the last character of word in trie, if
     * sets the isEndOfWord to false and deletes the node if and only if it has
     * no children, else it returns the current node.
     * @param word is the string which needs to be removed from trie.
     * @param curr is the current node we are at.
     * @param index is the index of the @word we are at.
     * @return if current node has childern, it returns @ curr, else it returns
     * nullptr.
     * @throw a runtime error in case @ word is not found in the trie.
     */
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

        // This if condition checks if the node has some childern.
        // The 1st if check, i.e. (curr->character[idx]) is checked specifically
        // because if the older string is a prefix of some other string, then,
        // there would be no need to check all 26 characters. Example- str1 =
        // abbey, str2 = abbex and we want to delete string "abbey", then in
        // this case, there would be no need to check all characters for the
        // chars a,b,b.
        if (curr->character[idx] || hasChildren(curr)) {
            return curr;
        }
        return nullptr;
    }

 public:
    // constructor to initialise the root of the trie.
    Trie() : m_root(std::make_shared<TrieNode>()) {}

    /**
     * Insert a word into the trie.
     * @param word which needs to be inserted into the string.
     */
    void insert(const std::string& word) {
        auto curr = m_root;
        for (char ch : word) {
            size_t index = ch - 'a';

            // if a node for current word is not already present in trie, create
            // a new node for it.
            if (!curr->character[index]) {
                curr->character[index] = std::make_shared<TrieNode>();
            }

            curr = curr->character[index];
        }
        curr->isEndOfWord = true;
    }

    /**
     * Search if a word is present in trie or not.
     * @param word which is needed to be searched in the trie.
     * @return True if the word is found in trie and isEndOfWord is set to true.
     * @return False if word is not found in trie or isEndOfWord is set to
     * false.
     */
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

    // Function to remove the word which calls the helper function.
    void removeWord(const std::string& word) {
        m_root = removeWordHelper(word, m_root, 0);
    }

 private:
    // data member to store the root of the trie.
    std::shared_ptr<TrieNode> m_root;
};

/**
 * Main function
 */
int main() {
    Trie trie;
    trie.insert("hel");
    trie.insert("hello");
    trie.removeWord("hel");
    std::cout << trie.search("hello") << '\n';

    return 0;
}
