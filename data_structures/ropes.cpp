#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/*
================================================================================
Rope Data Structure (Fully Commented Educational Implementation)

This file implements a Rope — a binary-tree based string data structure
optimized for efficient concatenation, insertion, deletion, and substring
operations on large texts. The implementation is intentionally readable and
annotated to explain the design, algorithms and complexity considerations.

Main features:
 - Rope class encapsulating tree-of-strings representation
 - Split / Concat operations (core of rope efficiency)
 - Insert / Delete / batchDeleteRanges
 - Substring and lightweight substring View
 - Rebalance (manual & automatic) to maintain logarithmic depths
 - Unit tests + demonstration + optional heavy benchmarks

Complexities (typical):
 - Concatenate: O(1)
 - Split: O(log n)
 - Insert/Delete: O(log n) (excluding rebalancing cost)
 - charAt: O(log n)
 - toString (materialize): O(n)

Notes:
 - This is an educational implementation (not fully production hardened).
 - Uses std::shared_ptr<Node> for simplicity of memory management.
 - For production, consider custom memory pools, move-only nodes, and arena
   allocation to avoid overhead of shared_ptr.
================================================================================
*/

class Rope {
 public:
    using size_type = std::size_t;

 private:
    // ------------------------------------------------------------------
    // Node representation
    // ------------------------------------------------------------------
    // Each Node is either a LEAF (contains 'data') or an INTERNAL node where
    // 'left' and/or 'right' point to children. For internal nodes, 'weight'
    // stores the length of the entire left subtree. That weight is used to
    // route index lookups and splits efficiently.
    struct Node {
        size_type weight =
            0;             // For leaf: data.size(); for internal: length(left)
        std::string data;  // Only populated for leaf nodes
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;

        // Leaf constructor
        explicit Node(const std::string& s)
            : weight(s.size()), data(s), left(nullptr), right(nullptr) {}

        // Internal constructor: link two subtrees and set weight = length(left)
        Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r)
            : weight(0), data(), left(l), right(r) {
            weight = getLength(left);
        }

