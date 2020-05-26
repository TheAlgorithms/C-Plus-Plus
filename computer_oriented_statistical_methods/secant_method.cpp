#include <cmath>
#include <iostream>

static float eq(float i) {
    return (pow(i, 3) - (4 * i) - 9);  // original equation
}

int main() {
    float a, b, z, c, m, n;
    for (int i = 0; i < 100; i++) {
        z = eq(i);
        if (z >= 0) {
            b = i;
            a = --i;
            break;
        }
    }

    std::cout << "\nFirst initial: " << a;
    std::cout << "\nSecond initial: " << b;
    for (int i = 0; i < 100; i++) {
        float h, d;
        m = eq(a);
        n = eq(b);

        c = ((a * n) - (b * m)) / (n - m);
        a = b;
        b = c;

        z = eq(c);
        if (z > 0 && z < 0.09)  // stoping criteria
            break;
    }

    std::cout << "\n\nRoot: " << c;
    return 0;
}
