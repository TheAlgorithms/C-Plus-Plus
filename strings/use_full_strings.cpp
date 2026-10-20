/**
 * @file
 * @brief Replace whole words in a string
 * @details Splits the text on spaces, replaces matching words
 * (case-sensitive or not), then joins the words back together.
 * @author [Yazan Brijawe](https://github.com/YazanBrijawe)
 */

#include <cassert>  /// for assert
#include <cctype>   /// for std::tolower
#include <iostream> /// for IO operations
#include <string>   /// for std::string
#include <vector>   /// for std::vector

/**
 * @namespace strings
 * @brief String algorithms
 */
namespace strings
{
    /**
     * @namespace usefullstrings
     * @brief Helper functions for working with words in a string
     */
    namespace usefullstrings
    {

        /**
         * @brief Converts a string to lowercase
         * @param S1 the input string (copied)
         * @returns the lowercase version of S1
         */
        std::string LowerAllString(std::string S1)
        {
            for (std::size_t i = 0; i < S1.length(); i++)
            {
                S1[i] = std::tolower(static_cast<unsigned char>(S1[i]));
            }
            return S1;
        }

        /**
         * @brief Splits a string into words on a delimiter
         * @details Empty parts are dropped, so repeated delimiters collapse.
         * @param S1 the input string (copied)
         * @param Delim the delimiter to split on (copied)
         * @returns the list of non-empty parts
         */
        std::vector<std::string> Split(std::string S1, std::string Delim)
        {
            std::vector<std::string> vString;
            std::size_t pos = 0;
            std::string sWord;
            while ((pos = S1.find(Delim)) != std::string::npos)
            {
                sWord = S1.substr(0, pos);
                if (sWord != "")
                {
                    vString.push_back(sWord);
                }
                S1.erase(0, pos + Delim.length());
            }
            if (S1 != "")
            {
                vString.push_back(S1);
            }
            return vString;
        }

        /**
         * @brief Joins strings into one, with a delimiter between them
         * @param vString the strings to join (copied)
         * @param Delim the delimiter placed between strings (copied)
         * @returns the joined string
         */
        std::string JoinString(std::vector<std::string> vString, std::string Delim)
        {
            std::string S1 = "";
            for (std::string &s : vString)
            {
                S1 = S1 + s + Delim;
            }
            return S1.substr(0, S1.length() - Delim.length());
        }

        /**
         * @brief Replaces every whole-word occurrence of a word
         * @param S1 the input text (copied)
         * @param WordToReplace the word to find
         * @param ReplaceTo the word to put in its place
         * @param MatchCase true for case-sensitive matching (default: true)
         * @returns the text after replacement
         */
        std::string ReplaceWord(std::string S1, std::string WordToReplace,
                                std::string ReplaceTo, bool MatchCase = true)
        {
            std::vector<std::string> vString = Split(S1, " ");
            for (std::string &s : vString)
            {
                if (MatchCase)
                {
                    if (s == WordToReplace)
                    {
                        s = ReplaceTo;
                    }
                }
                else
                {
                    if (LowerAllString(s) == LowerAllString(WordToReplace))
                    {
                        s = ReplaceTo;
                    }
                }
            }
            return JoinString(vString, " ");
        }

    } // namespace usefullstrings
} // namespace strings

/**
 * @brief Tests LowerAllString
 * @returns void
 */
static void test_lower()
{
    using strings::usefullstrings::LowerAllString;

    assert(LowerAllString("HeLLo") == "hello");     // mixed case
    assert(LowerAllString("") == "");               // empty string
    assert(LowerAllString("abc123!") == "abc123!"); // nothing to change
}

/**
 * @brief Tests Split
 * @returns void
 */
static void test_split()
{
    using strings::usefullstrings::Split;

    // double parentheses are needed because of the commas inside { }
    assert((Split("a b c", " ") == std::vector<std::string>{"a", "b", "c"}));
    assert((Split("a,b,c", ",") == std::vector<std::string>{"a", "b", "c"}));
    assert((Split("a  b", " ") == std::vector<std::string>{"a", "b"})); // empty part dropped
    assert((Split("", " ") == std::vector<std::string>{}));             // empty string
}

/**
 * @brief Tests JoinString
 * @returns void
 */
static void test_join()
{
    using strings::usefullstrings::JoinString;

    assert((JoinString(std::vector<std::string>{"a", "b", "c"}, "-") == "a-b-c"));
    assert((JoinString(std::vector<std::string>{"only"}, "-") == "only")); // one item
    assert((JoinString(std::vector<std::string>{}, "-") == ""));           // empty vector
}

/**
 * @brief Tests ReplaceWord
 * @returns void
 */
static void test_replace()
{
    using strings::usefullstrings::ReplaceWord;

    assert(ReplaceWord("I love cats", "cats", "dogs") == "I love dogs");
    assert(ReplaceWord("Hello hello", "hello", "hi") == "Hello hi");     // case-sensitive
    assert(ReplaceWord("Hello hello", "hello", "hi", false) == "hi hi"); // ignore case
    assert(ReplaceWord("cat category", "cat", "dog") == "dog category"); // whole words only
    assert(ReplaceWord("nothing here", "xyz", "abc") == "nothing here"); // no match
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test_lower();
    test_split();
    test_join();
    test_replace();
    std::cout << "All tests have successfully passed!\n";
    return 0;
}