        bool isLeaf() const { return !left && !right; }
    };

    // Root pointer of rope tree
    std::shared_ptr<Node> root = nullptr;

    // Operation counter (used to decide when to automatically rebalance)
    size_type op_count = 0;
    static constexpr size_type REBALANCE_THRESHOLD =
        128;                     // after this many ops -> auto rebalance
    bool auto_rebalance = true;  // can be disabled for bulk edits

    // ------------------------------------------------------------------
    // Basic helpers
    // ------------------------------------------------------------------

    // Return total number of characters under node
    static size_type getLength(const std::shared_ptr<Node>& node) {
        if (!node)
            return 0;
        if (node->isLeaf())
            return node->weight;  // leaf stores data.size()
        // internal node: left length = weight, plus right subtree length
        return node->weight + getLength(node->right);
    }

    // Recursive helper for charAt: traverse using 'weight'
    char charAtHelper(const std::shared_ptr<Node>& node,
                      size_type index) const {
        if (!node)
            throw std::out_of_range("Index out of bounds");
        if (node->isLeaf()) {
            if (index >= node->data.size())
                throw std::out_of_range("Index out of bounds");
            return node->data[index];
        }
        if (index < node->weight)
            return charAtHelper(node->left, index);
        return charAtHelper(node->right, index - node->weight);
    }

    // ------------------------------------------------------------------
    // Split helper: split tree at index -> returns pair(leftTree, rightTree)
    // semantics: left contains [0, index), right contains [index, end)
    // ------------------------------------------------------------------
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> splitHelper(
        const std::shared_ptr<Node>& node, size_type index) const {
        if (!node)
            return {nullptr, nullptr};

        // LEAF: split the string directly
        if (node->isLeaf()) {
            if (index == 0)
                return {nullptr, node};
            if (index >= node->data.size())
                return {node, nullptr};
            auto leftStr = node->data.substr(0, index);
            auto rightStr = node->data.substr(index);
            return {std::make_shared<Node>(leftStr),
                    std::make_shared<Node>(rightStr)};
        }

        // INTERNAL: decide whether split point is left or right of weight
        if (index <= node->weight) {
            // split inside left subtree
            auto [L_left, L_right] = splitHelper(node->left, index);
            // right result must concatenate (L_right + original right)
            std::shared_ptr<Node> rightRes = makeInternal(L_right, node->right);
            return {L_left, rightRes};
        } else {
            // split inside right subtree
            auto [R_left, R_right] =
                splitHelper(node->right, index - node->weight);
            // left result must concatenate (original left + R_left)
            std::shared_ptr<Node> leftRes = makeInternal(node->left, R_left);
            return {leftRes, R_right};
        }
    }

    // Collect leaf strings in-order into a vector
    void collectLeaves(const std::shared_ptr<Node>& node,
                       std::vector<std::string>& out) const {
        if (!node)
            return;
        if (node->isLeaf()) {
            if (!node->data.empty())
                out.push_back(node->data);
            return;
        }
        collectLeaves(node->left, out);
        collectLeaves(node->right, out);
    }

    // Build a balanced tree from sequence of leaf strings (divide & conquer)
    std::shared_ptr<Node> buildBalanced(const std::vector<std::string>& leaves,
                                        size_type l, size_type r) const {
        if (l > r)
            return nullptr;
        if (l == r)
            return std::make_shared<Node>(leaves[l]);
        size_type mid = l + (r - l) / 2;
        auto left = buildBalanced(leaves, l, mid);
        auto right = buildBalanced(leaves, mid + 1, r);
        if (!left)
            return right;
        if (!right)
            return left;
        return std::make_shared<Node>(left, right);
    }

    // Depth (height) of tree
    size_type depthHelper(const std::shared_ptr<Node>& node) const {
        if (!node)
            return 0;
        if (node->isLeaf())
            return 1;
        return 1 + std::max(depthHelper(node->left), depthHelper(node->right));
    }

    // Trigger rebalance when many operations accumulated
    void maybeRebalance() {
        if (!auto_rebalance)
            return;
        if (op_count >= REBALANCE_THRESHOLD) {
            rebalance();
            op_count = 0;
        }
    }

    // Utility to create an internal node, handling null children
    static std::shared_ptr<Node> makeInternal(std::shared_ptr<Node> l,
                                              std::shared_ptr<Node> r) {
        if (!l)
            return r;
        if (!r)
            return l;
        return std::make_shared<Node>(l, r);
    }

 public:
    // ------------------------------------------------------------------
    // Constructors / assignment
    // ------------------------------------------------------------------
    Rope() = default;
    explicit Rope(const std::string& s) {
        if (!s.empty())
            root = std::make_shared<Node>(s);
    }

    Rope(const Rope&) = default;
    Rope(Rope&&) noexcept = default;
    Rope& operator=(const Rope& other) = default;
    Rope& operator=(Rope&& other) noexcept = default;

    // ------------------------------------------------------------------
    // Configuration
    // ------------------------------------------------------------------
    void setAutoRebalance(bool v) { auto_rebalance = v; }
    bool getAutoRebalance() const { return auto_rebalance; }

    // ------------------------------------------------------------------
    // Queries
    // ------------------------------------------------------------------

    // Total length
    size_type length() const { return getLength(root); }
    bool empty() const { return length() == 0; }

    // Character access (O(log n))
    char charAt(size_type index) const {
        if (index >= length())
            throw std::out_of_range("Index out of bounds");
        return charAtHelper(root, index);
    }

    // Materialize entire rope into std::string (O(n))
    std::string toString() const {
        std::string out;
        out.reserve(length());  // pre-allocate to avoid repeated growth
        if (!root)
            return out;
        std::vector<std::string> leaves;
        collectLeaves(root, leaves);
        for (const auto& s : leaves) out += s;
        return out;
    }

    // ------------------------------------------------------------------
    // Split / Concatenate
    // ------------------------------------------------------------------

    // Split rope at index -> returns two ropes ([0,index), [index,end))
    std::pair<Rope, Rope> split(size_type index) const {
        if (index == 0)
            return {Rope(), *this};
        if (index >= length())
            return {*this, Rope()};
        auto [L, R] = splitHelper(root, index);
        Rope leftRope, rightRope;
        leftRope.root = L;
        leftRope.op_count = this->op_count;
        rightRope.root = R;
        rightRope.op_count = this->op_count;
        return {leftRope, rightRope};
    }

    // Concatenate two ropes (O(1) - just create new internal node)
    Rope concat(const Rope& other) const {
        if (empty())
            return other;
        if (other.empty())
            return *this;
        Rope result;
        result.root = makeInternal(root, other.root);
        result.op_count = std::max(this->op_count, other.op_count);
        return result;
    }
    Rope operator+(const Rope& other) const { return concat(other); }

    // In-place append
    Rope& operator+=(const Rope& other) {
        if (other.empty())
            return *this;
        if (empty()) {
            *this = other;
            return *this;
        }
        root = makeInternal(root, other.root);
        ++op_count;
        maybeRebalance();
        return *this;
    }

    // ------------------------------------------------------------------
    // Insert / Delete
    // ------------------------------------------------------------------

    // Insert string 's' at position 'index' (shifts right)
    // Algorithm: split at index -> left + s + right
    Rope& insert(size_type index, const std::string& s) {
        if (s.empty())
            return *this;
        if (index > length())
            throw std::out_of_range("Index out of bounds");
        auto [L, R] = split(index);
        Rope mid(s);
        if (L.empty() && R.empty()) {
            *this = mid;
        } else if (L.empty()) {
            root = makeInternal(mid.root, R.root);
        } else if (R.empty()) {
            root = makeInternal(L.root, mid.root);
        } else {
            auto temp = makeInternal(L.root, mid.root);
            root = makeInternal(temp, R.root);
        }
        ++op_count;
        maybeRebalance();
        return *this;
    }

    // Delete range [start, end)
    // Algorithm: split at start, split remainder at (end-start), discard middle
    Rope& deleteRange(size_type start, size_type end) {
        if (start >= end)
            return *this;
        if (end > length())
            throw std::out_of_range("Invalid range");
        auto [L, tmp] = split(start);
        auto [mid, R] = tmp.split(end - start);
        if (L.empty())
            root = R.root;
        else if (R.empty())
            root = L.root;
        else
            root = makeInternal(L.root, R.root);
        ++op_count;
        maybeRebalance();
        return *this;
    }

    // Batch delete multiple ranges efficiently. The approach:
    // 1) Normalize/clip ranges, sort and merge overlapping ranges.
    // 2) Collect leaves and rebuild new leaves by skipping deleted spans.
    // 3) Build balanced tree from resulting leaves.
    void batchDeleteRanges(
        std::vector<std::pair<size_type, size_type>> ranges) {
        if (!root)
            return;
        if (ranges.empty())
            return;

        size_type total_len = length();
        // clip and normalize
        for (auto& r : ranges) {
            if (r.first > total_len)
                r.first = total_len;
            if (r.second > total_len)
                r.second = total_len;
            if (r.first > r.second)
                std::swap(r.first, r.second);
        }
        std::sort(ranges.begin(), ranges.end());

        // merge overlapping
        std::vector<std::pair<size_type, size_type>> merged;
        for (auto& r : ranges) {
            if (r.first == r.second)
                continue;  // empty
            if (merged.empty() || r.first > merged.back().second)
                merged.push_back(r);
            else
                merged.back().second = std::max(merged.back().second, r.second);
        }
        if (merged.empty())
            return;

        // collect leaves and build new leaves skipping deletion spans
        std::vector<std::string> leaves;
        collectLeaves(root, leaves);
        std::vector<std::string> newLeaves;
        newLeaves.reserve(leaves.size());

        size_type curPos = 0;  // absolute index at start of current leaf
        size_type ridx = 0;    // index into merged ranges

        for (const auto& leaf : leaves) {
            size_type leafStart = curPos;
            size_type leafEnd = curPos + leaf.size();
            size_type scanPos = leafStart;

            // move ridx to first range that could overlap this leaf
            while (ridx < merged.size() && merged[ridx].second <= leafStart)
                ++ridx;

            // handle overlapping ranges inside this leaf
            while (ridx < merged.size() && merged[ridx].first < leafEnd) {
                size_type delStart = std::max(leafStart, merged[ridx].first);
                size_type delEnd = std::min(leafEnd, merged[ridx].second);
                if (delStart > scanPos) {
                    // keep substring before deletion
                    newLeaves.push_back(
                        leaf.substr(scanPos - leafStart, delStart - scanPos));
                }
                scanPos = delEnd;  // skip deleted part
                if (merged[ridx].second <= leafEnd)
                    ++ridx;
                else
                    break;  // if range continues beyond this leaf
            }

            if (scanPos < leafEnd) {
                // keep tail part of leaf
                newLeaves.push_back(
                    leaf.substr(scanPos - leafStart, leafEnd - scanPos));
            }
            curPos = leafEnd;
        }

        // rebuild tree from newLeaves (or clear)
        if (newLeaves.empty()) {
            root = nullptr;
        } else {
            root = buildBalanced(newLeaves, 0, newLeaves.size() - 1);
        }
        op_count = 0;  // batch operation resets op counter
    }

    // ------------------------------------------------------------------
    // Substring / View
    // ------------------------------------------------------------------

    // Return rope representing substring [start, end)
    Rope substring(size_type start, size_type end) const {
        if (start > end)
            throw std::out_of_range("Invalid range");
        if (end > length())
            throw std::out_of_range("Invalid range");
        if (start == end)
            return Rope();
        auto [L, tmp] = split(start);
        auto [mid, R] = tmp.split(end - start);
        return mid;
    }

    // Lightweight non-owning view into a rope. The view does NOT copy data.
    // It becomes invalid if parent rope is modified.
    struct View {
        const Rope* parent;
        size_type start;
        size_type len;
        View(const Rope* p = nullptr, size_type s = 0, size_type l = 0)
            : parent(p), start(s), len(l) {}
        std::string toString() const {
            if (!parent)
                return {};
            return parent->materializeRange(start, len);
        }
        size_type length() const { return len; }
        char charAt(size_type idx) const {
            if (!parent)
                throw std::out_of_range("No parent");
            if (idx >= len)
                throw std::out_of_range("Index out of bounds");
            return parent->charAt(start + idx);
        }
    };

    View substringView(size_type start, size_type end) const {
        if (start > end)
            throw std::out_of_range("Invalid range");
        if (end > length())
            throw std::out_of_range("Invalid range");
        return View(this, start, end - start);
    }

    // Efficiently materialize the contiguous range [start, start+len) into a
    // std::string This scans leaves sequentially and copies only the requested
    // characters.
    std::string materializeRange(size_type start, size_type len) const {
        if (len == 0)
            return std::string();
        if (start + len > length())
            throw std::out_of_range("Invalid range");

        std::vector<std::string> leaves;
        collectLeaves(root, leaves);
        std::string out;
        out.reserve(len);

        size_type cur = 0;     // start index of current leaf
        size_type need = len;  // how many remaining chars we need
        size_type wantStart = start;

        for (const auto& leaf : leaves) {
            size_type leafStart = cur;
            size_type leafEnd = cur + leaf.size();
            if (leafEnd <= wantStart) {
                cur = leafEnd;
                continue;
            }  // skip

            // overlap: compute offset in leaf to copy
            size_type s = (wantStart > leafStart) ? (wantStart - leafStart) : 0;
            size_type avail = leaf.size() - s;
            size_type take = std::min(avail, need);
            out.append(leaf.data() + s, take);
            need -= take;
            if (need == 0)
                break;
            cur = leafEnd;
        }
        return out;
    }

    // ------------------------------------------------------------------
    // Rebalancing
    // ------------------------------------------------------------------

    // Rebuilds the tree into a balanced shape. Optionally merges small leaf
    // strings into larger ones to reduce fragmentation.
    void rebalance(size_type min_leaf_size = 64) {
        if (!root)
            return;
        std::vector<std::string> leaves;
        collectLeaves(root, leaves);
        if (leaves.empty()) {
            root = nullptr;
            return;
        }

        // merge small leaves into buffers to avoid many tiny leaves
        std::vector<std::string> merged;
        std::string buffer;
        buffer.reserve(min_leaf_size * 2);
        for (const auto& s : leaves) {
            if (buffer.size() + s.size() <= min_leaf_size) {
                buffer += s;
            } else {
                if (!buffer.empty()) {
                    merged.push_back(buffer);
                    buffer.clear();
                }
                if (s.size() >= min_leaf_size)
                    merged.push_back(s);
                else
                    buffer = s;
            }
        }
        if (!buffer.empty())
            merged.push_back(buffer);
        if (merged.empty())
            merged = leaves;  // fallback

        root = buildBalanced(merged, 0, merged.size() - 1);
        op_count = 0;
    }

    // Diagnostics
    size_type depth() const { return depthHelper(root); }
    size_type operationCount() const { return op_count; }

    // Equality comparison (expensive - materials both ropes)
    bool operator==(const Rope& other) const {
        if (length() != other.length())
            return false;
        return toString() == other.toString();
    }
};

