/**
 * @file
 * @brief Length of longest substring without repeating characters
 * @details
 * From an input string, the length of the longest substring, in which the 
 * substring is continuous and has no repeating characters, will be the output.
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * @author [Rafaela Ferreira](https://github.com/rafaela-eacf)
 */
 
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>

/**
 * @brief Function find_longest_substring from a 
 * given string returns the length of the longest 
 * substring without repeating characters
 * @param string s which will be used to find 
 * the longest substring 
 * @returns int value that is equal to the length
 * of the longest substring
 */
int find_longest_substring(std::string s) {
    std::string current_substring = "";
    int max = 0; // length of longest substring
    int count = 0; 
    while(count < s.size())
    {
        if(current_substring.find(s.at(count)) == -1) // if character is not repeated
        {
            current_substring += s.substr(count,1); 
            count++;
        }
        else // if character is repeated
        {
            char tempc = s.at(count);
            int tempi = s.find(tempc);
            s = s.substr(tempi+1);
            count = 0;
            if(max < (int)current_substring.size() )
            {
                max = (int)current_substring.size();
            }
            current_substring = "";
        }
        
    }
    
    if( max < (int)current_substring.size())
    {
        max = (int)current_substring.size();
    }
    
    return max;
} 

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* Test 1: 
    s = "abcabcbb" 
    returns 3 */
    std::cout << "Test 1:\n";
    std::string s = "abcabcbb";
    assert(find_longest_substring(s) == 3); // this ensures that the algorithm works as expected
    std::cout << "String \"abcabcbb\" will return 3.\n";
    
    /* Test 2: 
    s = ""
    returns 0 */
    std::cout << "Test 2:\n";
    s = "";
    assert(find_longest_substring(s) == 0); // this ensures that the algorithm works as expected
    std::cout << "String \"\" will return 0.\n";
    
    /* Test 3: 
    s= " "
    returns 1 */
    std::cout << "Test 3:\n";
    s = " ";
    assert(find_longest_substring(s) == 1); // this ensures that the algorithm works as expected
    std::cout << "String \" \" will return 1.\n";
    
    /* Test 4: 
    s= "ckcr"
    returns 3 */
    std::cout << "Test 4:\n";
    s = "ckcr";
    assert(find_longest_substring(s) == 3); // this ensures that the algorithm works as expected
    std::cout << "String \"ckcr\" will return 3.\n";
    
    /* Test 5: 
    s = "nvskbea"
    returns 7 */
    std::cout << "Test 5:\n";
    s = "nvskbea";
    assert(find_longest_substring(s) == 7); // this ensures that the algorithm works as expected
    std::cout << "String \"nvskbea\" will return 7.\n";
    
    /* Test 6: 
    s = "wwwwww"
    returns 1 */
    std::cout << "Test 6:\n";
    s = "wwwwww";
    assert(find_longest_substring(s) == 1); // this ensures that the algorithm works as expected
    std::cout << "String \"wwwwww\" will return 1.\n";
    
    /* Test 7: 
    s = "rrewasr"
    returns 5 */
    std::cout << "Test 7:\n";
    s = "rrewasr";
    assert(find_longest_substring(s) == 5); // this ensures that the algorithm works as expected
    std::cout << "String \"rrewasr\" will return 5.\n";
    
    /* Test 8: 
    s= "pwwkew"
    returns 3 */
    std::cout << "Test 8:\n";
    s = "pwwkew";
    assert(find_longest_substring(s) == 3); // this ensures that the algorithm works as expected
    std::cout << "String \"pwwkew\" will return 3.\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}