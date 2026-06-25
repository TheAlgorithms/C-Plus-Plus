/**
 * @file
 * @author [Deep Raval](https://github.com/imdeep2905)
 *
 * @brief Implementation of [Morse Code]
 * (https://en.wikipedia.org/wiki/Morse_code).
 *
 * @details
 * Morse code is a method used in telecommunication to encode text characters
 * as standardized sequences of two different signal durations, called dots
 * and dashes or dits and dahs. Morse code is named after Samuel Morse, an
 * inventor of the telegraph.
 */

#include <cassert>    /// for assert
#include <iostream>   /// for std::cout
#include <stdexcept>  /// for std::invalid_argument
#include <string>     /// for std::string
#include <vector>     /// for std::vector

/** \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
namespace ciphers {
/** \namespace morse
 * \brief Functions for [Morse Code]
 * (https://en.wikipedia.org/wiki/Morse_code).
 */
namespace morse {

/**
 * @brief Get the morse representation for a given character.
 * @param c character to encode (lowercase a–z or digit 0–9)
 * @returns morse code string for the character
 * @throws std::invalid_argument if the character is not supported
 */
std::string char_to_morse(const char &c) {
    switch (c) {
        case 'a': return ".-";
        case 'b': return "-...";
        case 'c': return "-.-.";
        case 'd': return "-..";
        case 'e': return ".";
        case 'f': return "..-.";
        case 'g': return "--.";
        case 'h': return "....";
        case 'i': return "..";
        case 'j': return ".---";
        case 'k': return "-.-";
        case 'l': return ".-..";
        case 'm': return "--";
        case 'n': return "-.";
        case 'o': return "---";
        case 'p': return ".--.";
        case 'q': return "--.-";
        case 'r': return ".-.";
        case 's': return "...";
        case 't': return "-";
        case 'u': return "..-";
        case 'v': return "...-";
        case 'w': return ".--";
        case 'x': return "-..-";
        case 'y': return "-.--";
        case 'z': return "--..";
        case '1': return ".----";
        case '2': return "..---";
        case '3': return "...--";
        case '4': return "....-";
        case '5': return ".....";
        case '6': return "-....";
        case '7': return "--...";
        case '8': return "---..";
        case '9': return "----.";
        case '0': return "-----";
        default:
            throw std::invalid_argument(
                std::string("Found invalid character: ") + c);
    }
}

/**
 * @brief Get the character from its morse representation.
 * @param s morse code string to decode
 * @returns the character corresponding to the morse code
 * @throws std::invalid_argument if the morse code string is not recognised
 */
char morse_to_char(const std::string &s) {
    if (s == ".-")    return 'a';
    if (s == "-...")  return 'b';
    if (s == "-.-.")  return 'c';
    if (s == "-..")   return 'd';
    if (s == ".")     return 'e';
    if (s == "..-.")  return 'f';
    if (s == "--.")   return 'g';
    if (s == "....")  return 'h';
    if (s == "..")    return 'i';
    if (s == ".---")  return 'j';
    if (s == "-.-")   return 'k';
    if (s == ".-..")  return 'l';
    if (s == "--")    return 'm';
    if (s == "-.")    return 'n';
    if (s == "---")   return 'o';
    if (s == ".--.")  return 'p';
    if (s == "--.-")  return 'q';
    if (s == ".-.")   return 'r';
    if (s == "...")   return 's';
    if (s == "-")     return 't';
    if (s == "..-")   return 'u';
    if (s == "...-")  return 'v';
    if (s == ".--")   return 'w';
    if (s == "-..-")  return 'x';
    if (s == "-.--")  return 'y';
    if (s == "--..")  return 'z';
    if (s == ".----") return '1';
    if (s == "..---") return '2';
    if (s == "...--") return '3';
    if (s == "....-") return '4';
    if (s == ".....") return '5';
    if (s == "-....") return '6';
    if (s == "--...") return '7';
    if (s == "---..") return '8';
    if (s == "----.") return '9';
    if (s == "-----") return '0';
    throw std::invalid_argument("Found invalid Morse code: " + s);
}

/**
 * @brief Encrypt text to morse code.
 * @param text lowercase alphanumeric string to encrypt
 * @returns morse-encoded string with tokens separated by spaces
 * @throws std::invalid_argument if any character in text is not supported
 */
std::string encrypt(const std::string &text) {
    std::string encrypted_text = "";
    for (const char &c : text) {
        encrypted_text += ciphers::morse::char_to_morse(c) + " ";
    }
    return encrypted_text;
}

/**
 * @brief Decrypt morse code back to plain text.
 * @param text morse-encoded string with tokens separated by spaces
 * @returns decoded alphanumeric string
 * @throws std::invalid_argument if any morse token is not recognised
 */
std::string decrypt(const std::string &text) {
    std::string decrypted_text = "";
    std::size_t pos_start = 0, pos_end = 0, delim_len = 1;
    std::vector<std::string> splits;
    while ((pos_end = text.find(' ', pos_start)) != std::string::npos) {
        std::string token = text.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splits.push_back(token);
    }
    for (const std::string &s : splits) {
        decrypted_text += ciphers::morse::morse_to_char(s);
    }
    return decrypted_text;
}

}  // namespace morse
}  // namespace ciphers

/**
 * @brief Self-test implementation
 * @returns void
 */
static void test() {
    // Test 1: digits round-trip
    std::string text1 = "01234567890";
    std::string encrypted1 = ciphers::morse::encrypt(text1);
    std::string decrypted1 = ciphers::morse::decrypt(encrypted1);
    assert(text1 == decrypted1);
    std::cout << "Original text  : " << text1 << "\n";
    std::cout << "Encrypted text : " << encrypted1 << "\n";
    std::cout << "Decrypted text : " << decrypted1 << "\n\n";

    // Test 2: alphabet round-trip
    std::string text2 = "abcdefghijklmnopqrstuvwxyz";
    std::string encrypted2 = ciphers::morse::encrypt(text2);
    std::string decrypted2 = ciphers::morse::decrypt(encrypted2);
    assert(text2 == decrypted2);
    std::cout << "Original text  : " << text2 << "\n";
    std::cout << "Encrypted text : " << encrypted2 << "\n";
    std::cout << "Decrypted text : " << decrypted2 << "\n\n";

    // Test 3: invalid character must throw, NOT call std::exit
    bool threw = false;
    try {
        ciphers::morse::char_to_morse('@');
    } catch (const std::invalid_argument &e) {
        threw = true;
    }
    assert(threw && "char_to_morse must throw std::invalid_argument on bad input");

    // Test 4: invalid morse code must throw, NOT call std::exit
    threw = false;
    try {
        ciphers::morse::morse_to_char("..--..--");
    } catch (const std::invalid_argument &e) {
        threw = true;
    }
    assert(threw && "morse_to_char must throw std::invalid_argument on bad input");

    std::cout << "All tests passed.\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
