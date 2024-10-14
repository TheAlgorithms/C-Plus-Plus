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