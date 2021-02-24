/**
 * @file
 * @brief [Trie datastructure](https://iq.opengenus.org/autocomplete-using-trie-data-structure/)
 * with search variants
 * @details
 * This provides multiple variants of search functions
 * on a trie structure utilizing STL. The trie is valid
 * for only English alphabets.
 * @author [Ghanashyam](https://github.com/g-s-k-zoro)
 */

#include <algorithm>  /// for std::count
#include <cassert>    /// for assert
#include <cctype>     /// for tolower
#include <cstring>    /// for string operations
#include <iostream>   /// for IO Operations
#include <queue>      /// for std::priority_queue

/**
 * @namespace operations_on_datastructures
 * @brief Operations on data structures
 */
namespace operations_on_datastructures {
/**
 * @namespace trie_operations
 * @brief Functions for [Trie datastructure](https://iq.opengenus.org/autocomplete-using-trie-data-structure/)
 * implementation
 */
namespace trie_operations {
/**
 * @brief Class defining the structure of trie node and containing the methods
 * to perform operations on them.
 */
class Tnode {
 private:
    static constexpr uint8_t ENGLISH_ALPHABET_SIZE = 26;
    // pointers to alphabets
    std::vector<Tnode *> english;

    // To mark the end of word
    bool endOfWord;

    // To store the frequency of searches for the word
    uint32_t frequency;

 public:
    Tnode() {
        english.resize(ENGLISH_ALPHABET_SIZE, nullptr);
        endOfWord = false;
        frequency = 0;
    }
    // Copy Constructor
    Tnode(const Tnode &node) {
        english = node.english;
        endOfWord = node.endOfWord;
        frequency = node.frequency;
    }

    Tnode &operator=(const Tnode &node) = default;

    Tnode(Tnode &&) = default;

    Tnode &operator=(Tnode &&) = default;
    /**
     * @brief Function to count the number of children a node in the trie has
     * @param node a trie node whose children need to be counted
     * @return count of the number of children of the given node (max 26)
     */
    inline uint8_t numberOfChildren(Tnode *node) {
        return ENGLISH_ALPHABET_SIZE -
               std::count(node->english.begin(), node->english.end(), nullptr);
    }

    // Functions to perform operations on trie
    void Insert(const std::string &entry);
    void Delete(std::string entry);
    void DeleteFrom(Tnode *delete_from, std::string delete_string,
                    int remove_index);
    bool SearchPresence(const std::string &key);
    void SuggestAutocomplete(Tnode *new_root, const std::string &prefix);
    void SearchSuggestions(const std::string &key);
    void SuggestFreqAutocomplete(
        Tnode *new_root, const std::string &prefix,
        std::priority_queue<std::pair<int, std::string> > *suggestions);
    void SearchFreqSuggestions(const std::string &key);
    void SelectionTop_3(
        std::priority_queue<std::pair<int, std::string> > *suggestions);

