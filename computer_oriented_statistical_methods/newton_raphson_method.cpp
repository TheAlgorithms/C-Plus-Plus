#include <cmath>
#include <iostream>

static float eq(float i) {
    return (std::pow(i, 3) - (4 * i) - 9);  // original equation
}

static float eq_der(float i) {
    return ((3 * std::pow(i, 2)) - 4);  // derivative of equation
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
    c = (a + b) / 2;

    for (int i = 0; i < 100; i++) {
        float h;
        m = eq(c);
        n = eq_der(c);

        z = c - (m / n);
        c = z;

        if (m > 0 && m < 0.009)  // stoping criteria
            break;
    }

    std::cout << "\n\nRoot: " << z << std::endl;
    return 0;
}
