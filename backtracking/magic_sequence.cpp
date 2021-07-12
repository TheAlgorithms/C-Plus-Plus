/*
 * @brief [Magic sequence](https://www.csplib.org/Problems/prob019/) implementation
 *
 * @details
 *
 * @author [Jxtopher](https://github.com/jxtopher)
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

namespace backtracking {
namespace magic_sequence {
using sequence_t = std::vector<unsigned int>;

void print(const sequence_t& s) {
    for (const auto& item : s) std::cout << item << " ";
    std::cout << std::endl;
}

// Check if it's a magic sequence
bool is_magic(const sequence_t& s) {
    for (unsigned int i = 0; i < s.size(); i++) {
        if (std::count(s.cbegin(), s.cend(), i) != s[i]) {
            return false;
        }
    }
    return true;
}

// Filtering of sub-solutions
// true if the sub-solution is valid otherwise false
bool filtering(const sequence_t& s, unsigned int depth) {
    return std::accumulate(s.cbegin(), s.cbegin() + depth,
                           static_cast<unsigned int>(0)) <= s.size();
}

void solve(sequence_t* s, std::list<sequence_t>* ret, unsigned int depth = 0) {
    if (depth == s->size()) {
        if (is_magic(*s)) {
            ret->push_back(*s);
        }
    } else {
        for (unsigned int i = 0; i < s->size(); i++) {
            (*s)[depth] = i;
            if (filtering(*s, depth + 1)) {
                solve(s, ret, depth + 1);
            }
        }
    }
}

}  // namespace magic_sequence

}  // namespace backtracking

static void test() {
    backtracking::magic_sequence::sequence_t s_magic = {6, 2, 1, 0, 0,
                                                        0, 1, 0, 0, 0};
    assert(backtracking::magic_sequence::is_magic(s_magic));

    backtracking::magic_sequence::sequence_t s_not_magic = {5, 2, 1, 0, 0,
                                                            0, 1, 0, 0, 0};
    assert(!backtracking::magic_sequence::is_magic(s_not_magic));
}

int main() {
    test();

    for (unsigned int i = 2; i < 12; i++) {
        std::cout << "Solution for n = " << i << std::endl;
        std::list<backtracking::magic_sequence::sequence_t> r1;
        backtracking::magic_sequence::sequence_t s1(i, i);
        backtracking::magic_sequence::solve(&s1, &r1);
        for (const auto& item : r1) backtracking::magic_sequence::print(item);
    }
}
