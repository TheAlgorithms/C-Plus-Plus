/**
 * @file playfair_cipher.cpp
 * @brief  Implementation of [Playfair
 * Cipher](https://en.wikipedia.org/wiki/Playfair_cipher)
 * @details
 * The Playfair cipher is a manual symmetric encryption technique and was
 * the first literal digram substitution cipher.
 * Encryption Algorithm: The Algorithm consists of 3 steps:
 * Generate the key Square(5×5)
 * Split plain text in diagraphs
 * Convert each diagraph to cipher and combine them
 * Decryption Algorithm: The Algorithm also consists of 3 steps:
 * Generate the key Square(5×5)
 * Split cipher text in diagraphs
 * Convert each diagraph to text and combine them
 * @author [Sumaiya Fatma](https://github.com/sumushi)
 */

#include <cassert>
#include <iostream>

/**
 * \namespace ciphers \brief Algorithms for encryption and decryption
 */
namespace ciphers {

/** \namespace playfair \brief Functions for [Playfair
 * cipher](https://en.wikipedia.org/wiki/Playfair_cipher).
 */
namespace playfair {
/* 5*5 Key matrix containing 25 letters of alphabet used to
encrypt/decrypt given text */
char keyMat[5][5];
/**
 * Form key matrix: a 5*5 matrix containing 25 letters of alphabet
 * @param key key used to encrypt/decrypt cipher which wil be converted to
 * key matrix
 */
void keyMatrix(std::string key) {
  /* Array to store alphatets */
  int a[26];
  /* Initialise array of alphabets with -1, but i and j with 0 as
 they are interchangable */
  for (int i = 0; i < 26; i++) {
    a[i] = -1;
    if (i == 8 || i == 9) {
      a[i] = 0;
    }
  }
  /* s to keep track of current alphabet of input text
  to keep track of current alphabet of english language */
  int s = 0, t = 0;
  /* A string to store key elements in order which will later be
stored in keyMatrix */
  std::string keyString = "";
  while (keyString.length() < 25) {

    char c;
    /* First store all letters given in input text */
    if (s < key.length()) {
      c = key[s];
      s++;
    }
    /* then store remaining letters of english alphabet */
    else {
      c = t + 65;
      t++;
    }
    /* Checking the validity of each character whether it has
been already added or not, if not added flag its index in
alphabet array and then add to keyString */
    if (a[c - 65] == -1) {
      a[c - 65] = 1;
      keyString += c;
    }
    /* Exception Case: if letter is i or j, care has to be
taken as only one of them will be in keyMatrix */
    if (c == 'I' || c == 'J') {
      if (a['I' - 65] == 0) {
        keyString += 'I';
        a['I' - 65] = 1;
        a['J' - 65] = 1;
      }
    }
  }
  /* To keep track of current alphabet of keyString */
  s = 0;
  /* Iterating through key Matrix and Filling it with values from
key String */
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      keyMat[i][j] = keyString[s++];
    }
  }
}
/**
 * Encrypt given text using playfair cipher.
 * @param text diagraph to be encrypted
 * @returns new encrypted diagrapgh
 */
std::string encrypt_diagraph(const std::string &text) {
  /* To store encrypted diagraph */
  std::string res = "";
  /* Getting both char of diagraph */
  char c1 = text[0], c2 = text[1];
  /* Finding row and column for each character */
  int n1r = 0, n2r = 0, n1c = 0, n2c = 0;
  /* Iterating through key Matrix and finding the row and coloumn
for each character of input text diagraph */
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (c1 == keyMat[i][j]) {
        n1r = i;
        n1c = j;
      }
      if (c2 == keyMat[i][j]) {
        n2r = i;
        n2c = j;
      }
    }
  }
  /* If both letters in same coloumn take letter below each one */
  if (n1c == n2c) {
    res += keyMat[(n1r + 1) % 5][n1c];
    res += keyMat[(n2r + 1) % 5][n2c];
  }
  /* If both letter in same row, take letter to right of each one */
  else if (n1r == n2r) {
    res += keyMat[n1r][(n1c + 1) % 5];
    res += keyMat[n2r][(n2c + 1) % 5];
  }
  /* Else take horizontal opposite corner of rectangle formed */
  else {
    res += keyMat[n1r][n2c];
    res += keyMat[n2r][n1c];
  }
  /* Return the encrypted diagraph */
  return res;
}
/**
 * Decrypt given text using playfair cipher.
 * @param text diagraph to be decrypted
 * @returns new decrypted diagraph
 */
