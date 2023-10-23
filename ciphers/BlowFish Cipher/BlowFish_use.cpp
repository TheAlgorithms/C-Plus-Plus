#include <string.h>

#include <iostream>

#include "blowfish.h"
using namespace std;
typedef unsigned char byte;
int main() {
    BLOWFISH bf("FEDCBA9876543210");
    string asdf = "BlowwFIshhhhhhhhhhh!";
    asdf = bf.Encrypt_CBC(asdf);
    cout << "Encrypted: " << asdf << endl;
    asdf = bf.Decrypt_CBC(asdf);
    cout << "Decrypted: " << asdf;
    return 0;
}