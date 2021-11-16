/**
 * @file
 * @brief The finite automata to find the occurrences
 * of a pattern within a piece of text with time
 * complexity O(n)
 * @details
 * 1. The finite automata for a string is an algorithm
 * which will examine the characters in the given text
 * only once
 * 2. The finite automation starts with a initial state
 * q0 and then it reads the characters of its string one
 * at a time. When the automation reaches the next state
 * q and reads the character a, then it moves from state
 * q to state δ (q, a), now the machine has accepted string
 * so far.If any input is not allowed the it is rejected
 * @author [Name](https://github.com/SETURAJ)
 */
#include <cassert>   //For assert
#include <cstring>   //For string
#include <iostream>  //For IO operations
#include <vector>    //For std::vector

using namespace std;

/**
 * @brief  We start from first character
 * and at every step, consider next character of the
 * text and check its state in the built Finite
 * Automata
 */

int getNext(string pattern, char currentChar, int currentState) {
    if (currentState < pattern.length() && pattern[currentState] == currentChar)
        return currentState + 1;

    for (int i = currentState; i > 0; i--) {
        if (pattern[i - 1] == currentChar) {
            int j = 0;
            while (j < i - 1) {
                if (pattern[j] != pattern[currentState - i + 1 + j])
                    break;
                j++;
            }
            if (j == i - 1)
                return i;
        }
    }

    return 0;
}

/**
 * @brief The 2D table is built which represents
 * a Finite Automate which is the most important
 * part of the algorithm
 */

vector<vector<int>> create_table(string pattern) {
    vector<vector<int>> table(pattern.length() + 1, vector<int>(256, 0));

    for (int i = 0; i < pattern.length() + 1; i++) {
        for (int j = 0; j < 256; j++) {
            table[i][j] = getNext(pattern, j, i);
        }
    }

    return table;
}

/**
 * @brief The states are checked with the
 * Finite Automata table and the final output
 * is given
 */

void search(string pattern, string txt) {
    int pattLen = pattern.length();
    int txtLen = txt.length();
    int found = 0;
    vector<vector<int>> table = create_table(pattern);

    for (int i = 0, state = 0; i < txtLen; i++) {
        state = table[state][txt[i]];
        if (state == pattLen) {
            printf("\n Pattern found at index %d\n", i - pattLen + 1);
            found++;
        }
    }

    if (!found)
        std::cout << "Text does not contain Pattern";
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    string pattern, text;

    getline(cin, text);
    getline(cin, pattern);

    search(pattern, text);
    return 0;
}
