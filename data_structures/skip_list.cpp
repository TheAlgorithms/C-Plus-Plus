/**
 * @file skip_list.cpp
 * @brief Data structure for fast searching and insertion in \f$O(\log n)\f$
 * time
 * @details
 * A skip list is a data structure that is used for storing a sorted list of
 * items with a help of hierarchy of linked lists that connect increasingly
 * sparse subsequences of the items
 *
 * References used: [GeeksForGeek](https://www.geeksforgeeks.org/skip-list/),
 * [OpenGenus](https://iq.opengenus.org/skip-list) for PseudoCode and Code
 * @author [enqidu](https://github.com/enqidu)
 * @author [Krishna Vedala](https://github.com/kvedala)
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/** \namespace data_structures
 * \brief Data-structure algorithms
 */
namespace data_structures {
constexpr int MAX_LEVEL = 6;        ///< Maximum level of skip list
constexpr float PROBABILITY = 0.5;  ///< Current probability for "coin toss"

/**
 *  Node structure [Key][Node*, Node*...]
 */
struct Node {
    int key;      ///< key integer
    void* value;  ///< pointer of value
    std::vector<std::shared_ptr<Node>>
        forward;  ///< nodes of the given one in all levels

    /**
     * Creates node with provided key, level and value
     * @param key is number that is used for comparision
     * @param level is the maximum level node's going to added
     */
    Node(int key, int level, void* value = nullptr) : key(key), value(value) {
        // Initialization of forward vector
        for (int i = 0; i < (level + 1); i++) {
            forward.push_back(nullptr);
        }
    }
};

/*
A base class for generator that generate uniformly distributed random numbers in
[0, 1).
This is introduced mainly because we want to mock insertion of items.
*/
class BaseRandomNumberGenerator {
 public:
    virtual float operator()() = 0;
};

class CRandBasedGenerator : public BaseRandomNumberGenerator {
 public:
    float operator()() { return static_cast<float>(std::rand()) / RAND_MAX; }
};

/*
    This mock allows us to control the random numbers generated so we can
    ensure the new key is added to the required number of levels.
*/
class MockRandomNumberGenerator : public BaseRandomNumberGenerator {
    std::vector<float> randos;
    int idx;

 public:
    MockRandomNumberGenerator(const int level) : idx(0) {
        randos = std::vector<float>(level - 1, 0.1);
        randos.push_back(0.65);
    }
    float operator()() {
        // We want to control the skip list level for an item we are adding.
        if (idx < randos.size())
            return randos[idx++];
        else
            return randos[randos.size() - 1];
    }
};

/**
 * SkipList class implementation with basic methods
 */
class SkipList {
    // const int MAX_LEVEL;          ///< Maximum level of skip list
    int level;                     ///< Maximum level of the skiplist
    std::shared_ptr<Node> header;  ///< Pointer to the header node
    std::unique_ptr<BaseRandomNumberGenerator> uniformRealNumberGenerator;

    /**
     * Returns random level of the skip list.
     * Every higher level is 2 times less likely.
     * @return random level for skip list
     */
    int randomLevel() {
        int lvl = 0;
        while ((*uniformRealNumberGenerator)() < PROBABILITY &&
               lvl < MAX_LEVEL) {
            lvl++;
        }
        return lvl;
    }

 public:
    /**
     * Skip List constructor. Initializes header, start
     * Node for searching in the list
     */
    SkipList(std::unique_ptr<BaseRandomNumberGenerator> generator) {
        level = 0;
        // Header initialization
        header = std::make_shared<Node>(-1, MAX_LEVEL);
        uniformRealNumberGenerator = std::move(generator);
    }

    void setNumberGenerator(
        std::unique_ptr<BaseRandomNumberGenerator> generator) {
        uniformRealNumberGenerator = std::move(generator);
    }

    /**
     * Inserts elements with given key and value;
     * It's level is computed by randomLevel() function.
     * @param key is number that is used for comparision
     * @param value pointer to a value, that can be any type
     */
    void insertElement(int key, void* value) {
        std::shared_ptr<Node> x = header;
        std::array<std::shared_ptr<Node>, MAX_LEVEL + 1> update;
        update.fill(nullptr);

        for (int i = level; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < key) {
                x = x->forward[i];
            }
            update[i] = x;
        }

        x = x->forward[0];

        bool doesnt_exist = (x == nullptr || x->key != key);
        if (doesnt_exist) {
            int rlevel = randomLevel();

            if (rlevel > level) {
                for (int i = level + 1; i < rlevel + 1; i++) update[i] = header;

                // Update current level
                level = rlevel;
            }

            std::shared_ptr<Node> n =
                std::make_shared<Node>(key, rlevel, value);
            for (int i = 0; i <= rlevel; i++) {
                n->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = n;
            }
        }
    }