std::string decrypt_diagraph(const std::string &text) {
  /* To store decrypted diagraph */
  std::string res = "";
  /* Getting both char of diagraph */
  char c1 = text[0], c2 = text[1];
  /* Finding row and column for each character */
  int n1r = 0, n2r = 0, n1c = 0, n2c = 0;
  /* Iterating through key Matrix and finding the row and coloumn
for each character of input text diagraph */
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (c1 == keyMat[i][j]) {
        n1r = i;
        n1c = j;
      }
      if (c2 == keyMat[i][j]) {
        n2r = i;
        n2c = j;
      }
    }
  }
  /* If both letters in same coloumn take letter above each one */
  if (n1c == n2c) {
    res += keyMat[(n1r - 1) % 5][n1c];
    res += keyMat[(n2r - 1) % 5][n2c];
  }
  /* If both letter in same row, take letter to left of each one */
  else if (n1r == n2r) {
    res += keyMat[n1r][(n1c - 1) % 5];
    res += keyMat[n2r][(n2c - 1) % 5];
  }
  /* Else take horizontal opposite corner of rectangle formed */
  else {
    res += keyMat[n1r][n2c];
    res += keyMat[n2r][n1c];
  }
  /* Return the decrypted diagraph */
  return res;
}
/**
 * Encrypt given text using railfence cipher.
 * @param text text to be encrypted
 * @param key key used to build keyMatrix and encrypt the cipher
 * @returns new encrypted text
 */
std::string encrypt(std::string text, std::string key) {
  /* Form key Matrix using above function */
  keyMatrix(key);
  /* s to keep track of no. of splits made and remaining alphabets */
  int s = 0;
  std::string encrypted_text = "";
  while (s < text.length()) {
    /* Store each diagraph */
    std::string sub = "";
    /* If last diagraph can't be formed as only one letter left
then a bogus letter, here 'Z', is
added to last diagraph */
    if (text.length() - s == 1) {
      sub += text[text.length() - 1];
      sub += 'Z';
      s++;
    } else {
      sub = text.substr(s, 2);
    }
    /* 'J' is replaced by 'I' as 'I' is used in key matrix also */
    if (sub[0] == 'J') {
      sub[0] = 'I';
    }
    if (sub[1] == 'J') {
      sub[1] = 'I';
    }
    /* If both letters of diagrah are same, then second one is replaced by
'X' and then used to make another diagraph. Eg: ool, here oo is common
so diagraph will be 'ox', then 'ol' instead of 'oo' and 'lz' */
    if (sub[0] == sub[1]) {
      sub = sub[0];
      sub += 'X';
      encrypted_text += encrypt_diagraph(sub);
      s++;
    } else {
      encrypted_text += encrypt_diagraph(sub);
      s += 2;
    }
  }
  /* Return encrypted cipher */
  return encrypted_text;
}
/**
 * Decrypt given text using playfair cipher.
 * @param text text to be decrypted
 * @param key key used to build keyMatrix and decrypt the cipher
 * @returns new decrypted text
 */
std::string decrypt(std::string text, std::string key) {
  /* Form key Matrix using above function */
  keyMatrix(key);
  /* s to keep track of no. of splits made and remaining alphabets */
  int s = 0;
  std::string decrypted_text = "";
  while (s < text.length()) {
    /* Store each diagraph */
    std::string sub = "";
    /* If last diagraph can't be formed as only one letter left
then a bogus letter, here 'Z', is
added to last diagraph */
    if (text.length() - s == 1) {
      sub += text[text.length() - 1];
      sub += 'Z';
      s++;
    } else {
      sub = text.substr(s, 2);
    }
    /* 'J' is replaced by 'I' as 'I' is used in key matrix also */
    if (sub[0] == 'J') {
      sub[0] = 'I';
    }
    if (sub[1] == 'J') {
      sub[1] = 'I';
    }
    /* If both letters of diagrah are same, then second one is replaced by
'X' and then used to make another diagraph. Eg: ool, here oo is common
so diagraph will be 'ox', then 'ol' instead of 'oo' and 'lz' */
    if (sub[0] == sub[1]) {
      sub = sub[0];
      sub += 'X';
      decrypted_text += decrypt_diagraph(sub);
      s++;
    } else {
      decrypted_text += decrypt_diagraph(sub);
      s += 2;
    }
  }
  /* Return decrypted text */
  return decrypted_text;
}

} // namespace playfair
} // namespace ciphers

/**
 * Function to test above algorithm
 */
void test() {
  std::cout << "******************Test Cases******************" << std::endl;
  // Test 1
  std::string text1 = "COMPUTER";
  std::string key1 = "MONARCHY";
  std::string encrypted1 = ciphers::playfair::encrypt(text1, key1);
  std::string decrypted1 = ciphers::playfair::decrypt(encrypted1, key1);
  assert(text1 == decrypted1);
  std::cout << "Original text : " << text1;
  std::cout << "\nKey : " << key1;
  std::cout << "\nEncrypted text  : " << encrypted1;
  std::cout << "\nDecrypted text : " << decrypted1 << std::endl;
  std::cout << "**********************************************" << std::endl;

  // Test 2
  std::string text2 = "LALALAND";
  std::string key2 = "MOVIE";
  std::string encrypted2 = ciphers::playfair::encrypt(text2, key2);
  std::string decrypted2 = ciphers::playfair::decrypt(encrypted2, key2);
  assert(text2 == decrypted2);
  std::cout << "Original text : " << text2;
  std::cout << "\nKey : " << key2;
  std::cout << "\nEncrypted text : " << encrypted2;
  std::cout << "\nDecrypted text : " << decrypted2 << std::endl;
  std::cout << "**********************************************" << std::endl;
}

/** Driver Code */
int main() {
  // Testing
  test();
  return 0;
}
