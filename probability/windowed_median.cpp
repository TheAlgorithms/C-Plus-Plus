/**
 * \file
 * \brief An implementation of a median calculation of a sliding window along a data stream
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <set>

using namespace std;
/**
 * \class WindowedMedian
 * \brief A class to calculate the median of a leading sliding window at the back of a stream of integer values. Each insertion of a new value
 * is O(logN) in time, where N is the size of the sliding window. Each retrieval of median is O(1) in time. Space complexity is O(N)
 */
class WindowedMedian {
    const int _windowSize;                      // Sliding window size
    list<int> _window;                          // A sliding window of values along the stream
    multiset<int> _sortedValues;                // A DS to represent a balanced multi-value binary search tree (BST)
    multiset<int>::const_iterator _itMedian;    // An iterator that points to the root of the multi-value BST
    
    /**
     * \brief Inserts a value to a sorted multi-value BST
     * \param value Value to insert
     */
    void insertToSorted(int value) {
        _sortedValues.insert(value);    // Insert value to BST - O(logN)
        const auto sz = _sortedValues.size();
        if (sz == 1) {  // For the first value, set median iterator to BST root
            _itMedian = _sortedValues.begin();
            return;
        }
        
        // If new value goes to left tree branch, and number of elements is even, the new median in the balanced tree
        // is the left child of the median before the insertion
        if (value < *_itMedian && sz % 2 == 0)
            --_itMedian;    // O(1) - traversing one step to the left child
        
        // However, if the new value goes to the right branch, the previous median's right child is the new median in
        // the balanced tree
        else if (value >= *_itMedian && sz % 2 != 0)
            ++_itMedian;    // O(1) - traversing one step to the right child
    }
    
    /**
     * \brief Erases a value to a sorted multi-value BST
     * \param value Value to insert
     */
    void eraseFromSorted(int value) {
        const auto sz = _sortedValues.size();
        
        // If the erased value is on the left branch or the median itself and the number of elements is even, the new
        // median will be the right child of the current one
        if (value <= *_itMedian && sz % 2 == 0)
            ++_itMedian;    // O(1) - traversing one step to the right child
        
        // However, is the erased value is on the right branch or the median itself, and the number of elements is odd,
        // the new median will be the left child of the current one
        else if (value >= *_itMedian && sz % 2 != 0)
            --_itMedian;    // O(1) - traversing one step to the left child
        
        // Find the (first) position of the value we want to erase, and erase it
        const auto it = _sortedValues.find(value);  // O(logN)
        _sortedValues.erase(it);                    // O(logN)
    }
    
public:
    
    /**
     * \brief Constructs a WindowedMedian object
     * \param windowSize Sliding window size
     */
    WindowedMedian(int windowSize) : _windowSize(windowSize) {};
    
    /**
     * \brief Insert a new value to the stream
     * \param value New value to insert
     */
    void insert(int value) {
        
        // Push new value to the back of the sliding window - O(1)
        _window.push_back(value);
        insertToSorted(value);  // Insert value to the multi-value BST - O(logN)
        if (_window.size() > _windowSize) { // If exceeding size of window, pop from its left side
            eraseFromSorted(_window.front());   // Erase from the multi-value BST the window left side value
            _window.pop_front();    // Pop the left side value from the window - O(1)
        }
    }
    
    /**
     * \brief Gets the median of the values in the sliding window
     * \return Median of sliding window. For even window size return the average between the two values in the middle
     */
    float getMedian() const {
        if (_sortedValues.size() % 2 != 0)
            return *_itMedian;  // O(1)
        return 0.5 * *_itMedian + 0.5 * *next(_itMedian);   // O(1)
    }
    
    /**
     * \brief A naive and inefficient method to obtain the median of the sliding window. Used for testing!
     * \return Median of sliding window. For even window size return the average between the two values in the middle
     */
    float getMedianNaive() const {
        auto window = _window;
        window.sort();      // Sort window - O(NlogN)
        auto median = *next(window.begin(), window.size() / 2); // Find value in the middle - O(N)
        if (window.size() % 2 != 0)
            return median;
        return 0.5 * median + 0.5 * *next(window.begin(), window.size() / 2 - 1);   // O(N)
    }
};

#include <vector>
/**
 * \brief A testing function
 * \param vals Stream of values
 * \param windowSize Size of sliding window
 */
bool test(const vector<int> &vals, int windowSize) {
    WindowedMedian windowedMedian(windowSize);
    bool testSucceeded = true;
    for (int i = 0; i < vals.size(); i++) {
        windowedMedian.insert(vals[i]);
        
        // Comparing medians: efficient function vs. Naive one
        if (windowedMedian.getMedian() != windowedMedian.getMedianNaive()) {
            cout << "i = " << i << ": " << windowedMedian.getMedian() << "!=" <<
                windowedMedian.getMedianNaive() << endl;
            testSucceeded = false;
        }
    }
    return testSucceeded;
}

#include <cstdlib>
#include <ctime>
int main(int argc, const char * argv[]) {
    cout << "TEST 1" << endl;
    if (!test({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3))
        return -1;
    cout << "TEST 2" << endl;
    if (!test({9, 8, 7, 6, 5, 4, 3, 2, 1}, 3))
        return -1;
    cout << "TEST 3" << endl;
    if (!test({9, 8, 7, 6, 5, 4, 5, 6}, 4))
        return -1;
    cout << "TEST 4" << endl;
    if (!test({3, 3, 3, 3, 3, 3, 3, 3, 3}, 3))
        return -1;
    cout << "TEST 5" << endl;
    if (!test({3, 3, 3, 3, -7, 3, 3, 3, 3}, 3))
        return -1;
    cout << "TEST 6" << endl;
    if (!test({4, 3, 3, -5, 7, 1, 3, 4, 5}, 5))
        return -1;
    cout << "TEST 7" << endl;
    if (!test({470211272, 101027544, 1457850878, 1458777923, 2007237709, 823564440, 1115438165, 1784484492,
        74243042, 114807987}, 6))
        return -1;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 8; i < 100; i++) {
        const auto n = 1 + std::rand() / ((RAND_MAX + 5u) / 20);
        auto windowSize = 1 + std::rand() / ((RAND_MAX + 3u) / 10);
        vector<int> vals;
        for (int i = 0; i < n; i++)
            vals.push_back(rand() - RAND_MAX);
        cout << "TEST " << i << endl;
        if (!test(vals, windowSize))
            return -1;
    }
    return 0;
}
