#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
/**
    * This function plays the guessing game.
    * The function generates a random number between 1 and max_number.
    * The user is asked to guess the number.
    * The user is given feedback if the guess is too high or too low.
    * The user is informed of the number of attempts it took to guess the number.
    * @param max_number The maximum number that can be generated.
 */
void play_game(int max_number) {
    srand(time(0));
    int secret_number = rand() % max_number + 1;
    int guess;
    int attempts = 0;

    cout << "I have selected a number between 1 and " << max_number << ". Can you guess it?" << endl;

    while (true) {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;

        if (guess < secret_number) {
            cout << "Too low! Try again." << endl;
        } else if (guess > secret_number) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << "Congratulations! You've guessed the correct number in " << attempts << " attempts." << endl;
            break;
        }
    }
}

/**
    * The main function asks the user to choose a difficulty level.
    * The user can choose between Easy (1-50), Medium (1-100), and Hard (1-500).
    * The user can play the game multiple times.
    * The user is asked if they want to play again.
    * The game continues until the user chooses to stop playing.
 */
int main() {
    char choice;
    int difficulty_choice;
    int max_number;

    do {
        cout << "Choose a difficulty level:" << endl;
        cout << "1. Easy (1-50)" << endl;
        cout << "2. Medium (1-100)" << endl;
        cout << "3. Hard (1-500)" << endl;
        cout << "Enter your choice: ";
        cin >> difficulty_choice;

        switch (difficulty_choice) {
            case 1:
                max_number = 50;
                break;
            case 2:
                max_number = 100;
                break;
            case 3:
                max_number = 500;
                break;
            default:
                cout << "Invalid choice, setting to Medium (1-100)" << endl;
                max_number = 100;
        }

        play_game(max_number);

        cout << "Do you want to play again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Thank you for playing!" << endl;
    return 0;
}