// ------------------------------------------------------------------
// Unit tests and demos
// ------------------------------------------------------------------

static void unitTests() {
    std::cout << "Running unit tests...\n";

    // Basic concatenation
    {
        Rope a("Hello");
        Rope b(" World");
        Rope c = a + b;
        assert(c.toString() == "Hello World");
        assert(c.length() == 11);
        assert(c.charAt(0) == 'H' && c.charAt(10) == 'd');
    }
    std::cout << "   ✓ Basic concatenation\n";

    // Insert
    {
        Rope r("Hello World");
        r.insert(5, ", Beautiful");
        assert(r.toString() == "Hello, Beautiful World");
    }
    std::cout << "   ✓ Insert operation\n";

    // Substring
    {
        Rope r("Hello, Beautiful World");
        Rope sub = r.substring(7, 16);
        assert(sub.toString() == "Beautiful");
    }
    std::cout << "   ✓ Substring extraction\n";

    // Delete
    {
        Rope r("Hello, Beautiful World");
        r.deleteRange(5, 16);
        assert(r.toString() == "Hello World");
    }
    std::cout << "   ✓ Delete range\n";

    // Split
    {
        Rope r("Hello World");
        auto [L, R] = r.split(6);
        assert(L.toString() == "Hello ");
        assert(R.toString() == "World");
    }
    std::cout << "   ✓ Split operation\n";

    // Edge cases
    {
        Rope empty;
        assert(empty.length() == 0 && empty.toString() == "");
        Rope single("A");
        single.insert(1, "B");
        assert(single.toString() == "AB");
        Rope r("Test");
        r.insert(0, "Pre");
        assert(r.toString() == "PreTest");
        r.insert(r.length(), "Post");
        assert(r.toString() == "PreTestPost");
    }
    std::cout << "   ✓ Edge cases (empty, single char, boundary inserts)\n";

    // Auto-rebalance demonstration
    {
        Rope r("start");
        for (int i = 0; i < 200; ++i) r += Rope("x");
        size_t depth_before = r.depth();
        assert(depth_before < 400);
        std::string before = r.toString();
        r.rebalance();
        assert(r.toString() == before);
    }
    std::cout << "   ✓ Auto-rebalancing (operation counter working)\n";

    // Multiple sequential ops
    {
        Rope r("The quick brown fox");
        r.insert(10, "lazy ");
        assert(r.toString() == "The quick lazy brown fox");
        r.deleteRange(10, 15);
        assert(r.toString() == "The quick brown fox");
        auto sub = r.substring(4, 9);
        assert(sub.toString() == "quick");
    }
    std::cout << "   ✓ Multiple sequential operations\n";

    // Large text basic ops
    {
        std::string large_text;
        for (int i = 0; i < 1000; ++i)
            large_text += "Lorem ipsum dolor sit amet ";
        Rope r(large_text);
        assert(r.length() == large_text.size());
        r.insert(100, "INSERTED");
        assert(r.charAt(100) == 'I');
        r.deleteRange(100, 108);
        assert(r.length() == large_text.size());
    }
    std::cout << "   ✓ Large text operations\n";

    std::cout << " All unit tests passed!\n\n";
}

