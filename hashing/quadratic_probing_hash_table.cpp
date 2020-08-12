/**
 * @file
 * @author [achance6](https://github.com/achance6)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Storage mechanism using [quadratic probing
 * hash](https://en.wikipedia.org/wiki/Quadratic_probing) keys.
 * @note The implementation can be optimized by using OOP style.
 */
#include <cmath>
#include <iostream>
#include <vector>

/**
 * @addtogroup open_addressing Open Addressing
 * @{
 * @namespace quadratic_probing
 * @brief An implementation of hash table using [quadratic
 * probing](https://en.wikipedia.org/wiki/Quadratic_probing) algorithm.
 */
namespace quadratic_probing {
// fwd declarations
using Entry = struct Entry;
bool putProber(const Entry& entry, int key);
bool searchingProber(const Entry& entry, int key);
void add(int key);

// globals
int notPresent;
std::vector<Entry> table;
int totalSize;
int tomb = -1;
int size;
bool rehashing;

/** Node that holds key
 */
struct Entry {
    explicit Entry(int key = notPresent) : key(key) {}  ///< constructor
    int key;                                            ///< key value
};

/** Hash a key
 * @param key key value to hash
 * @returns hash of the key
 */
size_t hashFxn(int key) {
    std::hash<int> hash;
    return hash(key);
}

/** Performs quadratic probing to resolve collisions
 * @param key key value to search/probe
 * @param searching `true` if only searching, `false1 if assigning
 * @returns value of `notPresent`.
 */
int quadraticProbe(int key, bool searching) {
    int hash = static_cast<int>(hashFxn(key));
    int i = 0;
    Entry entry;
    do {
        size_t index =
            (hash + static_cast<size_t>(std::round(std::pow(i, 2)))) %
            totalSize;
        entry = table[index];
        if (searching) {
            if (entry.key == notPresent) {
                return notPresent;
            }
            if (searchingProber(entry, key)) {
                std::cout << "Found key!" << std::endl;
                return index;
            }
            std::cout << "Found tombstone or equal hash, checking next"
                      << std::endl;
            i++;
        } else {
            if (putProber(entry, key)) {
                if (!rehashing) {
                    std::cout << "Spot found!" << std::endl;
                }
                return index;
            }
            if (!rehashing) {
                std::cout << "Spot taken, looking at next (next index = "
                          << (hash + static_cast<size_t>(
                                         std::round(std::pow(i + 1, 2)))) %
                                 totalSize
                          << std::endl;
            }
            i++;
        }
        if (i == totalSize * 100) {
            std::cout << "Quadratic probe failed (infinite loop)" << std::endl;
            return notPresent;
        }
    } while (entry.key != notPresent);
    return notPresent;
}

/** Finds empty spot
 * @param entry Instance of table entry
 * @param key key value to search/probe
 * @returns `true` if key is present
 * @returns `false` if key is absent
 */
bool putProber(const Entry& entry, int key) {
    if (entry.key == notPresent || entry.key == tomb) {
        return true;
    }
    return false;
}

/** Looks for a matching key
 * @param entry Instance of table entry
 * @param key key value to search/probe
 * @returns `true` if key matches the entry
 * @returns `false` if key does not match the entry
 */
bool searchingProber(const Entry& entry, int key) {
    if (entry.key == key) {
        return true;
    }
    return false;
}

/** Get the entry instance corresponding to a key
 * @param key key value to search/probe
 * @returns if present, the entry instance
 * @returns if not present, a new instance
 */
Entry find(int key) {
    int index = quadraticProbe(key, true);
    if (index == notPresent) {
        return Entry();
    }
    return table[index];
}

/** Displays the table
 * @returns None
 */
void display() {
    for (int i = 0; i < totalSize; i++) {
        if (table[i].key == notPresent) {
            std::cout << " Empty ";
        } else if (table[i].key == tomb) {
            std::cout << " Tomb ";
        } else {
            std::cout << " ";
            std::cout << table[i].key;
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

/** Rehashes the table into a bigger table
 * @returns none
 */
void rehash() {
    // Necessary so wall of add info isn't printed all at once
    rehashing = true;
    int oldSize = totalSize;
    std::vector<Entry> oldTable(table);
    // Really this should use the next prime number greater than totalSize * 2
    totalSize *= 2;
    table = std::vector<Entry>(totalSize);
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].key != -1 && oldTable[i].key != notPresent) {
            size--;  // Size stays the same (add increments size)
            add(oldTable[i].key);
        }
    }
    // delete[] oldTable;
    rehashing = false;
    std::cout << "Table was rehashed, new size is: " << totalSize << std::endl;
}

/** Checks for load factor here
 * @param key  key value to hash and add to table
 */
void add(int key) {
    int index = quadraticProbe(key, false);
    table[index].key = key;
    // Load factor greater than 0.5 causes resizing
    if (++size / static_cast<double>(totalSize) >= 0.5) {
        rehash();
    }
}

/** Removes key. Leaves tombstone upon removal.
 * @param key  key value to hash and remove from table
 */
void remove(int key) {
    int index = quadraticProbe(key, true);
    if (index == notPresent) {
        std::cout << "key not found" << std::endl;
    }
    table[index].key = tomb;
    std::cout << "Removal successful, leaving tombstone" << std::endl;
    size--;
}

/** Information about the adding process
 * @param key  key value to hash and add to table
 */
void addInfo(int key) {
    std::cout << "Initial table: ";
    display();
    std::cout << std::endl;
    std::cout << "hash of " << key << " is " << hashFxn(key) << " % "
              << totalSize << " == " << hashFxn(key) % totalSize;
    std::cout << std::endl;
    add(key);
    std::cout << "New table: ";
    display();
}

/** Information about removal process
 * @param key  key value to hash and remove from table
 */
void removalInfo(int key) {
    std::cout << "Initial table: ";
    display();
    std::cout << std::endl;
    std::cout << "hash of " << key << " is " << hashFxn(key) << " % "
              << totalSize << " == " << hashFxn(key) % totalSize;
    std::cout << std::endl;
    remove(key);
    std::cout << "New table: ";
    display();
}

}  // namespace quadratic_probing
/**
 * @}
 */

