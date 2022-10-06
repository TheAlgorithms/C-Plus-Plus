/**
 * @file
 * @brief https://en.wikipedia.org/wiki/Trie
 * @details Trie is a handy data structure for string matching/searching/prefix
 * and it's very efficient with both time and space. This implementation is for
 * beginners where I only used strings with only [LOWER CASE ENGLISH LETTERS]
 * for simplicity. It has the 3 most basic and most essential functions.
 * @author [Dipankar](https://github.com/UltimateDip)
 * @see trie_modern.cpp trie_tree.cpp trie_using_hashmap.cpp for adavanced
 * usecase
 */

#include <assert.h>

#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Create a structure called Trie.
 * @param next
 * @param cnt
 * @param end_of_string : 'True' : A string is ending at that Node
 * 'False' : No string is ending at that Node.
 */
struct Trie {
    vector<Trie *> next;  //< this will hold info about next node of the Trie
    int cnt;  //<this will be used to count the number of prefix string till
              // that point (in below e.g. it's explained)
    bool end_of_string;  //<'True' : A string is ending at that Node
                         //'False' : No string is ending at that Node.

    Trie() {
        cnt = 0;
        next.resize(26, nullptr);  //< As only lower case letters are there only
                                   // 26 size is sufficient
        end_of_string = false;
    }
};

/**
 * @brief Counts the number of times string s appeared as a prefix
 * @param s The string that to be searched
 * @param head Head/Root of the Trie data structure
 * @returns '0' if there is no prefix equal to s
 * @returns (otherwise) returns the number of prefix s found
 */
int count_prefix(string s, Trie *head) {
    int ans = 0;
    Trie *temp = head;  //< temporary pointer to traverse and search

    for (auto &x : s) {
        if (temp->next[x - 'a']) {
            temp = temp->next[x - 'a'];
            ans = temp->cnt;
        } else {
            // If no next pointer exist that means there is no prefix as s
            ans = 0;
            break;
        }
    }
    return ans;
}

/**
 * @brief insert the given string in the Trie
 * @param s The string to be inserted
 * @param head Head/Root of the Trie
 */
void insert_string(string s, Trie *head) {
    Trie *temp = head;
    for (auto &x : s) {
        if (!temp->next[x - 'a']) {
            temp->next[x - 'a'] = new Trie();
        }
        temp = temp->next[x - 'a'];
        temp->cnt++;
    }

    temp->end_of_string = true;  //< Need to mark this as true as it's the end
}
/**
 * @brief Checks if the given string exists or not
 * @param s The string to be inserted
 * @param head Head/Root of the Trie
 * @returns `true` if string exists
 * @returns `false` if string doesn't exists
 */
bool is_exist(string s, Trie *head) {
    Trie *temp = head;
    for (auto &x : s) {
        // If next node is null that means doesn't exist
        if (!temp->next[x - 'a']) {
            return false;
        } else {
            temp = temp->next[x - 'a'];
        }
    }

    // At last also need to check if the current node has an end_of_string flag
    // or not. If 'true' that means string exists, else doesn't. More info in
    // example.
    return temp->end_of_string;
}

void test() {
    Trie *head = new Trie();  //< Head/Root of the Trie

    // Insert some strings for checks
    insert_string("dipankar", head);
    insert_string("diwali", head);

    // Check 1
    if (is_exist("dipankar", head)) {
        cout << "\"dipankar\" exists in the trie.\n";  //< This will run
    } else {
        cout << "\"dipankar\" doesn't exist in the trie.\n";
    }

    // Inserting some more strings
    insert_string("github", head);
    insert_string("gitlab", head);

    // Check 2
    if (is_exist("gitlab", head)) {
        cout << "\"git\" exists in the trie.\n";
    } else {
        cout << "\"git\" doesn't exist in the trie.\n";  //< This will run
    }

    // Check 3
    int total_prefix = count_prefix("git", head);
    assert(total_prefix == 2);
    cout << "\"git\" appeared " << total_prefix << " times as a prefix.\n";

    /* Here we can see "git" as a prefix exists 2 times, but as a whole string
     * it doens't exits. This is beacause as after inserting g->i->t we didn't
     * marked the node as "end_of_string=true" flag.
     */

    /******  Output ******
     * "dipankar" exists in the trie.
     * "git" exists in the trie.
     * "git" appeared 2 times as a prefix.
     *
     */
}

int main() {
    test();
    return 0;
}