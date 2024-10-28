/**
 * @file serialization.cpp
 * @brief Utility for binary serialization and deserialization of fundamental
 * data types and strings.
 * @details
 * Binary serialization converts data into its binary format for
 * efficient storage and transmission, which is more compact and faster than
 * text-based formats. This utility handles fundamental types like integers,
 * doubles, and characters by writing their binary representation directly to a
 * file using `reinterpret_cast`.
 *
 * ### Serializing:
 * - **Fundamental Types**: Written directly in their binary form.
 * - **Strings**: The string's length is written first, followed by the string
 * data, and a `|` delimiter to mark the end. String size should not exceed 1MB.
 *
 * ### Deserializing:
 * - **Fundamental Types**: Reads the binary data back into the appropriate
 * type.
 * - **Strings**: Reads the string's length, followed by the string data, and
 * checks for the `|` delimiter. An error is raised if the delimiter is missing.
 *
 * @author [SharonIV0X86](https://github.com/SharonIV0X86)
 */

#include <cassert>      // for assert
#include <cstdint>      // for std::uint32_t
#include <cstdio>       // for std::remove()
#include <fstream>      // for std::ifstream std::ofstream
#include <iostream>     // for std::ios std::cout std::cerr
#include <string>       // for std::string
#include <type_traits>  // for std::is_fundamental

/** @namespace serialization
 * @brief Classes for binary Serialization and Deserialization 
 */
namespace serialization {
/**
 * @class Serializer
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
     * @brief Serializes a string to a binary file.
     * @param out The output stream (std::ofstream).
     * @param data The string to be serialized.
     *
     * @note The string is serialized by first storing its length, followed by
     * the content. String length should not exceed 1MB
     */
    static void serialize(std::ofstream &out, const std::string &data) {
        std::uint32_t length = data.size();

        // Check if the string exceeds the size limit of 1MB.
        const std::uint32_t max_size = 1024 * 1024;
        if (length > max_size) {
            throw std::runtime_error("String exceeds the maximum size of 1MB.");
        }

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
     * @brief Deserializes fundamental data types (like int, float, double,
     * etc.) from a binary file.
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
     * @brief Deserializes a string from a binary file.
     * @param in The input stream (std::ifstream).
     * @param data The string where the deserialized content will be stored.
     *
     * The string is deserialized by reading its length, followed by the
     * characters, and finally validating the delimiter throws error if the
     * delimiter '|' is not found.
     */
    static void deserialize(std::ifstream &in, std::string &data) {
        std::uint32_t length;
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
}  // namespace Serialization

/**
 * @brief self test implementation
 * @return void
 */
void tests() {
    // Serialize fundamental types and string
    std::ofstream outFile("test_output.bin", std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Error opening file for output.");
    }

    int testInt = 12345;
    double testDouble = 9876.54321;
    char testChar = 'A';
    std::string testString = "Testing String Serialization!";

    // Serialize the data
    serialization::Serializer::serialize(outFile, testInt);
    serialization::Serializer::serialize(outFile, testDouble);
    serialization::Serializer::serialize(outFile, testChar);
    serialization::Serializer::serialize(outFile, testString);

    outFile.close();

    // Deserialize the data and assert
    std::ifstream inFile("test_output.bin", std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Error opening file for input.");
    }

    int intResult;
    double doubleResult;
    char charResult;
    std::string stringResult;

    // Deserialize the data
    serialization::Deserializer::deserialize(inFile, intResult);
    serialization::Deserializer::deserialize(inFile, doubleResult);
    serialization::Deserializer::deserialize(inFile, charResult);
    serialization::Deserializer::deserialize(inFile, stringResult);

    inFile.close();

    // Assert that the original and deserialized values are the same
    assert(testInt == intResult);
    assert(testDouble == doubleResult);
    assert(testChar == charResult);
    assert(testString == stringResult);

    std::cout << "Basic serialization/deserialization tests passed!\n";

    // Test for string too large error
    try {
        std::ofstream largeOutFile("large_string.bin", std::ios::binary);
        // Create a string larger than 1MB
        std::string largeString(1024 * 1024 + 1, 'A');
        serialization::Serializer::serialize(
            largeOutFile,
            largeString);  // Should throw an error
        largeOutFile.close();
        assert(false);  // If we reach here, the test has failed.
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) ==
               "String exceeds the maximum size of 1MB.");
        std::cout << "Large string serialization error test passed!\n";
    }
    // Test for missing delimiter in string serialization
    try {
        std::ofstream missingDelimiterOutFile("missing_delimiter.bin",
                                              std::ios::binary);

        std::string incompleteString = "Incomplete string test";
        std::uint32_t length = incompleteString.size();

        // Serialize string length and content without the delimiter
        missingDelimiterOutFile.write(reinterpret_cast<const char *>(&length),
                                      sizeof(length));
        missingDelimiterOutFile.write(incompleteString.c_str(),
                                      length);  // No delimiter '|'
        missingDelimiterOutFile.close();

        std::ifstream missingDelimiterInFile("missing_delimiter.bin",
                                             std::ios::binary);

        std::string deserializedString;
        serialization::Deserializer::deserialize(
            missingDelimiterInFile,
            deserializedString);  // Should throw an error
        missingDelimiterInFile.close();

        assert(false);
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) ==
               "Delimiter '|' not found after string.");
        std::cout << "Missing delimiter error test passed!\n";
    }

    // Clean up temporary files that were created during testing
    std::remove("large_string.bin");
    std::remove("missing_delimiter.bin");
    std::remove("test_output.bin");

    std::cout << "All tests passed successfully!\n";
}
/**
 * @brief Main function
 * @returns 0 on successful exit
 */
int main() {
    tests();  // run self test implementations
    return 0;
}
