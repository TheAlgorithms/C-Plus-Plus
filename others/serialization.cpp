#include <fstream>
#include <iostream>
#include <string>

/**
 * @file
 * @brief A simple Serializer and Deserializer utility for fundamental data
 * types and strings.
 */


class Serializer {
 public:
    /**
     * Serializes fundamental data types (like int, float, double, etc.) to a
     * binary file.
     * @tparam T The type of the data to be serialized.
     * @param out The output stream (std::ofstream).
     * @param data The data to be serialized.
     *
     * @note This function only works for fundamental types (primitives).
     */
    template <typename T>
    static void serialize(std::ofstream &out, const T &data) {
        static_assert(
            std::is_fundamental<T>::value,
            "Non-fundamental types are not allowed for this function!");
        out.write(reinterpret_cast<const char *>(&data), sizeof(T));
    }

    /**
     * Serializes a string to a binary file.
     * @param out The output stream (std::ofstream).
     * @param data The string to be serialized.
     *
     * The string is serialized by first storing its length, followed by the
     * content.
     */
    static void serialize(std::ofstream &out, const std::string &data) {
        ssize_t length = data.size();
        serialize(out, length);           // Serialize the length of the string.
        out.write(data.c_str(), length);  // Serialize the string characters.
        out.put('|');  // Add a delimiter to denote the end of the string.
    }
};

/**
 * @class Deserializer
 * A utility class for deserializing data from a binary file.
 */
class Deserializer {
 public:
    /**
     * Deserializes fundamental data types (like int, float, double, etc.) from
     * a binary file.
     * @tparam T The type of the data to be deserialized.
     * @param in The input stream (std::ifstream).
     * @param data The variable where the deserialized data will be stored.
     *
     * @note This function only works for fundamental types (primitives).
     */
    template <typename T>
    static void deserialize(std::ifstream &in, T &data) {
        static_assert(
            std::is_fundamental<T>::value,
            "Non-fundamental types are not allowed for this function!");
        in.read(reinterpret_cast<char *>(&data), sizeof(T));
    }

    /**
     * Deserializes a string from a binary file.
     * @param in The input stream (std::ifstream).
     * @param data The string where the deserialized content will be stored.
     *
     * The string is deserialized by reading its length, followed by the
     * characters, and finally validating the delimiter throws error if the
     * delimiter '|' is not found.
     */
    static void deserialize(std::ifstream &in, std::string &data) {
        ssize_t length;
        deserialize(in, length);  // Deserialize the length of the string.

        if (length > 1024 * 1024)  // Sanity check to prevent huge strings.
        {
            throw std::runtime_error(
                "Deserialized string length is too large.");
        }

        data.resize(length);  // Resize the string to fit the incoming data.
        in.read(&data[0], length);  // Read the string characters.
        char delimiter;
        in.get(delimiter);  // Check the delimiter.
        if (delimiter != '|') {
            throw std::runtime_error("Delimiter '|' not found after string.");
        }
    }
};

void runTests();

/**
 * Demonstrates the use of Serializer and Deserializer for fundamental types and
 * strings.
 */
int main() {
    std::ofstream outFile("output.bin", std::ios::binary);
    std::ifstream inFile("output.bin", std::ios::binary);

    if (!outFile || !inFile) {
        std::cerr << "Error opening files.\n";
        return 1;
    }

    // Data to be serialized.
    int num = 42;
    float pi = 3.14159f;
    std::string message = "Hello, Sharon!";

    Serializer::serialize(outFile, num);
    Serializer::serialize(outFile, pi);
    Serializer::serialize(outFile, message);
    outFile.close();  

    int numRead;
    float piRead;
    std::string messageRead;

    // Deserialize the data.
    Deserializer::deserialize(inFile, numRead);
    Deserializer::deserialize(inFile, piRead);
    Deserializer::deserialize(inFile, messageRead);
    inFile.close();

    std::cout << "Deserialized int: " << numRead << "\n";
    std::cout << "Deserialized float: " << piRead << "\n";
    std::cout << "Deserialized string: " << messageRead << "\n";

    return 0;
}

/**
 * @brief A test suite to perform extensive testing on the Serializer and
 * Deserializer.
 */
void runTests() {
    std::ofstream outFile("test_output.bin", std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for output.\n";
        return;
    }

    int testInt = 12345;
    double testDouble = 9876.54321;
    char testChar = 'A';
    std::string testString = "Testing String Serialization!";

    // Serialize the data
    Serializer::serialize(outFile, testInt);
    Serializer::serialize(outFile, testDouble);
    Serializer::serialize(outFile, testChar);
    Serializer::serialize(outFile, testString);

    outFile.close();

    std::ifstream inFile("test_output.bin", std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for input.\n";
        return;
    }

    int intResult;
    double doubleResult;
    char charResult;
    std::string stringResult;

    // Deserialize the data
    Deserializer::deserialize(inFile, intResult);
    Deserializer::deserialize(inFile, doubleResult);
    Deserializer::deserialize(inFile, charResult);
    Deserializer::deserialize(inFile, stringResult);

    inFile.close();

    std::cout << "Test Int: " << intResult << "\n";
    std::cout << "Test Double: " << doubleResult << "\n";
    std::cout << "Test Char: " << charResult << "\n";
    std::cout << "Test String: " << stringResult << "\n";
}
