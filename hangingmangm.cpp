#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function to choose a random word from a predefined list
string getRandomWord() {
    const vector<string> words = {
        "programming", "hangman", "development", "computer", 
        "software", "algorithm", "function", "variable"
    };
    srand(time(0)); // Seed for random number generation
    return words[rand() % words.size()];
}

// Function to display the current state of the guessed word
void displayWord(const string& word, const set<char>& guessedLetters) {
    for (char letter : word) {
        if (guessedLetters.count(letter)) {
            cout << letter << ' ';
        } else {
            cout << '_';
        }
    }
    cout << endl;
}

// Function to check if the word has been completely guessed
bool isWordGuessed(const string& word, const set<char>& guessedLetters) {
    for (char letter : word) {
        if (!guessedLetters.count(letter)) {
            return false;
        }
    }
    return true;
}

int main() {
    string word = getRandomWord();
    set<char> guessedLetters;
    int attemptsLeft = 6; // Number of allowed incorrect attempts
    char guess;

    cout << "Welcome to Hangman!" << endl;

    while (attemptsLeft > 0) {
        cout << "Current word: ";
        displayWord(word, guessedLetters);
        cout << "Attempts left: " << attemptsLeft << endl;
        cout << "Guessed letters: ";

        for (char letter : guessedLetters) {
            cout << letter << ' ';
        }
        cout << endl;

        cout << "Enter a letter: ";
        cin >> guess;

        // Convert guess to lowercase
        guess = tolower(guess);

        // Check if the letter has already been guessed
        if (guessedLetters.count(guess)) {
            cout << "You already guessed that letter." << endl;
            continue;
        }

        // Add guess to the set of guessed letters
        guessedLetters.insert(guess);

        // Check if the guessed letter is in the word
        if (word.find(guess) == string::npos) {
            attemptsLeft--;
            cout << "Incorrect guess!" << endl;
        }

        // Check if the word has been guessed
        if (isWordGuessed(word, guessedLetters)) {
            cout << "Congratulations! You've guessed the word: " << word << endl;
            break;
        }
    }

    if (attemptsLeft == 0) {
        cout << "You've run out of attempts! The word was: " << word << endl;
    }

    return 0;
}