    /**
     * Deletes an element by key and prints if has been removed successfully
     * @param key is number that is used for comparision.
     */
    void deleteElement(int key) {
        std::shared_ptr<Node> x = header;

        std::array<std::shared_ptr<Node>, MAX_LEVEL + 1> update;
        update.fill(nullptr);

        for (int i = level; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < key) {
                x = x->forward[i];
            }
            update[i] = x;
        }

        x = x->forward[0];

        bool doesnt_exist = (x == nullptr || x->key != key);

        if (!doesnt_exist) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != x) {
                    break;
                }
                update[i]->forward[i] = x->forward[i];
            }
            /* Remove empty levels*/
            while (level > 0 && header->forward[level] == nullptr) level--;
        }
    }

    /**
     * Searching element in skip list structure
     * @param key is number that is used for comparision
     * @return pointer to the value of the node
     */
    void* searchElement(int key) {
        std::shared_ptr<Node> x = header;

        for (int i = level; i >= 0; i--) {
            while (x->forward[i] && x->forward[i]->key < key) x = x->forward[i];
        }

        x = x->forward[0];
        if (x && x->key == key) {
            return x->value;
        } else {
            return nullptr;
        }
    }

    /**
     * Display skip list level
     */
    void displayList(std::ostream& out, std::string end = " ") {
        for (int i = 0; i <= level; i++) {
            std::shared_ptr<Node> node = header->forward[i];
            // out << /*"Level " << (i) << ": "; */
            while (node != nullptr) {
                out << node->key << " ";
                node = node->forward[i];
            }
            out << end;
        }
    }
};

}  // namespace data_structures

// Testing helper functions
std::string removeItem(std::string input, int key) {
    std::stringstream ss(input);
    std::stringstream out;

    int val;
    while (ss >> val) {
        if (val != key) {
            out << val << " ";
        }
    }

    std::string out_str = out.str();

    // Replace consecutive occurance of 2 or more spaces with one space.
    std::regex regex("(\\s{2,})");

    return std::regex_replace(out.str(), regex, std::string(" "));
}

std::string insertItem(const std::string input, int key, const int level) {
    std::stringstream out;
    int val;

    int count = 0;
    size_t start = 0;
    size_t end = 0;
    // Split levels as marked with ;
    do {
        end = input.find(';', start);
        std::stringstream in(input.substr(start, end - start));

        bool keyInserted = false;
        bool foundFirstLarger = false;
        while (in >> val) {
            if (val == key) {
                return input;
            } else if (foundFirstLarger == false && key < val) {
                foundFirstLarger = true;
                keyInserted = true;
                out << key << " " << val << " ";
            } else {
                out << val << " ";
            }
        }
        if (keyInserted == false) {
            out << key << " ";
        }

        start = end + 1;
        count++;
    } while (end != std::string::npos && count < level);

    while (count < level) {
        out << key << " ";
        count++;
    }
    if (end != std::string::npos) {
        std::regex regex("(;)");
        out << std::regex_replace(input.substr(start), regex, std::string(" "));
    }

    // Replace consecutive occurance of 2 or more spaces with one space.
    std::regex regex("(\\s{2,})");

    return std::regex_replace(out.str(), regex, std::string(" "));
}

data_structures::SkipList createSkipListTestInstance() {
    data_structures::SkipList lst(
        make_unique<data_structures::CRandBasedGenerator>());

    int count = 0;
    for (int j = 0; j < 100; j++) {
        int k = (std::rand() % 512 + 1);
        lst.insertElement(k, &j);
        count++;
    }

    return lst;
}

void isTrue(bool isEqual, std::string failure_msg, std::string success_msg) {
    if (isEqual)
        std::cout << success_msg << std::endl;
    else
        std::cout << failure_msg << std::endl;
}

void testInsertNewKey() {
    data_structures::SkipList lst = createSkipListTestInstance();

    // Add 200 to the skip list
    int key = 200;
    int level = 4;

    // Generate ground truth for the insertion
    std::stringstream ss_insertion_target;
    lst.displayList(ss_insertion_target, " ; ");

    std::string target = insertItem(ss_insertion_target.str(), key, level);

    // This mock allows us to control the random numbers generated so we can
    // ensure the new key is added to the required number of levels.
    lst.setNumberGenerator(
        make_unique<data_structures::MockRandomNumberGenerator>(level));

    // Actually insert into the skip list
    lst.insertElement(key, NULL);

    std::stringstream ss_insertion;
    lst.displayList(ss_insertion, "");

    isTrue(ss_insertion.str() == target, "FAILURE: test_insert_key",
           "SUCCESS: test_insert_key");
}

// TEST: Insert a key that is already in the skip list
void testInsertExistingKey() {
    data_structures::SkipList lst = createSkipListTestInstance();

    // Add 200 to the skip list
    int key = 390;
    int level = 5;

    // Inserting a key that is already there should leave the skip list
    // unchanged. Record the current state of the skip list
    std::stringstream ss_insertion_gt;
    lst.displayList(ss_insertion_gt, "");

    // Actually insert into the skip list
    lst.setNumberGenerator(
        make_unique<data_structures::MockRandomNumberGenerator>(level));
    lst.insertElement(key, NULL);

    std::stringstream ss_insertion;
    lst.displayList(ss_insertion, "");

    isTrue(ss_insertion.str() == ss_insertion_gt.str(),
           "FAILURE: test_insert_existing_key",
           "SUCCESS: test_insert_existing_key");
}

