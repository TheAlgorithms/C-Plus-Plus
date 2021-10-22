/**
 * @file
 * @brief Implementation of [Railfence
 * Cipher](https://en.wikipedia.org/wiki/Rail_fence_cipher)
 * @details
 * The rail fence cipher (also called a zigzag cipher) is a form of
 * classical transposition cipher. It derives its name from the manner in
 * which encryption is performed. Encryption: In the rail fence cipher, the
 * plaintext is written downwards diagonally on successive "rails" of an
 * imaginary fence, then moving up when the bottom rail is reached, down
 * again when the top rail is reached, and so on until the whole plaintext
 * is written out. The ciphertext is then read off in rows. Decryption: Let
 * N be the number of rails used during encryption. Observe that as the
 * plaintext is written, the sequence of each letter's vertical position on
 * the rails varies up and down in a repeating cycle. In general the
 * sequence repeats with a period of 2(N−1). Let L be the length of the
 * string to be decrypted. Suppose for a moment that L is a multiple of
 * 2(N−1) and let K = L/2(N−1). One begins by splitting the ciphertext into
 * strings such that the length of the first and last string is K and the
 * length of each intermediate string is 2K.
 * @author [Sumaiya Fatma](https://github.com/sumushi)
 */

#include <cassert>     /// for assert
#include <iostream>    /// for IO operations

/**
 * \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
namespace ciphers {

/** \namespace railfence \brief Functions for [Railfence
 * cipher](https://en.wikipedia.org/wiki/Rail_fence_cipher).
 */
namespace railfence {

/**
 * Encrypt given text using railfence cipher.
 * @param text text to be encrypted
 * @param key number of rails to be used
 * @returns new encrypted text
 */
std::string encrypt(const std::string &text, const int &key) {
  int len = text.length();
  /* Empty string stores encrypted */
  std::string encrypted_text = "";
  /* Empty matrix to cipher text into rails */
  char rail[key][len];
  /* Filling the rail matrix to distinguish between filled and
  unfilled cells */
  for (int i = 0; i < key; i++) {
    for (int j = 0; j < len; j++) {
      rail[i][j] = '-';
    }
  }
  /* Using a flag to check whether to move up or down */
  bool down = false;
  /* r is row number and c defines the coloumn number */
  int r = 0, c = 0;
  /* iterating through each character of provided string and
  putting it at the right place in rail matrix */
  for (int i = 0; i < len; i++) {
    /* if at first or last row reverse the direction of filling
    rows */
    if (r == 0 || r == key - 1) {
      down = !down;
    }
    /* Fill in the cell, move a column forward */
    rail[r][c++] = text[i];
    if (down) {
      /* if direction is down, move one row below */
      r++;
    } else {
      /* if direction is up, move one row above */
      r--;
    }
  }
  for (int i = 0; i < key; i++) {
    /* iterating through each element of rail matrix left to
    right */
    for (int j = 0; j < len; j++) {
      if (rail[i][j] != '-') {
        /* If matrix was filled,adding the filled character
        to output */
        encrypted_text += rail[i][j];
      }
    }
  }
  /* Returning encrypted text */
  return encrypted_text;
}
/**
 * Decrypt given text using railfence cipher.
 * @param text text to be decrypted
 * @param key number of rails to be used
 * @returns new decrypted text
 */
std::string decrypt(const std::string &text, const int &key) {
  int len = text.length();
  /* Empty string stores decrypted */
  std::string decrypted_text = "";
  /* Empty matrix ciphers plain text into rails */
  char rail[key][len];
  for (int i = 0; i < key; i++) {
    for (int j = 0; j < len; j++) {
      /* Filling the rail matrix to distinguish between
      filled and unfilled cells */
      rail[i][j] = '-';
    }
  }
  /* Using a flag to check direction */
  bool down = false;
  /* r equal row number and c equals coloumn number */
  int r = 0, c = 0;
  /* iterating through each character of provided string to mark
  the cells to be filled */
  for (int i = 0; i < len; i++) {
    /* if at first or last row */
    if (r == 0 || r == key - 1) {
      /* reverse the direction of filling */
      down = !down;
    }
    /* Mark the cell and move a column forward */
    rail[r][c++] = '*';
    if (down) {
      /* if direction is down, move one row below */
      r++;
    } else {
      /* if direction is up, move one row above */
      r--;
    }
  }
  int n = 0;
  for (int i = 0; i < key; i++) {
    /* iterating through each element of rail matrix left to
    right */
    for (int j = 0; j < len; j++) {
      if (rail[i][j] != '-') {
        /* If matrix cell was marked, filling a character
        from input text */
        rail[i][j] = text[n++];
      }
    }
  }
  /* reset the value of down */
  down = 0;
  /* reset the value of c and r */
  r = 0, c = 0;
  /* Moving through the rail matrix in zig-zag manner using down
  flag and r and c values */
  for (int i = 0; i < len; i++) {
    /* if at first or last row */
    if (r == 0 || r == key - 1) {
      /* reverse the direction of filling */
      down = !down;
    }
    /* Add the char to output */
    decrypted_text += rail[r][c++];
    if (down) {
      /* if direction is down, move one row below */
      r++;
    } else {
      /* if direction is up, move one row above */
      r--;
    }
  }
  /* Returning decrypted text */
  return decrypted_text;
}
} // namespace railfence
} // namespace ciphers

/**
 * Function to test above algorithm
 */
void test() {
  std::cout << "******************Test Cases******************" << std::endl;
  // Test 1
  std::string text1 = "ALANTURING";
  std::string encrypted1 = ciphers::railfence::encrypt(text1, 4);
  std::string decrypted1 = ciphers::railfence::decrypt(encrypted1, 4);
  assert(text1 == decrypted1);
  std::cout << "Original text : " << text1;
  std::cout << "\nEncrypted text (with rails = 4) : " << encrypted1;
  std::cout << "\nDecrypted text : " << decrypted1 << std::endl;
  std::cout << "**********************************************" << std::endl;

  // Test 2
  std::string text2 = "helloworld";
  std::string encrypted2 = ciphers::railfence::encrypt(text2, 3);
  std::string decrypted2 = ciphers::railfence::decrypt(encrypted2, 3);
  assert(text2 == decrypted2);
  std::cout << "Original text : " << text2;
  std::cout << "\nEncrypted text (with rails = 3) : " << encrypted2;
  std::cout << "\nDecrypted text : " << decrypted2 << std::endl;
  std::cout << "**********************************************" << std::endl;
}

/** Driver Code */
int main() {
  // Testing
  test();
  return 0;
}
