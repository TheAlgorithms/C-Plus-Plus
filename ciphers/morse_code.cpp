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
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

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
 * Get the morse representation for given character.
 * @param c Character
 * @returns morse representation string of character
 */
std::string char_to_morse(const char &c) {
    // return corresponding morse code
    switch (c) {
        case 'a':
            return ".-";
        case 'b':
            return "-...";
        case 'c':
            return "-.-.";
        case 'd':
            return "-..";
        case 'e':
            return ".";
        case 'f':
            return "..-.";
        case 'g':
            return "--.";
        case 'h':
            return "....";
        case 'i':
            return "..";
        case 'j':
            return ".---";
        case 'k':
            return "-.-";
        case 'l':
            return ".-..";
        case 'm':
            return "--";
        case 'n':
            return "-.";
        case 'o':
            return "---";
        case 'p':
            return ".--.";
        case 'q':
            return "--.-";
        case 'r':
            return ".-.";
        case 's':
            return "...";
        case 't':
            return "-";
        case 'u':
            return "..-";
        case 'v':
            return "...-";
        case 'w':
            return ".--";
        case 'x':
            return "-..-";
        case 'y':
            return "-.--";
        case 'z':
            return "--..";
        case '1':
            return ".----";
        case '2':
            return "..---";
        case '3':
            return "...--";
        case '4':
            return "....-";
        case '5':
            return ".....";
        case '6':
            return "-....";
        case '7':
            return "--...";
        case '8':
            return "---..";
        case '9':
            return "----.";
        case '0':
            return "-----";
        default:
            std::cerr << "Found invalid character: " << c << ' ' << std::endl;
            std::exit(0);
    }
}
/**
 * Get character from the morse representation.
 * @param s Morse representation
 * @returns corresponding character
 */
char morse_to_char(const std::string &s) {
    // return corresponding character
    if (s == ".-") {
        return 'a';
    } else if (s == "-...") {
        return 'b';
    } else if (s == "-.-.") {
        return 'c';
    } else if (s == "-..") {
        return 'd';
    } else if (s == ".") {
        return 'e';
    } else if (s == "..-.") {
        return 'f';
    } else if (s == "--.") {
        return 'g';
    } else if (s == "....") {
        return 'h';
    } else if (s == "..") {
        return 'i';
    } else if (s == ".---") {
        return 'j';
    } else if (s == "-.-") {
        return 'k';
    } else if (s == ".-..") {
        return 'l';
    } else if (s == "--") {
        return 'm';
    } else if (s == "-.") {
        return 'n';
    } else if (s == "---") {
        return 'o';
    } else if (s == ".--.") {
        return 'p';
    } else if (s == "--.-") {
        return 'q';
    } else if (s == ".-.") {
        return 'r';
    } else if (s == "...") {
        return 's';
    } else if (s == "-") {
        return 't';
    } else if (s == "..-") {
        return 'u';
    } else if (s == "...-") {
        return 'v';
    } else if (s == ".--") {
        return 'w';
    } else if (s == "-..-") {
        return 'x';
    } else if (s == "-.--") {
        return 'y';
    } else if (s == "--..") {
        return 'z';
    } else if (s == ".----") {
        return '1';
    } else if (s == "..---") {
        return '2';
    } else if (s == "...--") {
        return '3';
    } else if (s == "....-") {
        return '4';
    } else if (s == ".....") {
        return '5';
    } else if (s == "-....") {
        return '6';
    } else if (s == "--...") {
        return '7';
    } else if (s == "---..") {
        return '8';
    } else if (s == "----.") {
        return '9';
    } else if (s == "-----") {
        return '0';
    } else {
        std::cerr << "Found invalid Morse code: " << s << ' ' << std::endl;
        std::exit(0);
    }
}
/**
 * Encrypt given text using morse code.
 * @param text text to be encrypted
 * @returns new encrypted text
 */
std::string encrypt(const std::string &text) {
    std::string encrypted_text = "";  // Empty string to store encrypted text
    // Going through each character of text and converting it
    // to morse representation
    for (const char &c : text) {
        encrypted_text += ciphers::morse::char_to_morse(c) + " ";
    }
    return encrypted_text;  // Returning encrypted text
}
/**
 * Decrypt given morse coded text.
 * @param text text to be decrypted
 * @returns new decrypted text
 */
std::string decrypt(const std::string &text) {
    // Going through each character of text and converting it
    // back to normal representation.
    std::string decrypted_text = "";  // Empty string to store decrypted text
    // Spliting string (with delimiter = " ") and storing it
    // in vector
    std::size_t pos_start = 0, pos_end = 0, delim_len = 1;
    std::vector<std::string> splits;
    while ((pos_end = text.find(' ', pos_start)) != std::string::npos) {
        std::string token = text.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splits.push_back(token);
    }

    // Traversing through each morse code string
    for (const std::string &s : splits) {
        // Add corresponding character
        decrypted_text += ciphers::morse::morse_to_char(s);
    }

    return decrypted_text;  // Returning decrypted text
}
}  // namespace morse
}  // namespace ciphers

/**
 * @brief Function to test above algorithm
 * @returns void
 */
static void test() {
    // Test 1
    std::string text1 = "01234567890";
    std::string encrypted1 = ciphers::morse::encrypt(text1);
    std::string decrypted1 = ciphers::morse::decrypt(encrypted1);
    assert(text1 == decrypted1);
    std::cout << "Original text : " << text1 << std::endl;
    std::cout << "Encrypted text : " << encrypted1 << std::endl;
    std::cout << "Decrypted text : " << decrypted1 << std::endl;
    // Test 2
    std::string text2 = "abcdefghijklmnopqrstuvwxyz";
    std::string encrypted2 = ciphers::morse::encrypt(text2);
    std::string decrypted2 = ciphers::morse::decrypt(encrypted2);
    assert(text2 == decrypted2);
    std::cout << "Original text : " << text2 << std::endl;
    std::cout << "Encrypted text : " << encrypted2 << std::endl;
    std::cout << "Decrypted text : " << decrypted2 << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Testing
    test();
    return 0;
}
