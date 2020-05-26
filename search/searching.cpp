#include <cstdlib>
#include <iostream>
#include <string>

char paragraph;

int main() {
    std::string paragraph;
    std::cout << "Please enter your paragraph: \n";
    std::getline(std::cin, paragraph);
    std::cout << "\nHello, your paragraph is:\n " << paragraph << "!\n";
    std::cout << "\nThe size of your paragraph = " << paragraph.size()
              << " characters. \n\n";

    if (paragraph.empty()) {
        std::cout << "\nThe paragraph is empty" << std::endl;
    } else {
        while (true) {
            std::string word;
            std::cout << "Please enter the word you are searching for: ";
            std::getline(std::cin, word);
            std::cout << "Hello, your word is " << word << "!\n";
            if (paragraph.find(word) == std::string::npos) {
                std::cout << word << " does not exist in the sentence"
                          << std::endl;
            } else {
                std::cout << "The word " << word << " is now found at location "
                          << paragraph.find(word) << std::endl
                          << std::endl;
            }
            system("pause");
        }
    }
}
