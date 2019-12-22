#include<stdlib.h>
#include <math.h>
#include <iostream>
float eq(float i) {
    return (pow(i, 3) - (4 * i) - 9);  // origial equation
}
int main() {
    float a, b, z, c, m, n;
    system("clear");
    for (int i = 0; i < 100; i++) {
        z = eq(i);
        if (z >= 0) {
            b = i;
            a = --i;
            goto START;
            }
        }
    START:
    std::cout << "\nFirst initial: " << a;
    std::cout << "\nSecond initial: " << b;
    for (int i = 0; i < 100; i++) {
        float h, d;
        m = eq(a);
        n = eq(b);
        c = ((a * n) - (b * m)) / (n - m);
        a = c;
        z = eq(c);
        if (z > 0 && z < 0.09) {  // stoping criteria
            goto END;
        }
    }
    END:
    std::cout << "\n\nRoot: " << c;
    system("pause");
}
