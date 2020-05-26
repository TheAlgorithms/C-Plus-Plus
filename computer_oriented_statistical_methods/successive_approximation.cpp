
#include <cmath>
#include <iostream>

float eq(float y) { return ((3 * y) - (cos(y)) - 2); }
float eqd(float y) { return ((0.5) * ((cos(y)) + 2)); }

int main() {
    float y, x1, x2, x3, sum, s, a, f1, f2, gd;
    int i, n;

    for (i = 0; i < 10; i++) {
        sum = eq(y);
        std::cout << "value of equation at " << i << " " << sum << "\n";
        y++;
    }
    std::cout << "enter the x1->";
    std::cin >> x1;
    std::cout << "enter the no iteration to perform->\n";
    std::cin >> n;

    for (i = 0; i <= n; i++) {
        x2 = eqd(x1);
        std::cout << "\nenter the x2->" << x2;
        x1 = x2;
    }
    return 0;
}