    // To free up the dynamically allocated objects
    ~Tnode() {
        int i = 0;
        for (i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
            if (english[i]) {
                delete english[i];
            }
        }
    }
};

/**
 * @brief Function to insert a word in the trie
 * @param entry string entry to be inserted in the trie
 */
void Tnode::Insert(const std::string &entry) {
    Tnode *cur_pos = this;
    int letter_index = 0;

    for (auto &i : entry) {
        // To ignore case
        letter_index = tolower(i) - 97;

        // Allocate a node for each character of entry if not present in the
        // trie
        if (cur_pos->english[letter_index] == nullptr) {
            cur_pos->english[letter_index] = new Tnode();
        }

        cur_pos = cur_pos->english[letter_index];
    }
    // cur_pos points to the last char, mark it as end of word
    cur_pos->endOfWord = true;
}

/**
 * @brief Function recursively deletes the substring character by
 * character iterating through the string to be deleted. It traverses till the
 * end of word in a recursive fashion, from there it deletes characters one by
 * one till it reaches back to the initial call.
 * @param delete_from the acting root to the required suffix to be deleted
 * @param delete_string the string to be deleted from the trie
 * @param remove_index index denoting the beginning of the substring to be
 * deleted
 */
void Tnode::DeleteFrom(Tnode *delete_from, std::string delete_string,
                       int remove_index) {
    if (delete_string.size() == remove_index) {
        int letter_index = tolower(delete_string[remove_index]) - 97;

        DeleteFrom(delete_from->english[letter_index], delete_string,
                   remove_index + 1);

        delete delete_from;
    }
}

/**
 * @brief Function to verify presence and hence delete an entry from the trie
 * @param entry string entry to be deleted from the trie
 */
void Tnode::Delete(std::string entry) {
    Tnode *cur_pos = this,
          *delete_from = this;  // Current pointer pointing to root
    int letter_index = 0, delete_from_index = 0, i = 0, n = entry.size();

    for (i = 0; i < n; i++) {
        // To ignore case
        letter_index = tolower(entry[i]) - 97;

        // Display error message when given entry is not present in the tree
        if (cur_pos->english[letter_index] == nullptr) {
            std::cout << "Entry not Found" << std::endl;
            return;
        }
        // If the current node is end of word for the current prefix or if it
        // has 2 or more branches It cannot be deleted while deleting the
        // required entry.
        if (numberOfChildren(cur_pos) > 1 || cur_pos->endOfWord) {
            delete_from = cur_pos;      // denotes the beginning of the shortest
                                        // suffix that is allowed to be deleted
            delete_from_index = i - 1;  // Beginning index of the suffix
                                        // corresponding to the 'entry'
        }

        // Traversing through the entry
        cur_pos = cur_pos->english[letter_index];
    }

    // cur_pos now points to the last char of entry. Display message if that
    // entry does not exist
    if (!cur_pos->endOfWord) {
        std::cout << "Entry not Found" << std::endl;
        return;
    }

    // If cur_pos is not a leaf node, unmark end of word and assign 0 to it's
    // frequency for deletion
    if (numberOfChildren(cur_pos)) {
        cur_pos->endOfWord = false;
        cur_pos->frequency = 0;
        return;
    }

    // The first character of the suffix to be deleted
    letter_index = tolower(entry[delete_from_index + 1]) - 97;
    // Point cur_pos to the next node
    cur_pos = delete_from->english[letter_index];
    // Sever the connection from the main trie
    delete_from->english[letter_index] = nullptr;

    // If number of characters in the suffix are more than 1, recursively delete
    // each character starting from cur_pos using the helper function
    if (n > delete_from_index + 2) {
        DeleteFrom(cur_pos, entry, delete_from_index + 2);
    }
    // If the suffix is only 1 char in length
    else {
        delete cur_pos;
    }
}

/**
 * @brief Function to check a word's presence in the trie (Basic)
 * @param key the string key to be searched in the trie
 * @return true if the key is found
 * @return false if the key is not found
 */
bool Tnode::SearchPresence(const std::string &key) {
    Tnode *cur_pos = this;
    int letter_index = 0;

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        // If any character in the order of the key is absent, word not found!
        if (cur_pos->english[letter_index] == nullptr) {
            return false;
        }
        cur_pos = cur_pos->english[letter_index];
    }
    // Word is only present in the trie if the key is a valid complete entry and
    // not just a prefix.
    if (cur_pos->endOfWord) {
        (cur_pos->frequency)++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Recursive function to suggest all the entries of trie
 * which have a given common prefix
 * @param new_root pointer pointing to the node corresponding to the last char
 * of prefix
 * @param prefix the common prefix that all the suggestions must have
 */
void Tnode::SuggestAutocomplete(Tnode *new_root, const std::string &prefix) {
    // Iterate through all 26 nodes as we have to print all strings with the
    // given prefix
    int i = 0;
    for (i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
        if (new_root->english[i] != nullptr) {
            // Print the sugestion only if it's a valid complete entry and not
            // just a prefix
            if (new_root->english[i]->endOfWord) {
                std::cout << prefix + char(i + 97) << std::endl;
            }

            SuggestAutocomplete(new_root->english[i], prefix + char(i + 97));
        }
    }
}

/**
 * @brief Lists out all the words in trie with the longest prefix
 * of the search key that is present in the trie. For example - if trie contains
 * "abc", "abcde", "abcdefg", "abcddef" and if the search key is "abcdezz", then
 * the longest common prefix is "abcde" and hence search results will be
 * "abcde", "abcdefg".
 * @param key the string key to be searched for suggestions
 */
void Tnode::SearchSuggestions(const std::string &key) {
    Tnode *cur_pos = nullptr, *prev_pos = nullptr;
    cur_pos = prev_pos = this;  // maintaining 2 pointers, initialized to root
    int letter_index = 0;
    std::string prefix =
        "";  // variable storing the updated value of longest common prefix

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        prev_pos = cur_pos;  // Previous pointer updated to point to the last
                             // char of the longest common prefix

        // When the node for the character does not exist, longest prefix has
        // been determined and SuggestAutocomplete is called
        if (cur_pos->english[letter_index] == nullptr) {
            SuggestAutocomplete(prev_pos, prefix);
            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
                      << std::endl;
            return;
        }
        // Updating the longest common prefix
        prefix += char(tolower(i));
        cur_pos = cur_pos->english[letter_index];
    }
    // If the key is a valid entry of trie, display it @ top of the suggestions
    if (cur_pos->endOfWord) {
        std::cout << key << std::endl;
        (cur_pos->frequency)++;
    }

    (void)prev_pos;  // Idiom to ignore previous pointer

    // Call for suggestions when the search key is present as an entry/a prefix
    // in the trie
    SuggestAutocomplete(cur_pos, prefix);
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
              << std::endl;
    return;
}

/**
 * @brief Function to display the 3 suggestions with highest frequency
 * of search hits
 * @param suggestions a max heap that contains pairs of (frequency, word)
 * heapified based on frequency
 */
void Tnode::SelectionTop_3(
    std::priority_queue<std::pair<int, std::string> > *suggestions) {
    // Display Either top 3 or total number of suggestions, whichever is smaller
    int n = suggestions->size(), Top = 0;
    Top = n < 3 ? n : 3;
    while (Top--) {
        std::cout << suggestions->top().second << std::endl;
        suggestions->pop();
    }
}

/**
 * @brief Recursive function to suggest most frequently
 * searched entries of trie which have a given common prefix
 * @param new_root pointer pointing to the node corresponding to the last char
 * of prefix
 * @param prefix the common prefix that all the suggestions must have
 * @param suggestions a max heap that contains pairs of (frequency, word)
 * heapified based on frequency
 */
void Tnode::SuggestFreqAutocomplete(
    Tnode *new_root, const std::string &prefix,
    std::priority_queue<std::pair<int, std::string> > *suggestions) {
    int i = 0;
    for (i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
        if (new_root->english[i] != nullptr) {
            // Add to sugestions only if it's a valid complete entry and not
            // just a prefix
            if (new_root->english[i]->endOfWord) {
                suggestions->push(std::make_pair(
                    new_root->english[i]->frequency, prefix + char(i + 97)));
            }

            SuggestFreqAutocomplete(new_root->english[i], prefix + char(i + 97),
                                    suggestions);
        }
    }
}

/**
 * @brief Lists out the most frequent words in trie with the
 * longest prefix of the search key that is present in the trie. For example -
 * if trie contains "abc", "abcde", "abcdefg", "abcddef" and they have been
 * previously searched for 3, 1, 2, 4 times respectively, if the search key is
 * "ab", then the longest common prefix is "ab" and only the top 3 frequencies
 * among the matches would be displayed viz. "abcddef", "abc", "abcdefg".
 * @param key the string key to be searched for suggestions
 */
void Tnode::SearchFreqSuggestions(const std::string &key) {
    Tnode *cur_pos = nullptr, *prev_pos = nullptr;
    cur_pos = prev_pos = this;  // maintaining 2 pointers, initialized to root
    int letter_index = 0;
    std::string prefix =
        "";  // variable storing the updated value of longest common prefix
    std::priority_queue<std::pair<int, std::string> >
        suggestions;  // max heap to store (frequency, word) in descending order
                      // of freq

    std::priority_queue<std::pair<int, std::string> > *Suggestions =
        &suggestions;

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        prev_pos = cur_pos;  // Previous pointer updated to point to the last
                             // char of the longest common prefix

        // When the node for the character does not exist, longest prefix has
        // been determined and SuggestFreqAutocomplete is called
        if (cur_pos->english[letter_index] == nullptr) {
            SuggestFreqAutocomplete(prev_pos, prefix, Suggestions);
            // To display the top 3 results
            SelectionTop_3(Suggestions);
            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
                      << std::endl;
            return;
        }
        // Updating the longest common prefix
        prefix += char(tolower(i));
        cur_pos = cur_pos->english[letter_index];
    }
    // If the key is a valid entry of trie, display it @ top of the suggestions
    if (cur_pos->endOfWord) {
        (cur_pos->frequency)++;
        std::cout << key << std::endl;
    }

