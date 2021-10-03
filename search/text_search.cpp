/**
 * \file
 * \brief Search for words in a long textual paragraph.
 */
#include <cstdlib>
#include <iostream>
#ifdef _MSC_VER
#include <string>  // required for MS Visual C++
#else
#include <cstring>
#endif

/** Main function
 */

std::string lower(std::string word) {
    int length = word.length();
    std::string lc = "";

    for (int i = 0; i < length; i++) {
        lc += tolower(word[i]);
    }

    return lc;
}

int main() {
    std::string paragraph;
    std::cout << "Please enter your paragraph: \n";
    getline(std::cin, paragraph);
    std::cout << "\nHello, your paragraph is:\n " << paragraph << "!\n";
    std::cout << "\nThe size of your paragraph = " << paragraph.size()
              << " characters. \n\n";

    if (paragraph.empty()) {
        std::cout << "\nThe paragraph is empty" << std::endl;
    } else {
        int ch = 0;
        while (true) {
            std::string word;
            std::cout << "Please enter the word you are searching for: ";
            getline(std::cin, word);
            std::cout << "Ignore case? 1 = Yes, 0 = No" << std::endl;
            std::cin >> ch;
            if (ch == 1) {
                std::string lowerCase = lower(paragraph);
                std::string lowerCaseWord = lower(word);

                std::cout << "Hello, your word is " << word << "!\n";
                if (lowerCase.find(lowerCaseWord) == std::string::npos) {
                    std::cout << word << " does not exist in the sentence"
                              << std::endl;
                } else {
                    std::cout << "The word " << word
                              << " is now found at location "
                              << lowerCase.find(lowerCaseWord) << std::endl
                              << std::endl;
                }
            } else {
                std::cout << "Hello, your word is " << word << "!\n";
                if (paragraph.find(word) == std::string::npos) {
                    std::cout << word << " does not exist in the sentence"
                              << std::endl;
                } else {
                    std::cout << "The word " << word
                              << " is now found at location "
                              << paragraph.find(word) << std::endl
                              << std::endl;
                }
            }
            std::cin.get();
        }
    }

    return 0;
}
