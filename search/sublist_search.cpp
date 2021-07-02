/**
 * @file
 * @brief Implementation of the [Sublist Search
 * Algorithm](https://www.geeksforgeeks.org/sublist-search-search-a-linked-list-in-another-list)
 * @details
 *       * Sublist search is used to detect a presence of one list in another
 * list.
 *       * Suppose we have a single-node list (let's say the first list), and we
 * want to ensure that the list is present in another list (let's say the second
 * list), then we can perform the sublist search to find it.
 *
 *       * For instance, the first list contains these elements: 23 -> 30 -> 41,
 * and the second list contains these elements: 10 -> 15 -> 23 -> 30 -> 41
 * -> 49. At a glance, we see that the first list presents in the second list.
 *
 *       ### Working
 *          * The sublist search algorithm works by comparing the first element
 * of the first list with the first element of the second list.
 *          * If the two values don't match, it goes to the next element of the
 * second list. It does this until the two values match.
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @brief A Node structure representing a single link Node in a linked list.
 */
struct Node {
    int data;
    Node *next;
};

/**
 * @brief Main searching function
 * @param sublist A linked list which is supposed to be searched in mainList.
 * @param mainList A linked list in which sublist will be searched.
 * @returns true if the sublist is found
 * @returns false if the sublist is NOT found
 */
bool sublistSearch(Node *sublist, Node *mainList) {
    if (sublist == nullptr || mainList == nullptr) {
        return false;
    }

    Node *target_ptr = sublist;

    while (mainList != nullptr) {
        Node *main_ptr = mainList;  // Initialize main pointer to the current
                                    // node of main list.

        while (target_ptr != nullptr) {
            if (main_ptr == nullptr) {
                return false;

            } else if (main_ptr->data == target_ptr->data) {
                // If the data of target node and main node is equal then move
                // to the next node of both lists.
                target_ptr = target_ptr->next;
                main_ptr = main_ptr->next;

            } else {
                break;
            }
        }

        if (target_ptr == nullptr) {
            // Is target pointer becomes null that means the target list is been
            // traversed without returning false. Which means the sublist has
            // been found and return ture.
            return true;
        }

        target_ptr = sublist;  // set the target pointer again to stating point
                               // of target list.
        mainList = mainList->next;  // set the main pointer to the next element
                                    // of the main list and repeat the algo.
    }

    // If the main list is exhausted, means sublist does not found, return false
    return false;
}

/**
 * @brief A simple function to print the linked list
 * @param start The head of the linked list
 * @returns void
 */
void printLinkedList(Node *start) {
    while (start != nullptr) {
        std::cout << "->" << start->data;
        start = start->next;
    }
    std::cout << std::endl;
}

/**
 * @brief Makes a dummy linked list for testing.
 * @param data A vector of "int" containing the data that is supposed to be
 * stored in nodes of linked list.
 * @returns Node* A head pointer to the linked list.
 */
Node *makeLinkedList(const std::vector<int> &data) {
    Node *head = nullptr;
    Node *tail = nullptr;
    for (int i : data) {
        Node *node = new Node;
        node->data = i;
        node->next = nullptr;
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }
    }
    return head;
}

/**
 * A class, encapsulating the necessary test cases.
 */
class TestCases {
 private:
    template <typename T>
    void log(T msg) {
        // It's just to avoid writing cout and endl
        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:
    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }

    void testCase_1() {
        const bool expectedOutput = true;

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 1 for sublist search Algorithm : ");
        log("Description:");
        log("   EDGE CASE : Only contains one element");

        std::vector<int> sublistData = {6};
        std::vector<int> mainlistData = {2, 5, 6, 7, 8};

        Node *sublistLL = makeLinkedList(sublistData);
        Node *mainlistLL = makeLinkedList(mainlistData);

        bool exists = sublistSearch(sublistLL, mainlistLL);

        log("Checking assert expression...");
        assert(exists == expectedOutput);
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");

        delete (sublistLL);
        delete (mainlistLL);
    }

    void testCase_2() {
        const bool expectedOutput = true;

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 2 for sublist search Algorithm : ");
        log("Description:");
        log("   contains main list of 100 elements and sublist of 20");

        std::vector<int> sublistData(20);
        std::vector<int> mainlistData(100);

        for (int i = 0; i < 100; i++) {
            // Inserts 100 elements in main list
            mainlistData[i] = i + 1;
        }

        int temp = 0;
        for (int i = 45; i < 65; i++) {
            // Inserts 20 elements in sublist
            sublistData[temp] = i + 1;
            temp++;
        }

        Node *sublistLL = makeLinkedList(sublistData);
        Node *mainlistLL = makeLinkedList(mainlistData);

        bool exists = sublistSearch(sublistLL, mainlistLL);

        log("Checking assert expression...");
        assert(exists == expectedOutput);
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }

    void testCase_3() {
        const bool expectedOutput = false;

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 3 for sublist search Algorithm : ");
        log("Description:");
        log("   contains main list of 50 elements and sublist of 20");

        std::vector<int> sublistData(20);
        std::vector<int> mainlistData(50);

        for (int i = 0; i < 50; i++) {
            // Inserts 100 elements in main list
            mainlistData.push_back(i + 1);
        }

        for (int i = 45; i < 65; i++) {
            // Inserts 20 elements in sublist
            sublistData.push_back(i + 1);
        }

        Node *sublistLL = makeLinkedList(sublistData);
        Node *mainlistLL = makeLinkedList(mainlistData);

        bool exists = sublistSearch(sublistLL, mainlistLL);

        log("Checking assert expression...");
        assert(exists == expectedOutput);
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
};

/**
 * @brief A test function that runs various checks
 * @returns void
 */
static void test() {
    TestCases tc;
    tc.runTests();
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // Executing various test cases first.

    std::vector<int> mainlistData = {2, 5, 6, 7, 8};
    std::vector<int> sublistData = {6, 8};
    Node *mainlistLL = makeLinkedList(mainlistData);
    Node *sublistLL = makeLinkedList(sublistData);

    bool exists = sublistSearch(sublistLL, mainlistLL);

    std::cout << "Sublist :" << std::endl;
    printLinkedList(sublistLL);

    std::cout << "Main list : " << std::endl;
    printLinkedList(mainlistLL);
    std::cout << std::endl;

    if (exists) {
        std::cout << "[TRUE] - sublist found in main list";
    } else {
        std::cout << "[FALSE] - sublist NOT found in main list";
    }
    return 0;
}
