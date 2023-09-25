#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<int> cacheList;
    unordered_map<int, list<int>::iterator> cacheMap;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    // Function to access a page
    void accessPage(int page) {
        // Check if the page is in the cache
        if (cacheMap.find(page) != cacheMap.end()) {
            // Move the accessed page to the front of the list (most recently used)
            cacheList.erase(cacheMap[page]);
            cacheList.push_front(page);
            cacheMap[page] = cacheList.begin();
        } else {
            // If the cache is full, remove the least recently used page
            if (cacheList.size() >= capacity) {
                int lruPage = cacheList.back();
                cacheList.pop_back();
                cacheMap.erase(lruPage);
            }
            // Add the new page to the cache
            cacheList.push_front(page);
            cacheMap[page] = cacheList.begin();
        }
    }

    // Function to display the current state of the cache
    void displayCache() {
        for (int page : cacheList) {
            cout << page << " ";
        }
        cout << endl;
    }
};

int main() {
    int cacheCapacity;
    cout << "Enter the cache capacity: ";
    cin >> cacheCapacity;

    LRUCache cache(cacheCapacity);

    int pages[] = {1, 2, 3, 1, 4, 5, 2, 1, 6, 7};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    for (int i = 0; i < numPages; i++) {
        cache.accessPage(pages[i]);
        cout << "Accessed Page: " << pages[i] << ", Cache: ";
        cache.displayCache();
    }

    return 0;
}
