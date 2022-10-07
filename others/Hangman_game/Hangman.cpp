#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
using namespace std;
void print_string(char b[], int k, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << b[i];
    }
    cout << "\n";
    cout << "Number of chances = " << k << "\n";
}
int main()
{
    srand(time(0));
    ifstream inFile;
    inFile.open("inputs.txt");
    string a;
    int random = rand() % 56;
    for (int i = 0; i < random; i++)
        getline(inFile, a);
    int len = a.length();
    char b[len];
    for (int i = 0; i < len; i++)
    {
        b[i] = '*';
    }
    char ch;
    cout << "Welcome to hangman game , guess the letters in the string. If you make 5 wrong guesses then you lose.\n";
    cout << "The string to be guessed is\n";
    int k = 5, correct = 0;
    ;
    print_string(b, k, len);
    cout << "The length of the string to be guessed is " << len << endl;
    do
    {
        cout << "Guess a character\n";
        cin >> ch;
        int flag = 0;
        for (int i = 0; i < len; i++)
        {
            if (ch == a[i])
            {
                b[i] = a[i];
                a[i] = -1;
                flag++;
                correct++;
            }
        }
        if (flag > 0)
        {
            cout << "Correct guess\n";
            cout << "Now the string is\n";
            print_string(b, k, len);
        }
        else
        {
            k--;
            cout << "Wrong guess , Try again\n";
            cout << "Now the string is\n";
            print_string(b, k, len);
        }
        if (correct == len)
        {
            cout << "Won the game\n";
            return 0;
        }
        cout << "\n";
    } while (k > 0);
    cout << "You lose , try again\n";
    return 0;
}