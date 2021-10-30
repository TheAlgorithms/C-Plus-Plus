/**
 * @file
 * @brief An implementation of a median calculation of a sliding window along a
 * data stream
 *
 * @details
 * Given a stream of integers, the algorithm calculates the median of a fixed
 * size window at the back of the stream. The leading time complexity of this
 * algorithm is O(log(N), and it is inspired by the known algorithm to [find
 * median from (infinite) data
 * stream](https://www.tutorialcup.com/interview/algorithm/find-median-from-data-stream.htm),
 * with the proper modifications to account for the finite window size for which
 * the median is requested
 *
 * ### Algorithm
 * The sliding window is managed by a list, which guarantees O(1) for both
 * pushing and popping. Each new value is pushed to the window back, while a
 * value from the front of the window is popped. In addition, the algorithm
 * manages a multi-value binary search tree (BST), implemented by std::multiset.
 * For each new value that is inserted into the window, it is also inserted to
 * the BST. When a value is popped from the window, it is also erased from the
 * BST. Both insertion and erasion to/from the BST are O(logN) in time, with N
 * the size of the window. Finally, the algorithm keeps a pointer to the root of
 * the BST, and updates its position whenever values are inserted or erased
 * to/from BST. The root of the tree is the median! Hence, median retrieval is
 * always O(1)
 *
 * Time complexity: O(logN). Space complexity: O(N). N - size of window
 * @author [Yaniv Hollander](https://github.com/YanivHollander)
 */
#include <cassert>  /// for assert
#include <cstdlib>  /// for std::rand - needed in testing
#include <ctime>    /// for std::time - needed in testing
#include <list>     /// for std::list - used to manage sliding window
#include <set>  /// for std::multiset - used to manage multi-value sorted sliding window values
#include <vector>  /// for std::vector - needed in testing

/**
 * @namespace probability
 * @brief Probability algorithms
 */
namespace probability {
/**
 * @namespace windowed_median
 * @brief Functions for the Windowed Median algorithm implementation
 */
namespace windowed_median {
using Window = std::list<int>;
using size_type = Window::size_type;

/**
 * @class WindowedMedian
 * @brief A class to calculate the median of a leading sliding window at the
 * back of a stream of integer values.
 */
class WindowedMedian {
    const size_type _windowSize;  ///< sliding window size
    Window _window;  ///< a sliding window of values along the stream
    std::multiset<int> _sortedValues;  ///< a DS to represent a balanced
                                       /// multi-value binary search tree (BST)
    std::multiset<int>::const_iterator
        _itMedian;  ///< an iterator that points to the root of the multi-value
                    /// BST

    /**
     * @brief Inserts a value to a sorted multi-value BST
     * @param value Value to insert
     */
    void insertToSorted(int value) {
        _sortedValues.insert(value);  /// Insert value to BST - O(logN)
        const auto sz = _sortedValues.size();
        if (sz == 1) {  /// For the first value, set median iterator to BST root
            _itMedian = _sortedValues.begin();
            return;
        }

        /// If new value goes to left tree branch, and number of elements is
        /// even, the new median in the balanced tree is the left child of the
        /// median before the insertion
        if (value < *_itMedian && sz % 2 == 0) {
            --_itMedian;  // O(1) - traversing one step to the left child
        }

        /// However, if the new value goes to the right branch, the previous
        /// median's right child is the new median in the balanced tree
        else if (value >= *_itMedian && sz % 2 != 0) {
            ++_itMedian;  /// O(1) - traversing one step to the right child
        }
    }

    /**
     * @brief Erases a value from a sorted multi-value BST
     * @param value Value to insert
     */
    void eraseFromSorted(int value) {
        const auto sz = _sortedValues.size();

        /// If the erased value is on the left branch or the median itself and
        /// the number of elements is even, the new median will be the right
        /// child of the current one
        if (value <= *_itMedian && sz % 2 == 0) {
            ++_itMedian;  /// O(1) - traversing one step to the right child
        }

        /// However, if the erased value is on the right branch or the median
        /// itself, and the number of elements is odd, the new median will be
        /// the left child of the current one
        else if (value >= *_itMedian && sz % 2 != 0) {
            --_itMedian;  // O(1) - traversing one step to the left child
        }

        /// Find the (first) position of the value we want to erase, and erase
        /// it
        const auto it = _sortedValues.find(value);  // O(logN)
        _sortedValues.erase(it);                    // O(logN)
    }

