/**
 * @file
 * @brief Implementation of the [Sublist Search
 * Algorithm](https://www.geeksforgeeks.org/sublist-search-search-a-linked-list-in-another-list)
 * @details
 *
 * ### Algorithm
 *
 *  * Sublist search is used to detect a presence of one list in another list.
 *  * Suppose we have a single-node list (let's say the first list), and we
 *  want to ensure that the list is present in another list (let's say the
 * second list), then we can perform the sublist search to find it.
 *
 *  * For instance, the first list contains these elements: 23 -> 30 -> 41,
 *  and the second list contains these elements: 10 -> 15 -> 23 -> 30 -> 41
 *  -> 49. At a glance, we see that the first list presents in the second list.
 *
 * ### Working
 *
 *  * The sublist search algorithm works by comparing the first element
 *  of the first list with the first element of the second list.
 *  * If the two values don't match, it goes to the next element of the
 *  second list. It does this until the two values match.
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace search
 * @brief Searching algorithms
 */
namespace search {
/**
 * @namespace sublist_search
 * @brief Functions for the [Sublist
 * Search](https://www.geeksforgeeks.org/sublist-search-search-a-linked-list-in-another-list)
 * implementation
 */
namespace sublist_search {
/**
 * @brief A Node structure representing a single link Node in a linked list
 */
struct Node {
    uint32_t data = 0;  ///< the key/value of the node
    Node *next{};       ///< pointer to the next node
};

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
 * @brief Give a vector of data,
 * it adds each element of vector in the linked list and return the address of
 * head pointer.
 * @param data A vector of "int" containing the data that is supposed to be
 * stored in nodes of linked list.
 * @returns Node* A head pointer to the linked list.
 */
Node *makeLinkedList(const std::vector<uint64_t> &data) {
    /// This is used in test cases for rapidly creating linked list with 100+
    /// elements, instead of hard-coding 100 elements in test cases.
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

    /// Initialize target pointer to the head node of sublist.
    Node *target_ptr = sublist;

    while (mainList != nullptr) {
        /// Initialize main pointer to the current node of main list.
        Node *main_ptr = mainList;

        while (target_ptr != nullptr) {
            if (main_ptr == nullptr) {
                return false;

            } else if (main_ptr->data == target_ptr->data) {
                /// If the data of target node and main node is equal then move
                /// to the next node of both lists.
                target_ptr = target_ptr->next;
                main_ptr = main_ptr->next;

            } else {
                break;
            }
        }

        if (target_ptr == nullptr) {
            /// Is target pointer becomes null that means the target list is
            /// been traversed without returning false. Which means the sublist
            /// has been found and return ture.
            return true;
        }

        /// set the target pointer again to stating point of target list.
        target_ptr = sublist;

        /// set the main pointer to the next element of the main list and repeat
        /// the algo.
        mainList = mainList->next;
    }

    /// If the main list is exhausted, means sublist does not found, return
    /// false
    return false;
}

}  // namespace sublist_search
}  // namespace search

/**
 * @brief class encapsulating the necessary test cases
 */
class TestCases {
 private:
    /**
     * @brief A function to print given message on console.
     * @tparam T Type of the given message.
     * @returns void
     * */
    template <typename T>
    void log(T msg) {
        // It's just to avoid writing cout and endl
        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:
    /**
     * @brief Executes test cases
     * @returns void
     * */
    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }

    /**
     * @brief A test case contains edge case, Only contains one element.
     * @returns void
     * */
    void testCase_1() {
        const bool expectedOutput = true;  ///< Expected output of this test

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 1 for sublist search Algorithm : ");
        log("Description:");
        log("   EDGE CASE : Only contains one element");

        std::vector<uint64_t> sublistData = {
            6};  ///< Data to make linked list which will be the sublist
        std::vector<uint64_t> mainlistData = {
            2, 5, 6, 7,
            8};  ///< Data to make linked list which will be the main list

        search::sublist_search::Node *sublistLL =
            search::sublist_search::makeLinkedList(
                sublistData);  ///< Sublist to be searched
        search::sublist_search::Node *mainlistLL =
            search::sublist_search::makeLinkedList(
                mainlistData);  ///< Main list in which sublist is to be
                                ///< searched

        bool exists = search::sublist_search::sublistSearch(
            sublistLL, mainlistLL);  ///< boolean, if sublist exist or not

        log("Checking assert expression...");
        assert(exists == expectedOutput);
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");

        delete (sublistLL);
        delete (mainlistLL);
    }