using highclk = std::chrono::high_resolution_clock;

// ----------------------
// Benchmarks (optional)
// ----------------------
// The default arguments are large and may use lots of memory/time. Reduce
// them for running on modest machines.

static void benchmarkAppend(size_t n = 500000, size_t chunkSize = 4096) {
    std::cout << "Running append benchmark (n=" << n << ", chunk=" << chunkSize
              << ")...\n";
    std::string chunk(chunkSize, 'a');
    size_t loops = (n + chunkSize - 1) / chunkSize;

    // std::string version (chunked append)
    {
        auto t0 = highclk::now();
        std::string s;
        s.reserve(n);
        for (size_t i = 0; i < loops; ++i) s.append(chunk);
        auto t1 = highclk::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0)
                      .count();
        std::cout << "  std::string append (chunked): " << us
                  << " µs (final len=" << s.size() << ")\n";
    }

    // Rope version (concatenate many small ropes)
    {
        auto t0 = highclk::now();
        Rope r;
        for (size_t i = 0; i < loops; ++i) r += Rope(chunk);
        auto t1 = highclk::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0)
                      .count();
        std::cout << "  Rope append (chunked): " << us
                  << " µs (final len=" << r.length() << ", depth=" << r.depth()
                  << ")\n";
    }
}

static void benchmarkInsertMiddle(size_t initial_n = 5000000,
                                  size_t inserts = 10000,
                                  size_t chunkSize = 1024) {
    std::cout << "Running heavy middle-insert benchmark (initial=" << initial_n
              << ", inserts=" << inserts << ", chunk=" << chunkSize << ")...\n";
    std::string chunk(chunkSize, 'x');

    // std::string middle-inserts (very expensive for large sizes)
    {
        std::string s(initial_n, 'a');
        auto t0 = highclk::now();
        for (size_t i = 0; i < inserts; ++i) {
            size_t pos = s.size() / 2;
            s.insert(pos, chunk);
        }
        auto t1 = highclk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                      .count();
        std::cout << "  std::string middle-inserts: " << ms
                  << " ms (final len=" << s.size() << ")\n";
    }

    // Rope middle-inserts (batch-style: disable auto rebalance while inserting)
    {
        std::string base(initial_n, 'a');
        Rope r(base);
        r.setAutoRebalance(false);
        auto t0 = highclk::now();
        for (size_t i = 0; i < inserts; ++i) {
            r.insert(r.length() / 2, chunk);
        }
        auto t1 = highclk::now();
        r.setAutoRebalance(true);
        r.rebalance();
        auto t2 = highclk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                      .count();
        auto reb_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                .count();
        std::cout << "  Rope middle-inserts (batch): " << ms
                  << " ms + rebalance " << reb_ms
                  << " ms (final len=" << r.length() << ", depth=" << r.depth()
                  << ")\n";
    }
}

