#include <cmath>
#include <iostream>

static float eq(float i) {
    return (std::pow(i, 3) - (4 * i) - 9);  // original equation
}

int main() {
    float a, b, x, z;

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
        x = (a + b) / 2;
        z = eq(x);
        std::cout << "\n\nz: " << z << "\t[" << a << " , " << b
                  << " | Bisect: " << x << "]";

        if (z < 0) {
            a = x;
        } else {
            b = x;
        }

        if (z > 0 && z < 0.0009)  // stoping criteria
            break;
    }

    std::cout << "\n\nRoot: " << x;
    return 0;
}