    (void)prev_pos;  // Idiom to ignore previous pointer

    // Call for Suggestions when the search key is present as an entry/a prefix
    // in the trie
    SuggestFreqAutocomplete(cur_pos, prefix, Suggestions);
    // Display the top 3 results
    SelectionTop_3(Suggestions);

    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
              << std::endl;
    return;
}
}  // namespace trie_operations
}  // namespace operations_on_datastructures

/**
 * @brief Function to test a simple search before and after deleting
 * an entry. And to test out the multiple variants of search.
 */
static void test() {
    auto root = new operations_on_datastructures::trie_operations::Tnode();
    std::vector<std::string> inputs = {
        "abcde", "sss",    "ssss",  "ssst", "sssu", "sssv",
        "sst",   "ssts",   "sstt",  "sstu", "tutu", "tutuv",
        "tutuu", "tutuvs", "tutus", "tvst", "tvsu", "vvvv"};

    for (auto &i : inputs) {
        root->Insert(i);
    }
    // Search an existing entry
    assert(root->SearchPresence("vvvv"));
    std::cout << root->SearchPresence("vvvv") << std::endl;
    // Delete it
    root->Delete("vvvv");
    // Search for the entry again
    assert(!root->SearchPresence("vvvv"));
    std::cout << root->SearchPresence("vvvv") << std::endl;

    std::cout << root->SearchPresence("tutu") << std::endl;
    root->SearchSuggestions("tutu");
    std::cout << root->SearchPresence("tutu") << std::endl;

    root->SearchSuggestions("tutuv");
    std::cout << root->SearchPresence("tutuv") << std::endl;

    root->SearchSuggestions("tutuvs");

    root->SearchFreqSuggestions(
        "tu");  // The top 3 frequent entries with prefix tu are tutu, tutuv &
                // tutuvs respectively
    root->SearchSuggestions(
        "");  // Empty search to list all the entries in the trie
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char const *argv[]) {
    test();  // run self-test implementations
    return 0;
}