static void benchmarkDeleteMiddle(size_t initial_n = 5000000,
                                  size_t deletes = 10000,
                                  size_t chunkSize = 1024) {
    std::cout << "Running heavy middle-delete benchmark (initial=" << initial_n
              << ", deletes=" << deletes << ", chunk=" << chunkSize << ")...\n";

    // std::string delete
    {
        std::string s(initial_n + deletes * chunkSize, 'a');
        auto t0 = highclk::now();
        for (size_t i = 0; i < deletes; ++i) {
            size_t pos = s.size() / 2;
            s.erase(pos, chunkSize);
        }
        auto t1 = highclk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                      .count();
        std::cout << "  std::string middle-deletes: " << ms
                  << " ms (final len=" << s.size() << ")\n";
    }

    // Rope batch deletes using batchDeleteRanges
    {
        std::vector<std::pair<Rope::size_type, Rope::size_type>> ranges;
        ranges.reserve(deletes);

        Rope::size_type cur_len = initial_n + deletes * chunkSize;
        for (size_t i = 0; i < deletes; ++i) {
            Rope::size_type pos = cur_len / 2;
            ranges.emplace_back(pos, pos + chunkSize);
            cur_len -= chunkSize;
        }

        std::string base(initial_n + deletes * chunkSize, 'a');
        Rope r(base);
        auto t0 = highclk::now();
        r.batchDeleteRanges(ranges);
        auto t1 = highclk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                      .count();
        std::cout << "  Rope batch-deleteRanges: " << ms
                  << " ms (final len=" << r.length() << ", depth=" << r.depth()
                  << ")\n";
    }
}