void testInsertLargestKey() {  // TEST: Insert the largest key
    data_structures::SkipList lst = createSkipListTestInstance();

    int key = 10000;
    int level = data_structures::MAX_LEVEL;

    // We will use string processing to insert a key into this string and
    // use the result as a target
    std::stringstream ss_insertion_target;
    lst.displayList(ss_insertion_target, " ; ");
    std::string target = insertItem(ss_insertion_target.str(), key, level);

    // Actually insert into the skip list
    // This mock allows us to control the random numbers generated so we can
    // ensure the new key is added to the required number of levels.
    lst.setNumberGenerator(
        make_unique<data_structures::MockRandomNumberGenerator>(level));

    lst.insertElement(key, NULL);

    std::stringstream ss_insertion;
    lst.displayList(ss_insertion, "");

    isTrue(ss_insertion.str() == target, "FAILURE: test_insert_largest_key",
           "SUCCESS: test_insert_largest_key");
}

// TEST: Insert what would be the smallest key in the skip list
void testInsertSmallestKey() {
    data_structures::SkipList lst = createSkipListTestInstance();

    int key = -10000;
    int level = 1;

    // We will use string processing to insert a key into this string and
    // use the result as a target
    std::stringstream ss_insertion_target;
    lst.displayList(ss_insertion_target, " ; ");
    std::string target = insertItem(ss_insertion_target.str(), key, level);

    // Actually insert into the skip list
    // This mock allows us to control the random numbers generated so we can
    // ensure the new key is added to the required number of levels.
    lst.setNumberGenerator(
        make_unique<data_structures::MockRandomNumberGenerator>(level));

    lst.insertElement(key, NULL);

    std::stringstream ss_insertion;
    lst.displayList(ss_insertion, "");

    isTrue(ss_insertion.str() == target, "FAILURE: test_insert_smallest_key",
           "SUCCESS: test_insert_smallest_key");
}

void testDeleteExistingKey() {  // TEST: Delete an existing key
    data_structures::SkipList lst = createSkipListTestInstance();

    int key = 119;
    int level = 1;

    // We will use string processing to insert a key into this string and
    // use the result as a target
    std::stringstream ss_deletion_target;
    lst.displayList(ss_deletion_target, " ");
    std::string target = removeItem(ss_deletion_target.str(), key);

    // Actually insert into the skip list
    // This mock allows us to control the random numbers generated so we can
    // ensure the new key is added to the required number of levels.
    lst.setNumberGenerator(
        make_unique<data_structures::MockRandomNumberGenerator>(level));

    lst.deleteElement(key);

    std::stringstream ss_deletion;
    lst.displayList(ss_deletion, "");

    isTrue(ss_deletion.str() == target, "FAILURE: test_delete_existing_key",
           "SUCCESS: test_delete_existing_key");
}

// TEST: Delete a key that is not in the skip list
void testDeleteKeyNotInSkipList() {
    data_structures::SkipList lst = createSkipListTestInstance();

    int key = 299;
    int level = 1;

    // We will use string processing to insert a key into this string and
    // use the result as a target
    std::stringstream ss_deletion_target;
    lst.displayList(ss_deletion_target, " ");
    std::string target = removeItem(ss_deletion_target.str(), key);

    // Actually insert into the skip list
    // This mock allows us to control the random numbers generated so we can
    // ensure the new key is added to the required number of levels.
    lst.setNumberGenerator(
        make_unique<data_structures::MockRandomNumberGenerator>(level));

    lst.deleteElement(key);

    std::stringstream ss_deletion;
    lst.displayList(ss_deletion, "");

    isTrue(ss_deletion.str() == target,
           "FAILURE: test_delete_key_not_in_skip_list",
           "SUCCESS: test_delete_key_not_in_skip_list");
}

/**
 * Main function:
 * Creates and inserts random 2^[number of levels]
 * elements into the skip lists and than displays it
 */
int main() {
    std::srand(0);

    data_structures::SkipList lst(
        make_unique<data_structures::CRandBasedGenerator>());

    int count = 0;
    for (int j = 0; j < 100; j++) {
        int k = (std::rand() % 512 + 1);
        lst.insertElement(k, &j);
        count++;
    }
    std::cout << "Number of nodes: " << count << "  "
              << (2 << (data_structures::MAX_LEVEL + 2)) << "\n";

    lst.displayList(std::cout, "\n");

    testInsertNewKey();

    testInsertExistingKey();

    testInsertLargestKey();

    testInsertSmallestKey();

    testDeleteExistingKey();

    testDeleteKeyNotInSkipList();

    return 0;
}
