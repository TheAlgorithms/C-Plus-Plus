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
using namespace std;

string lower(string word) {
    int length = word.length();
    string lc = "";

    for (int i = 0; i < length; i++) {
        lc += tolower(word[i]);
    }

    return lc;
}

int main() {
    string paragraph;
    cout << "Please enter your paragraph: \n";
    getline(cin, paragraph);
    cout << "\nHello, your paragraph is:\n " << paragraph << "!\n";
    cout << "\nThe size of your paragraph = " << paragraph.size()
         << " characters. \n\n";

    if (paragraph.empty()) {
        cout << "\nThe paragraph is empty" << endl;
    } else {
        int ch;
        while (true) {
            string word;
            cout << "Please enter the word you are searching for: ";
            getline(cin, word);
            cout << "Ignore case? 1 = Yes, 0 = No" << endl;
            cin >> ch;
            if (ch == 1) {
                string lowerCase = lower(paragraph);
                string lowerCaseWord = lower(word);

                cout << "Hello, your word is " << word << "!\n";
                if (lowerCase.find(lowerCaseWord) == string::npos) {
                    cout << word << " does not exist in the sentence" << endl;
                } else {
                    cout << "The word " << word << " is now found at location "
                         << lowerCase.find(lowerCaseWord) << endl
                         << endl;
                }
            } else {
                cout << "Hello, your word is " << word << "!\n";
                if (paragraph.find(word) == string::npos) {
                    cout << word << " does not exist in the sentence" << endl;
                } else {
                    cout << "The word " << word << " is now found at location "
                         << paragraph.find(word) << endl
                         << endl;
                }
            }
            cin.get();
        }
    }

    return 0;
}
