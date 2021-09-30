/**
 * @file
 * @brief Implementation of [RSA asymmetric cryptography algorithm]
 * (https://en.wikipedia.org/wiki/RSA_(cryptosystem))
 *
 * @details
 * RSA algorithm is asymmetric cryptography algorithm.
 * Asymmetric actually means that it works on two different keys i.e.
 * Public Key and Private Key. As the name describes that the Public Key
 * is given to everyone and Private key is kept private.

   An example of asymmetric cryptography :

   A client (for example browser) sends its public key to the server and
 requests for some data. The server encrypts the data using client’s public key
 and sends the encrypted data. Client receives this data and decrypts it.

 * ### Algorithm
 * The idea! The idea of RSA is based on the fact that it is difficult to
 factorize a large integer.
 *  The public key consists of two numbers where one number is multiplication of
 two large prime numbers.
 *  And private key is also derived from the same two prime numbers.
 * So if somebody can factorize the large number, the private key is
 compromised.
 *  Therefore encryption strength totally lies on the key size and
 *  if we double or triple the key size, the strength of encryption increases
 exponentially.
 * RSA keys can be typically 1024 or 2048 bits long, but experts believe
 * that 1024 bit keys could be broken in the near future. But till now it
 * seems to be an infeasible task.
 * @author [Parveen Jangra](https://github.com/Parveen-jangra)
 */

#include <iostream>
using namespace std;
long int p, q, n, y, e, d, i, j, m, c,
    flag;        // e = public key,    d = private key
char oMsg[100];  // Orignal message
char eMsg[100];  // Encrypted message
char dMsg[100];  // Decrypted message

bool isPrime = true;
bool prime(long int num) {
    for (i = 2; i < (num / 2); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

long int claculateD(long int e) {
    long int k = 1;
    while (1) {
        k = k + y;
        if (k % e == 0) {
            return (k / e);
        }
    }
}

void claculateE() {
    for (int j = 2; j < y; j++) {
        if (y % j == 0)
            continue;
        isPrime = prime(j);
        if (isPrime && j != p && j != q) {
            e = j;
            flag = claculateD(e);

            if (flag > 0) {
                d = flag;
                break;
            }
        }
    }
}

int main() {
    cout << "Input (prime number) p : ";
    cin >> p;
    isPrime = prime(p);
    if (!isPrime) {
        cout << "P is Not Prime\n";
        exit(1);
    }

    cout << "Input (prime number) q : ";
    cin >> q;
    isPrime = prime(q);

    if (!isPrime) {
        cout << "q is Not Prime\n";
        exit(1);
    }
    n = p * q;
    y = (p - 1) * (q - 1);
    claculateE();

    cout << "Input message: ";
    cin >> oMsg;
    cout << "p\tq\tn\ty\tm" << endl;
    cout << p << "\t" << q << "\t" << n << "\t" << y << "\t" << oMsg << "\t"
         << endl;

    cout << "e= " << e << endl;
    cout << "d= " << d << endl;

    int a;
    for (a = 0; oMsg[a] != '\0'; a++) {
        // Encryption Algorithm

        m = oMsg[a];  // convert char to ASCII code
        long int k = 1;
        for (int i = 0; i < e; i++) {
            k = k * m;
            k = k % n;
        }
        c = k;
        eMsg[a] = c;  // convert int into char

        // Decryption Algorithm

        k = 1;
        for (i = 0; i < d; i++) {
            k = k * c;
            k = k % n;
        }
        m = k;

        dMsg[a] = m;  // convert int into char
    }

    eMsg[a] = -1;
    dMsg[a] = -1;

    cout << "\nThe Encrypted Message is ";
    for (i = 0; eMsg[i] != -1; i++) {
        cout << eMsg[i];
    }

    cout << "\nThe Decrypted Message is ";
    for (i = 0; dMsg[i] != -1; i++) {
        cout << dMsg[i];
    }
    cout << endl;

    return 0;
}