/**
 * @file double_hash_hash_table.cpp
 * @author [achance6](https://github.com/achance6)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Storage mechanism using [double-hashed
 * keys](https://en.wikipedia.org/wiki/Double_hashing).
 * @note The implementation can be optimized by using OOP style.
 */
#include <iostream>
#include <memory>
#include <vector>

/**
 * @addtogroup open_addressing Open Addressing
 * @{
 * @namespace double_hashing
 * @brief An implementation of hash table using [double
 * hashing](https://en.wikipedia.org/wiki/Double_hashing) algorithm.
 */
namespace double_hashing {
// fwd declarations
using Entry = struct Entry;
bool putProber(const Entry& entry, int key);
bool searchingProber(const Entry& entry, int key);
void add(int key);

// Undocumented globals
int notPresent;
std::vector<Entry> table;
int totalSize;
int tomb = -1;
int size;
bool rehashing;

/** Node object that holds key */
struct Entry {
    explicit Entry(int key = notPresent) : key(key) {}  ///< constructor
    int key;                                            ///< key value
};

/**
 * @brief Hash a key. Uses the STL library's `std::hash()` function.
 *
 * @param key value to hash
 * @return hash value of the key
 */
size_t hashFxn(int key) {
    std::hash<int> hash;
    return hash(key);
}

/**
 * @brief Used for second hash function
 *
 * @param key key value to hash
 * @return  hash value of the key
 */
size_t otherHashFxn(int key) {
    std::hash<int> hash;
    return 1 + (7 - (hash(key) % 7));
}

/**
 * @brief Performs double hashing to resolve collisions
 *
 * @param key key value to apply double-hash on
 * @param searching `true` to check for conflicts
 * @return Index of key when found
 * @return new hash if no conflicts present
 */
int doubleHash(int key, bool searching) {
    int hash = static_cast<int>(hashFxn(key));
    int i = 0;
    Entry entry;
    do {
        int index =
            static_cast<int>(hash + (i * otherHashFxn(key))) % totalSize;
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
                std::cout << "Spot taken, looking at next (next index:"
                          << " "
                          << static_cast<int>(hash + (i * otherHashFxn(key))) %
                                 totalSize
                          << ")" << std::endl;
            }
            i++;
        }
        if (i == totalSize * 100) {
            std::cout << "DoubleHash probe failed" << std::endl;
            return notPresent;
        }
    } while (entry.key != notPresent);
    return notPresent;
}

/** Finds empty spot in a vector
 * @param entry vector to search in
 * @param key key to search for
 * @returns `true` if key is not present or is a `toumb`
 * @returns `false` is already occupied
 */
bool putProber(const Entry& entry, int key) {
    if (entry.key == notPresent || entry.key == tomb) {
        return true;
    }
    return false;
}

/** Looks for a matching key
 * @param entry vector to search in
 * @param key key value to search
 * @returns `true` if found
 * @returns `false` if not found
 */
bool searchingProber(const Entry& entry, int key) {
    if (entry.key == key) {
        return true;
    }
    return false;
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
 * @returns None
 */
void rehash() {
    // Necessary so wall of add info isn't printed all at once
    rehashing = true;
    int oldSize = totalSize;
    std::vector<Entry> oldTable(table);
    // Really this should use the next prime number greater than totalSize * 2
    table = std::vector<Entry>(totalSize * 2);
    totalSize *= 2;
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].key != -1 && oldTable[i].key != notPresent) {
            size--;  // Size stays the same (add increments size)
            add(oldTable[i].key);
        }
    }
    // delete[] oldTable;
    // oldTable.reset();

    rehashing = false;
    std::cout << "Table was rehashed, new size is: " << totalSize << std::endl;
}

/** Checks for load factor here
 * @param key key value to add to the table
 */
void add(int key) {
    // auto* entry = new Entry();
    // entry->key = key;
    int index = doubleHash(key, false);
    table[index].key = key;
    // Load factor greater than 0.5 causes resizing
    if (++size / static_cast<double>(totalSize) >= 0.5) {
        rehash();
    }
}

/** Removes key. Leaves tombstone upon removal.
 * @param key key value to remove
 */
void remove(int key) {
    int index = doubleHash(key, true);
    if (index == notPresent) {
        std::cout << "key not found" << std::endl;
    }
    table[index].key = tomb;
    std::cout << "Removal successful, leaving tombstone" << std::endl;
    size--;
}

/** Information about the adding process
 * @param key key value to add to table
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
 * @param key key value to remove from table
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
}  // namespace double_hashing
/**
 * @}
 */

using double_hashing::Entry;
using double_hashing::table;
using double_hashing::totalSize;

/** Main program
 * @returns 0 on success
 */
int main() {
    int cmd = 0, key = 0;
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
                double_hashing::addInfo(key);
                break;
            case 2:
                std::cout << "Enter key to remove = ";
                std::cin >> key;
                double_hashing::removalInfo(key);
                break;
            case 3: {
                std::cout << "Enter key to search = ";
                std::cin >> key;
                Entry entry = table[double_hashing::doubleHash(key, true)];
                if (entry.key == double_hashing::notPresent) {
                    std::cout << "Key not present";
                }
                break;
            }
            case 4:
                std::cout << "Enter element to generate hash = ";
                std::cin >> key;
                std::cout << "Hash of " << key
                          << " is = " << double_hashing::hashFxn(key);
                break;
            case 5:
                double_hashing::display();
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
