/**
 * @file
 * @author [achance6](https://github.com/achance6)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Storage mechanism using [linear probing
 * hash](https://en.wikipedia.org/wiki/Linear_probing) keys.
 * @note The implementation can be optimized by using OOP style.
 */
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace {  // keep the code local to this file by assigning them to an unnamed
             // namespace

/** Node object that holds key */
struct Entry {
    explicit Entry(int key = notPresent) : key(key) {}  ///< constructor
    int key;                                            ///< key value
};

// fwd declarations
bool putProber(Entry entry, int key);
bool searchingProber(Entry entry, int key);
void add(int key);

// Undocumented globals
int notPresent;
std::vector<Entry> table;
int totalSize;
int tomb = -1;
int size;
bool rehashing;

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

/** Performs linear probing to resolve collisions
 * @param key key value to hash
 * @return hash value of the key
 */
int linearProbe(int key, bool searching) {
    int hash = static_cast<int>(hashFxn(key));
    int i = 0;
    Entry entry;
    do {
        int index = static_cast<int>((hash + i) % totalSize);
        entry = table[index];
        if (searching) {
            if (entry.key == notPresent) {
                return notPresent;
            }
            if (searchingProber(entry, key)) {
                cout << "Found key!" << endl;
                return index;
            }
            cout << "Found tombstone or equal hash, checking next" << endl;
            i++;
        } else {
            if (putProber(entry, key)) {
                if (!rehashing) {
                    cout << "Spot found!" << endl;
                }
                return index;
            }
            if (!rehashing) {
                cout << "Spot taken, looking at next" << endl;
            }
            i++;
        }
        if (i == totalSize) {
            cout << "Linear probe failed" << endl;
            return notPresent;
        }
    } while (entry.key != notPresent);
    return notPresent;
}

/** Finds empty spot
 * @param entry instance to check in
 * @param key key value to hash
 * @return hash value of the key
 */
bool putProber(const Entry& entry, int key) {
    if (entry.key == notPresent || entry.key == tomb) {
        return true;
    }
    return false;
}

/** Looks for a matching key
 * @param entry instance to check in
 * @param key key value to hash
 * @return hash value of the key
 */
bool searchingProber(const Entry& entry, int key) {
    if (entry.key == key) {
        return true;
    }
    return false;
}

/** Function to displays the table
 * @returns none
 */
void display() {
    for (int i = 0; i < totalSize; i++) {
        if (table[i].key == notPresent) {
            cout << " Empty ";
        } else if (table[i].key == tomb) {
            cout << " Tomb ";
        } else {
            cout << " ";
            cout << table[i].key;
            cout << " ";
        }
    }
    cout << endl;
}

/** Rehashes the table into a bigger table
 * @returns None
 */
void rehash() {
    // Necessary so wall of add info isn't printed all at once
    rehashing = true;
    int oldSize = totalSize;
    std::vector<Entry> oldTable(table);
    // Really this should use the next prime number greater than totalSize *
    // 2
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
    cout << "Table was rehashed, new size is: " << totalSize << endl;
}

/** Adds entry using linear probing. Checks for load factor here
 * @param key key value to hash and add
 */
void add(int key) {
    int index = linearProbe(key, false);
    table[index].key = key;
    // Load factor greater than 0.5 causes resizing
    if (++size / static_cast<double>(totalSize) >= 0.5) {
        rehash();
    }
}

/** Removes key. Leaves tombstone upon removal.
 * @param key key value to hash and remove
 */
void remove(int key) {
    int index = linearProbe(key, true);
    if (index == notPresent) {
        cout << "key not found" << endl;
    }
    cout << "Removal Successful, leaving tomb" << endl;
    table[index].key = tomb;
    size--;
}

/** Information about the adding process
 * @param key key value to hash and add
 */
void addInfo(int key) {
    cout << "Initial table: ";
    display();
    cout << endl;
    cout << "hash of " << key << " is " << hashFxn(key) << " % " << totalSize
         << " == " << hashFxn(key) % totalSize;
    cout << endl;
    add(key);
    cout << "New table: ";
    display();
}

/** Information about removal process
 * @param key key value to hash and remove
 */
void removalInfo(int key) {
    cout << "Initial table: ";
    display();
    cout << endl;
    cout << "hash of " << key << " is " << hashFxn(key) << " % " << totalSize
         << " == " << hashFxn(key) % totalSize;
    cout << endl;
    remove(key);
    cout << "New table: ";
    display();
}
}  // namespace

/** Main function
 * @returns 0 on success
 */
int main() {
    int cmd = 0, hash = 0, key = 0;
    cout << "Enter the initial size of Hash Table. = ";
    cin >> totalSize;
    table = std::vector<Entry>(totalSize);
    bool loop = true;
    while (loop) {
        system("pause");
        cout << endl;
        cout << "PLEASE CHOOSE -" << endl;
        cout << "1. Add key. (Numeric only)" << endl;
        cout << "2. Remove key." << endl;
        cout << "3. Find key." << endl;
        cout << "4. Generate Hash. (Numeric only)" << endl;
        cout << "5. Display Hash table." << endl;
        cout << "6. Exit." << endl;
        cin >> cmd;
        switch (cmd) {
            case 1:
                cout << "Enter key to add = ";
                cin >> key;
                addInfo(key);
                break;
            case 2:
                cout << "Enter key to remove = ";
                cin >> key;
                removalInfo(key);
                break;
            case 3: {
                cout << "Enter key to search = ";
                cin >> key;
                Entry entry = table[linearProbe(key, true)];
                if (entry.key == notPresent) {
                    cout << "Key not present";
                }
                break;
            }
            case 4:
                cout << "Enter element to generate hash = ";
                cin >> key;
                cout << "Hash of " << key << " is = " << hashFxn(key);
                break;
            case 5:
                display();
                break;
            default:
                loop = false;
                break;
                // delete[] table;
        }
        cout << endl;
    }
    return 0;
}