 public:
    /**
     * @brief Constructs a WindowedMedian object
     * @param windowSize Sliding window size
     */
    explicit WindowedMedian(size_type windowSize) : _windowSize(windowSize){};

    /**
     * @brief Insert a new value to the stream
     * @param value New value to insert
     */
    void insert(int value) {
        /// Push new value to the back of the sliding window - O(1)
        _window.push_back(value);
        insertToSorted(value);  // Insert value to the multi-value BST - O(logN)
        if (_window.size() > _windowSize) {  /// If exceeding size of window,
                                             /// pop from its left side
            eraseFromSorted(
                _window.front());  /// Erase from the multi-value BST
                                   /// the window left side value
            _window.pop_front();   /// Pop the left side value from the window -
                                   /// O(1)
        }
    }

    /**
     * @brief Gets the median of the values in the sliding window
     * @return Median of sliding window. For even window size return the average
     * between the two values in the middle
     */
    float getMedian() const {
        if (_sortedValues.size() % 2 != 0) {
            return *_itMedian;  // O(1)
        }
        return 0.5f * *_itMedian + 0.5f * *next(_itMedian);  /// O(1)
    }

    /**
     * @brief A naive and inefficient method to obtain the median of the sliding
     * window. Used for testing!
     * @return Median of sliding window. For even window size return the average
     * between the two values in the middle
     */
    float getMedianNaive() const {
        auto window = _window;
        window.sort();  /// Sort window - O(NlogN)
        auto median =
            *next(window.begin(),
                  window.size() / 2);  /// Find value in the middle - O(N)
        if (window.size() % 2 != 0) {
            return median;
        }
        return 0.5f * median +
               0.5f * *next(window.begin(), window.size() / 2 - 1);  /// O(N)
    }
};
}  // namespace windowed_median
}  // namespace probability

/**
 * @brief Self-test implementations
 * @param vals Stream of values
 * @param windowSize Size of sliding window
 */
static void test(const std::vector<int> &vals, int windowSize) {
    probability::windowed_median::WindowedMedian windowedMedian(windowSize);
    for (const auto val : vals) {
        windowedMedian.insert(val);

        /// Comparing medians: efficient function vs. Naive one
        assert(windowedMedian.getMedian() == windowedMedian.getMedianNaive());
    }
}

/**
 * @brief Main function
 * @param argc command line argument count (ignored)
 * @param argv command line array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, const char *argv[]) {
    /// A few fixed test cases
    test({1, 2, 3, 4, 5, 6, 7, 8, 9},
         3);  /// Array of sorted values; odd window size
    test({9, 8, 7, 6, 5, 4, 3, 2, 1},
         3);  /// Array of sorted values - decreasing; odd window size
    test({9, 8, 7, 6, 5, 4, 5, 6}, 4);     /// Even window size
    test({3, 3, 3, 3, 3, 3, 3, 3, 3}, 3);  /// Array with repeating values
    test({3, 3, 3, 3, 7, 3, 3, 3, 3}, 3);  /// Array with same values except one
    test({4, 3, 3, -5, -5, 1, 3, 4, 5},
         5);  /// Array that includes repeating values including negatives

    /// Array with large values - sum of few pairs exceeds MAX_INT. Window size
    /// is even - testing calculation of average median between two middle
    /// values
    test({470211272, 101027544, 1457850878, 1458777923, 2007237709, 823564440,
          1115438165, 1784484492, 74243042, 114807987},
         6);

    /// Random test cases
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> vals;
    for (int i = 8; i < 100; i++) {
        const auto n =
            1 + std::rand() /
                    ((RAND_MAX + 5u) / 20);  /// Array size in the range [5, 20]
        auto windowSize =
            1 + std::rand() / ((RAND_MAX + 3u) /
                               10);  /// Window size in the range [3, 10]
        vals.clear();
        vals.reserve(n);
        for (int i = 0; i < n; i++) {
            vals.push_back(
                rand() - RAND_MAX);  /// Random array values (positive/negative)
        }
        test(vals, windowSize);  /// Testing randomized test
    }
    return 0;
}
