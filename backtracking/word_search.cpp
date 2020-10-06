/**
 * @file
 * @brief Program to find if a word exists in a grid
 *
 * @details
 * A grid that contains characters and a string is provided.
 * The code will check if the string can be constructed
 * from letters of sequentially adjacent cell. "adjacent" cells are those
 * horizontally or vertically neighboring.
 *
 * @author [Anjali Jha](https://github.com/anjali1903)
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * Function that checks if the string is present in grid
 * using backtracking
 */
bool check(std::vector<std::vector<char>>& board, std::string& word, int r,
           int c, int index) {
    bool flag = false;
    if (index == word.size() - 1) {
        return true;
    }
    board[r][c] = '*';
    if (!flag and r + 1 < board.size() and word[index + 1] == board[r + 1][c])
        flag = check(board, word, r + 1, c, index + 1);

    if (!flag and r - 1 >= 0 and word[index + 1] == board[r - 1][c])
        flag = check(board, word, r - 1, c, index + 1);

    if (!flag and c + 1 < board[0].size() and
        word[index + 1] == board[r][c + 1])
        flag = check(board, word, r, c + 1, index + 1);

    if (!flag and c - 1 >= 0 and word[index + 1] == board[r][c - 1])
        flag = check(board, word, r, c - 1, index + 1);

    board[r][c] = word[index];
    return flag;
}

bool exist(std::vector<std::vector<char>>& board, std::string word) {
    bool flag = false;
    int r, c;
    for (r = 0; r < board.size(); r++) {
        for (c = 0; c < board[0].size(); c++) {
            if (word[0] == board[r][c])
                flag = check(board, word, r, c, 0);
            if (flag)
                return true;
        }
    }
    return false;
}

/** Test function */
void test() {
    std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

    // exist(board, "ECCS") return true
    assert(exist(board, "ECCS") == true);
    // exist(board, "ABCB") return false
    assert(exist(board, "ABCB") == false);
    // exist(board,"ABFDEE") return true
    assert(exist(board, "ABFDEE") == true);
}

/**
 * Main Function
 */
int main() {
    test();  // execute the tests
    return 0;
}