    /**
     * @brief A test case which contains main list of 100 elements and sublist
     * of 20.
     * @returns void
     * */
    void testCase_2() {
        const bool expectedOutput = true;  /// Expected output of this test

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 2 for sublist search Algorithm : ");
        log("Description:");
        log("   contains main list of 100 elements and sublist of 20");

        std::vector<uint64_t> sublistData(
            20);  ///< Data to make linked list which will be the sublist
        std::vector<uint64_t> mainlistData(
            100);  ///< Main list in which sublist is to be searched

        for (int i = 0; i < 100; i++) {
            /// Inserts 100 elements in main list
            mainlistData[i] = i + 1;
        }

        int temp = 0;
        for (int i = 45; i < 65; i++) {
            /// Inserts 20 elements in sublist
            sublistData[temp] = i + 1;
            temp++;
        }

        search::sublist_search::Node *sublistLL =
            search::sublist_search::makeLinkedList(
                sublistData);  ///< Sublist to be searched
        search::sublist_search::Node *mainlistLL =
            search::sublist_search::makeLinkedList(
                mainlistData);  ///< Main list in which sublist is to be
                                ///< searched

        bool exists = search::sublist_search::sublistSearch(
            sublistLL, mainlistLL);  ///< boolean, if sublist exist or not

        log("Checking assert expression...");
        assert(exists == expectedOutput);
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }

    /**
     * @brief A test case which contains main list of 50 elements and sublist
     * of 20.
     * @returns void
     * */
    void testCase_3() {
        const bool expectedOutput = false;  ///< Expected output of this test

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 3 for sublist search Algorithm : ");
        log("Description:");
        log("   contains main list of 50 elements and sublist of 20");

        std::vector<uint64_t> sublistData(20);  ///< Sublist to be searched
        std::vector<uint64_t> mainlistData(
            50);  ///< Main list in which sublist is to be searched

        for (int i = 0; i < 50; i++) {
            /// Inserts 100 elements in main list
            mainlistData.push_back(i + 1);
        }

        for (int i = 45; i < 65; i++) {
            /// Inserts 20 elements in sublist
            sublistData.push_back(i + 1);
        }

        search::sublist_search::Node *sublistLL =
            search::sublist_search::makeLinkedList(
                sublistData);  ///< Sublist to be searched
        search::sublist_search::Node *mainlistLL =
            search::sublist_search::makeLinkedList(
                mainlistData);  ///< Main list in which sublist is to be
                                ///< searched

        bool exists = search::sublist_search::sublistSearch(
            sublistLL, mainlistLL);  ///< boolean, if sublist exist or not

        log("Checking assert expression...");
        assert(exists == expectedOutput);
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
};

/**
 * @brief Self-test implementations
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
    test();  // run self-test implementations

    std::vector<uint64_t> mainlistData = {
        2, 5, 6, 7, 8};  ///< Main list in which sublist is to be searched
    std::vector<uint64_t> sublistData = {6, 8};  ///< Sublist to be searched

    search::sublist_search::Node *mainlistLL =
        search::sublist_search::makeLinkedList(mainlistData);
    search::sublist_search::Node *sublistLL =
        search::sublist_search::makeLinkedList(
            sublistData);  ///< Main list in which sublist is to be
                           ///< searched

    bool exists = search::sublist_search::sublistSearch(
        sublistLL,
        mainlistLL);  ///< boolean to check if the sublist exists or not

    std::cout << "Sublist: " << std::endl;
    search::sublist_search::printLinkedList(sublistLL);

    std::cout << "Main list: " << std::endl;
    search::sublist_search::printLinkedList(mainlistLL);
    std::cout << std::endl;

    if (exists) {
        std::cout << "[TRUE] - sublist found in main list\n";
    } else {
        std::cout << "[FALSE] - sublist NOT found in main list\n";
    }
    return 0;
}
