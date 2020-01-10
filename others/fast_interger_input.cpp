// Read integers in the fastest way in c plus plus
#include<iostream>
void fastinput(int *number) {
// variable to indicate sign of input integer
    bool negative = false;
    register int c;
    *number = 0;

    // extract current character from buffer
    c = std::getchar();
    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = std::getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = std::getchar())
        *number = *number *10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        *(number) *= -1;
}

// Function Call
int main() {
    int number;
    fastinput(&number);
    std::cout << number << "\n";
    return 0;
}