using quadratic_probing::Entry;
using quadratic_probing::table;
using quadratic_probing::totalSize;

/** Main function
 * @returns None
 */
int main() {
    int cmd = 0, hash = 0, key = 0;
    std::cout << "Enter the initial size of Hash Table. = ";
    std::cin >> totalSize;
    table = std::vector<Entry>(totalSize);
    bool loop = true;
    while (loop) {
        std::cout << std::endl;
        std::cout << "PLEASE CHOOSE -" << std::endl;
        std::cout << "1. Add key. (Numeric only)" << std::endl;
        std::cout << "2. Remove key." << std::endl;
        std::cout << "3. Find key." << std::endl;
        std::cout << "4. Generate Hash. (Numeric only)" << std::endl;
        std::cout << "5. Display Hash table." << std::endl;
        std::cout << "6. Exit." << std::endl;
        std::cin >> cmd;
        switch (cmd) {
            case 1:
                std::cout << "Enter key to add = ";
                std::cin >> key;
                quadratic_probing::addInfo(key);
                break;
            case 2:
                std::cout << "Enter key to remove = ";
                std::cin >> key;
                quadratic_probing::removalInfo(key);
                break;
            case 3: {
                std::cout << "Enter key to search = ";
                std::cin >> key;
                quadratic_probing::Entry entry =
                    quadratic_probing::table[quadratic_probing::quadraticProbe(
                        key, true)];
                if (entry.key == quadratic_probing::notPresent) {
                    std::cout << "Key not present";
                }
                break;
            }
            case 4:
                std::cout << "Enter element to generate hash = ";
                std::cin >> key;
                std::cout << "Hash of " << key
                          << " is = " << quadratic_probing::hashFxn(key);
                break;
            case 5:
                quadratic_probing::display();
                break;
            default:
                loop = false;
                break;
                // delete[] table;
        }
        std::cout << std::endl;
    }
    return 0;
}
