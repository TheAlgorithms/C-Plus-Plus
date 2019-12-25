#include <iostream>
#include <cstdint>

/*
    Program that computes a^b in O(logN) time.
    It is based on formula that:
        case1) if b is even: a^b = a^(b/2) * a^(b/2) = (a^(b/2))ˆ2
        case2) if b is odd: a^b = a^((b-1)/2) * a^((b-1)/2) * a = (a^((b-1)/2))^2 * a
    We can compute a^b recursively using above algorithm.
*/

using namespace std;

int64_t fast_power_recursive(int64_t a, int64_t b) {
    if (b == 0) return 1;
    int64_t bottom = fast_power_recursive(a, b >> 1);
    // Since it is integer division b/2 = (b-1)/2 where b is odd.
    // Therefore, case2 is easily solved by integer division.

    int64_t result;
    if ((b & 1) == 0)  // case1
        result = bottom * bottom;
    else  // case2
        result = bottom * bottom * a;
    return result;
}

/*
    Same algorithm with little different formula.
    It still calculates in O(logN)
*/
int64_t fast_power_linear(int64_t a, int64_t b) {
    int64_t result = 1;
    while (b) {
        if (b & 1) result = result * a;
        a = a * a;
        b = b >> 1;
    }
    return result;
}

int main() {

    ios_base::sync_with_stdio(false);

    int64_t a, b;
    cin >> a >> b;

    cout << "a^b is = " << fast_power_recursive(a, b) << endl;
    cout << "a^b is = " << fast_power_linear(a, b) << endl;


    return 0;
}