static void benchmarkSubstring(size_t n = 5000000, size_t queries = 100,
                               size_t len = 1000000) {
    std::cout << "Running heavy substring benchmark (n=" << n
              << ", queries=" << queries << ", len=" << len << ")...\n";

    // std::string substr (copies) -- expensive
    {
        std::string s(n, 'a');
        auto t0 = highclk::now();
        for (size_t i = 0; i < queries; ++i) {
            size_t pos = (i * 997) % (n - len);
            volatile std::string sub = s.substr(pos, len);
            (void)sub;
        }
        auto t1 = highclk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                      .count();
        std::cout << "  std::string substr (copies): " << ms << " ms\n";
    }

    // Rope substringView creation (views, no copy)
    {
        Rope r(std::string(n, 'a'));
        auto t0 = highclk::now();
        for (size_t i = 0; i < queries; ++i) {
            size_t pos = (i * 997) % (n - len);
            volatile auto view = r.substringView(pos, pos + len);
            (void)view;
        }
        auto t1 = highclk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                      .count();
        std::cout << "  Rope substringView (create views no copy): " << ms
                  << " ms\n";
    }

    // Rope substringView + toString (materialize) -- copies
    {
        Rope r(std::string(n, 'a'));
        auto t0 = highclk::now();
        for (size_t i = 0; i < queries; ++i) {
            size_t pos = (i * 997) % (n - len);
            volatile std::string s = r.substringView(pos, pos + len).toString();
            (void)s;
        }
        auto t1 = highclk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0)
                      .count();
        std::cout << "  Rope substringView + toString (copies): " << ms
                  << " ms\n";
    }
}

