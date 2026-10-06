/**
 * @file
 * @brief Implementation of the [Smith-Waterman
 * algorithm](https://en.wikipedia.org/wiki/Smith%E2%80%93Waterman_algorithm)
 * for local sequence alignment
 *
 * @details
 * The Smith-Waterman algorithm is a dynamic programming algorithm for
 * determining similar regions between two sequences (nucleotide or protein
 * sequences). It performs local sequence alignment, which identifies the best
 * matching subsequence rather than aligning entire sequences.
 *
 * The algorithm works by:
 * 1. Creating a scoring matrix where each cell represents the maximum
 *    alignment score ending at that position
 * 2. Using match, mismatch, and gap penalties to calculate scores
 * 3. Allowing scores to reset to 0 (ensuring local rather than global
 *    alignment)
 * 4. Tracing back from the highest scoring position to reconstruct the
 *    alignment
 *
 * ### Algorithm
 * Given two sequences S1 and S2 of lengths m and n:
 * - Initialize a (m+1) × (n+1) matrix H with H[i][0] = H[0][j] = 0
 * - For each cell H[i][j]:
 *   - H[i][j] = max(0, H[i-1][j-1] + match/mismatch_score,
 *                   H[i-1][j] + gap_penalty, H[i][j-1] + gap_penalty)
 * - Find the maximum value in H matrix
 * - Traceback from maximum value to cell with value 0
 *
 * Time Complexity: O(m × n) where m and n are the lengths of the sequences
 * Space Complexity: O(m × n) for the scoring matrix
 *
 * @author [Ali Alimohammadi](https://github.com/AliAlimohammadi)
 */

#include <algorithm>  /// for std::max
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <string>     /// for std::string
#include <utility>    /// for std::pair
#include <vector>     /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace smith_waterman
 * @brief Functions for the Smith-Waterman algorithm
 */
namespace smith_waterman {

/**
 * @enum Direction
 * @brief Direction indicators for traceback in the scoring matrix
 */
enum Direction {
    NONE = 0,      ///< No direction (score is 0)
    DIAGONAL = 1,  ///< Match or mismatch
    UP = 2,        ///< Gap in subject sequence
    LEFT = 3       ///< Gap in query sequence
};

/**
 * @brief Calculate the score for a character pair
 * 
 * @param a First character
 * @param b Second character
 * @param match_score Score for matching characters (typically positive)
 * @param mismatch_score Score for mismatching characters (typically negative)
 * @return int The calculated score
 */
int score_function(char a, char b, int match_score, int mismatch_score) {
    return (a == b) ? match_score : mismatch_score;
}

/**
 * @brief Compute the Smith-Waterman scoring matrix
 * @details
 * The Smith-Waterman algorithm uses dynamic programming to find the optimal
 * local alignment. The recurrence relation is:
 * 
 * H(i,j) = max {
 *     H(i-1,j-1) + s(a_i, b_j),  // diagonal: match/mismatch
 *     H(i-1,j) + gap_score,      // up: gap in subject
 *     H(i,j-1) + gap_score,      // left: gap in query
 *     0                          // start new alignment
 * }
 * 
 * Additionally stores direction information for efficient traceback.
 * When multiple paths have equal scores, the algorithm prioritizes diagonal
 * moves, then up, then left.
 * 
 * @param query First sequence
 * @param subject Second sequence
 * @param match_score Score for matching characters (default: 2)
 * @param mismatch_score Penalty for mismatching characters (default: -1)
 * @param gap_score Penalty for gaps (default: -1)
 * @return std::pair of scoring matrix and direction matrix
 */
std::pair<std::vector<std::vector<int>>, std::vector<std::vector<Direction>>>
smith_waterman(const std::string &query, const std::string &subject,
               int match_score = 2, int mismatch_score = -1,
               int gap_score = -1) {
    size_t m = query.length();
    size_t n = subject.length();

    // Initialize scoring matrix with zeros
    std::vector<std::vector<int>> score(m + 1, std::vector<int>(n + 1, 0));
    
    // Initialize direction matrix for traceback
    std::vector<std::vector<Direction>> direction(m + 1, 
                                                   std::vector<Direction>(n + 1, NONE));

    // Fill matrices using dynamic programming
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            // Calculate scores from three possible sources
            int match_mismatch = score[i - 1][j - 1] + 
                score_function(query[i - 1], subject[j - 1], 
                              match_score, mismatch_score);
            int gap_subject = score[i - 1][j] + gap_score;
            int gap_query = score[i][j - 1] + gap_score;

            // Take maximum of all options, including 0 (local alignment)
            int max_score = std::max({match_mismatch, gap_subject, gap_query, 0});
            score[i][j] = max_score;

            // Store direction for traceback
            if (max_score == 0) {
                direction[i][j] = NONE;
            } else if (max_score == match_mismatch) {
                direction[i][j] = DIAGONAL;
            } else if (max_score == gap_subject) {
                direction[i][j] = UP;
            } else {
                direction[i][j] = LEFT;
            }
        }
    }

    return {score, direction};
}

/**
 * @brief Perform traceback to reconstruct the optimal local alignment
 * @details
 * Starting from the cell with maximum score, follows the direction matrix
 * backwards until reaching a cell with score 0, reconstructing the alignment.
 * Gaps introduced during the alignment are represented by the dash ('-') character
 * in the returned aligned sequences.
 * 
 * @param score The scoring matrix from smith_waterman()
 * @param direction The direction matrix from smith_waterman()
 * @param query First sequence
 * @param subject Second sequence
 * @return std::pair<std::string, std::string> The aligned sequences, where gaps
 * are represented by '-' characters
 */
