/**
 * @file
 * @brief A simple Serializer and Deserializer utility for fundamental data
 * types and strings.
 */
#include <cassert>      // for assert
#include <cstdint>      // for std::uint32_t
#include <fstream>      // for std::ifstream std::ofstream
#include <iostream>     // for std::ios std::cout std::cerr
#include <string>       // for std::string
#include <type_traits>  // for std::is_fundamental

/**
 * @brief A utility class for serializing fundamental data types and strings to
 * a binary file.
 */
class Serializer {
 public:
    /**
     * @brief Serializes fundamental data types to a binary file.
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
 * A utility class for deserializing fundamental data types and strings to a
 * binary file
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
/**
 * @brief self test implementation
 * @return void
 */
void tests() {
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

    // Assert that the original and deserialized values are the same
    assert(testInt == intResult);
    assert(testDouble == doubleResult);
    assert(testChar == charResult);
    assert(testString == stringResult);

    std::cout << "All tests passed!\n";
}

int main() {
    tests();

    return 0;
}

/**
 * @brief A test suite to perform extensive testing on the Serializer and
 * Deserializer.
 */