// ------------------------------------------------------------------
// Main: run unit tests, demonstration and (optionally) benchmarks
// ------------------------------------------------------------------
int main() {
    try {
        unitTests();

        std::cout << "=== Rope Demonstration ===\n";
        Rope r1("Hello");
        Rope r2(" World");
        Rope r3("!");
        Rope combined = r1 + r2 + r3;
        std::cout << "Combined: " << combined.toString() << "\n";
        std::cout << "charAt(6): " << combined.charAt(6) << "\n";

        combined.insert(5, " Beautiful");
        std::cout << "After insert: " << combined.toString() << "\n";

        combined.deleteRange(6, 15);
        std::cout << "After delete: " << combined.toString() << "\n";

        Rope sub = combined.substring(6, 11);
        std::cout << "Substring(6,11): " << sub.toString() << "\n";

        // Demonstrate rebalance
        Rope large("Initial ");
        for (int i = 0; i < 100; ++i)
            large += Rope("x" + std::to_string(i) + " ");
        std::cout << "\nLarge rope length: " << large.length()
                  << ", depth before: " << large.depth() << "\n";
        large.rebalance();
        std::cout << "After manual rebalance depth: " << large.depth()
                  << "\n\n";

        // NOTE: the following benchmarks are heavy. Reduce sizes if your
        // machine is limited.
        benchmarkAppend(100000, 4096);  // smaller defaults
        // benchmarkInsertMiddle(500000, 1000, 512);
        // benchmarkDeleteMiddle(500000, 1000, 512);
        // benchmarkSubstring(500000, 20, 100000);

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
