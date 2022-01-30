#include <iostream>
#include <vector>
using namespace std;

//Determines the number of possibilities to get a dice sum given number of dice and faces.
int diceRoll (int x, int y, int z) {
    vector <int> vect(z + 1);
    vect[0] = 1;
    for (int i = 1; i <= x; i++) {
        vector <int> vectTemp(z + 1);
        for (int j = 1; j <= y; j++) {
            for (int k = j; k <= z; k++) {
                vectTemp[k] += vect[k - j];
            }
        }
        swap(vect, vectTemp);
    }
    return vect[z];
}

int main () {
    cout << "Dice faces: " << endl;
    int diceFaces = 0;
    cin >> diceFaces;

    cout << "Number of dice: " << endl;
    int numDice = 0;
    cin >> numDice;

    cout << "Dice sum: " << endl;
    int diceSum = 0;
    cin >> diceSum;

    cout << "Number of ways to get sum of " << diceSum << ": " << diceRoll(diceFaces, numDice, diceSum) << endl;
}