std::pair<std::string, std::string>
traceback(const std::vector<std::vector<int>> &score,
          const std::vector<std::vector<Direction>> &direction,
          const std::string &query, const std::string &subject) {
    // Find the cell with maximum score
    int max_value = 0;
    size_t i_max = 0;
    size_t j_max = 0;

    for (size_t i = 0; i < score.size(); ++i) {
        for (size_t j = 0; j < score[i].size(); ++j) {
            if (score[i][j] > max_value) {
                max_value = score[i][j];
                i_max = i;
                j_max = j;
            }
        }
    }

    // If no significant alignment found, return empty strings
    if (max_value == 0) {
        return {"", ""};
    }

    // Traceback from maximum score position
    // Build alignment strings efficiently using vectors
    std::vector<char> align1_vec;
    std::vector<char> align2_vec;
    size_t i = i_max;
    size_t j = j_max;

    // Follow direction matrix until we hit NONE (score of 0)
    while (i > 0 && j > 0 && direction[i][j] != NONE) {
        switch (direction[i][j]) {
            case DIAGONAL:
                // Match or mismatch
                align1_vec.push_back(query[i - 1]);
                align2_vec.push_back(subject[j - 1]);
                --i;
                --j;
                break;
            case UP:
                // Gap in subject
                align1_vec.push_back(query[i - 1]);
                align2_vec.push_back('-');
                --i;
                break;
            case LEFT:
                // Gap in query
                align1_vec.push_back('-');
                align2_vec.push_back(subject[j - 1]);
                --j;
                break;
            default:
                break;
        }
    }

    // Reverse vectors and construct strings
    std::reverse(align1_vec.begin(), align1_vec.end());
    std::reverse(align2_vec.begin(), align2_vec.end());
    
    return {std::string(align1_vec.begin(), align1_vec.end()),
            std::string(align2_vec.begin(), align2_vec.end())};
}

}  // namespace smith_waterman
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using dynamic_programming::smith_waterman::smith_waterman;
    using dynamic_programming::smith_waterman::traceback;

    // Test 1: Simple exact match
    auto [score1, dir1] = smith_waterman("AGCT", "AGCT");
    auto result1 = traceback(score1, dir1, "AGCT", "AGCT");
    assert(result1.first == "AGCT");
    assert(result1.second == "AGCT");
    std::cout << "Test 1 passed: Simple exact match\n";

    // Test 2: Partial match
    auto [score2, dir2] = smith_waterman("AGCT", "AGT");
    auto result2 = traceback(score2, dir2, "AGCT", "AGT");
    assert(!result2.first.empty());
    assert(!result2.second.empty());
    std::cout << "Test 2 passed: Partial match\n";

    // Test 3: Different sequences with common subsequence
    auto [score3, dir3] = smith_waterman("ACACACTA", "AGCACACA");
    auto result3 = traceback(score3, dir3, "ACACACTA", "AGCACACA");
    assert(!result3.first.empty());
    assert(!result3.second.empty());
    std::cout << "Test 3 passed: Common subsequence alignment\n";

    // Test 4: No match scenario
    auto [score4, dir4] = smith_waterman("AAAA", "TTTT");
    auto result4 = traceback(score4, dir4, "AAAA", "TTTT");
    assert(result4.first.empty());
    assert(result4.second.empty());
    std::cout << "Test 4 passed: No match scenario\n";

    // Test 5: Empty string handling
    auto [score5, dir5] = smith_waterman("", "AGCT");
    auto result5 = traceback(score5, dir5, "", "AGCT");
    assert(result5.first.empty());
    assert(result5.second.empty());
    std::cout << "Test 5 passed: Empty string handling\n";

    // Test 6: Longer sequences with multiple gaps
    auto [score6, dir6] = smith_waterman("GCATGCT", "GATTACA");
    auto result6 = traceback(score6, dir6, "GCATGCT", "GATTACA");
    assert(!result6.first.empty());
    assert(!result6.second.empty());
    assert(result6.first.length() == result6.second.length());
    std::cout << "Test 6 passed: Longer sequences with gaps\n";

    // Test 7: Custom scoring parameters
    auto [score7, dir7] = smith_waterman("AGCT", "AGCT", 3, -2, -2);
    auto result7 = traceback(score7, dir7, "AGCT", "AGCT");
    assert(result7.first == "AGCT");
    assert(result7.second == "AGCT");
    std::cout << "Test 7 passed: Custom scoring parameters\n";

    // Test 8: Case sensitivity
    auto [score8, dir8] = smith_waterman("agct", "AGCT");
    auto result8 = traceback(score8, dir8, "agct", "AGCT");
    assert(result8.first.empty());
    assert(result8.second.empty());
    std::cout << "Test 8 passed: Case sensitivity\n";

    std::cout << "\nAll tests passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    std::cout << "Smith-Waterman Algorithm for Local Sequence Alignment\n";
    std::cout << "======================================================\n\n";

    // Example usage
    std::string query = "GCATGCT";
    std::string subject = "GATTACA";

    std::cout << "Query:   " << query << "\n";
    std::cout << "Subject: " << subject << "\n\n";

    auto [score_matrix, direction_matrix] = 
        dynamic_programming::smith_waterman::smith_waterman(query, subject);
    auto alignment = 
        dynamic_programming::smith_waterman::traceback(score_matrix, 
                                                       direction_matrix,
                                                       query, subject);

    std::cout << "Optimal Local Alignment:\n";
    std::cout << "Query:   " << alignment.first << "\n";
    std::cout << "Subject: " << alignment.second << "\n\n";

    // Run tests
    std::cout << "Running tests...\n";
    std::cout << "================\n";
    test();

    return 0;
}
