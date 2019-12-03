// Copyright 2019

#include<stdlib.h>
#include<iostream>
#include<functional>
#include<string>
#include<cmath>

using std::endl;
using std::cout;
using std::cin;
using std::string;

// fwd declarations
struct Entry;
bool putProber(Entry entry, int key);
bool searchingProber(Entry entry, int key);
void add(int key);

// globals
int notPresent;
struct Entry* table;
int totalSize;
int tomb = -1;
int size;
bool rehashing;

// Node that holds key
struct Entry {
    explicit Entry(int key = notPresent) : key(key) {}
    int key;
};

// Hash a key
int hashFxn(int key) {
    std::hash<int> hash;
    return hash(key);
}

// Performs quadratic probing to resolve collisions
int quadraticProbe(int key, bool searching) {
    int hash = static_cast<int>(fabs(hashFxn(key)));
    int i = 0;
    Entry entry;
    do {
        int index = std::round(fabs((hash +
            static_cast<int>(std::round(std::pow(i, 2)))) % totalSize));
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
                if (!rehashing) cout << "Spot found!" << endl;
                return index;
            }
            if (!rehashing) {
                cout << "Spot taken, looking at next (next index = " <<
                    std::round(fabs((hash + static_cast<int>(std::round(
                        std::pow(i + 1, 2)))) % totalSize)) << endl;
            }
            i++;
        }
        if (i == totalSize * 100) {
            cout << "Quadratic probe failed (infinite loop)" << endl;
            return notPresent;
        }
    } while (entry.key != notPresent);
    return notPresent;
}

// Finds empty spot
bool putProber(Entry entry, int key) {
    if (entry.key == notPresent || entry.key == tomb) {
        return true;
    }
    return false;
}

// Looks for a matching key
bool searchingProber(Entry entry, int key) {
    if (entry.key == key) return true;
    return false;
}

// Helper
Entry find(int key) {
    int index = quadraticProbe(key, true);
    if (index == notPresent) return Entry();
    return table[index];
}

// Displays the table
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

// Rehashes the table into a bigger table
void rehash() {
    // Necessary so wall of add info isn't printed all at once
    rehashing = true;
    int oldSize = totalSize;
    Entry* oldTable = table;
    // Really this should use the next prime number greater than totalSize * 2
    table = new Entry[totalSize * 2];
    totalSize *= 2;
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].key != -1 && oldTable[i].key != notPresent) {
            size--;  // Size stays the same (add increments size)
            add(oldTable[i].key);
        }
    }
    delete[] oldTable;
    rehashing = false;
    cout << "Table was rehashed, new size is: " << totalSize << endl;
}

// Checks for load factor here
void add(int key) {
    Entry * entry = new Entry();
    entry->key = key;
    int index = quadraticProbe(key, false);
    table[index] = *entry;
    // Load factor greater than 0.5 causes resizing
    if (++size/ static_cast<double>(totalSize) >= 0.5) {
        rehash();
    }
}

// Removes key. Leaves tombstone upon removal.
void remove(int key) {
    int index = quadraticProbe(key, true);
    if (index == notPresent) {
        cout << "key not found" << endl;
    }
    table[index].key = tomb;
    cout << "Removal successful, leaving tombstone" << endl;
    size--;
}

// Information about the adding process
void addInfo(int key) {
    cout << "Initial table: ";
    display();
    cout << endl;
    cout << "hash of " << key << " is " << hashFxn(key) << " % "
        << totalSize << " == " << fabs(hashFxn(key) % totalSize);
    cout << endl;
    add(key);
    cout << "New table: ";
    display();
}

// Information about removal process
void removalInfo(int key) {
    cout << "Initial table: ";
    display();
    cout << endl;
    cout << "hash of " << key << " is " << hashFxn(key)
        << " % " << totalSize << " == " << hashFxn(key) % totalSize;
    cout << endl;
    remove(key);
    cout << "New table: ";
    display();
}

// I/O
int main(void) {
    int cmd, hash, key;
    cout << "Enter the initial size of Hash Table. = ";
    cin >> totalSize;
    table = new Entry[totalSize];
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
            Entry entry = table[quadraticProbe(key, true)];
            if (entry.key == notPresent) {
                cout << "Key not present";
            }
            break;
        }
        case 4:
            cout << "Enter element to generate hash = ";
            cin >> key;
            cout << "Hash of " << key << " is = " << fabs(hashFxn(key));
            break;
        case 5:
            display();
            break;
        default:
            loop = false;
            break;
            delete[] table;
        }
        cout << endl;
    }
    return 0;
}
