#include <iostream>
using namespace std;

int main() {
    int a = 0;
    cout << "Enter a range to generate even numbers : ";
    cin >> a;
    for (int i = 1; i <= 2 * a; i++) {
        if (i % 2 == 0)
            cout << i << " ";
    }
    cout << endl;

    return 0;
}
