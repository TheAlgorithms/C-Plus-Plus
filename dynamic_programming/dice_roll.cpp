#include <iostream>
#include <vector>

//Determines the number of possibilities to get a dice sum given number of dice and faces.
int diceRoll (int x, int y, int z) {
    std::vector <int> vect(z + 1);
    vect[0] = 1;
    for (int i = 1; i <= x; i++) {
        std::vector <int> vectTemp(z + 1);
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
    std::cout << "Dice faces: " << std::endl;
    int diceFaces = 0;
    std::cin >> diceFaces;

    std::cout << "Number of dice: " << std::endl;
    int numDice = 0;
    std::cin >> numDice;

    std::cout << "Dice sum: " << std::endl;
    int diceSum = 0;
    std::cin >> diceSum;

    std::cout << "Number of ways to get sum of " << diceSum << ": " << diceRoll(diceFaces, numDice, diceSum) << std::endl;
}