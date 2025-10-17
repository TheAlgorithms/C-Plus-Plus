#include <iostream>
using namespace std;

int main() {
    double velocity, gravity = 9.8, maxHeight;

    cout << "Enter the initial velocity of the ball (m/s): ";
    cin >> velocity;

    maxHeight = (velocity * velocity) / (2 * gravity);

    cout << "The maximum height the ball will reach is: " << maxHeight << " meters." << endl;

    return 0;
}
