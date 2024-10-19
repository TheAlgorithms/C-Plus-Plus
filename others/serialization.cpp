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
 * data, and a `|` delimiter to mark the end.
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
     * Serializes a string to a binary file.
     * @param out The output stream (std::ofstream).
     * @param data The string to be serialized.
     *
     * The string is serialized by first storing its length, followed by the
     * content.
     */
    static void serialize(std::ofstream &out, const std::string &data) {
        std::uint32_t length = data.size();
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
/**
 * @brief self test implementation
 * @return void
 */
void tests() {
    try {
        std::ofstream outFile("test_output.bin", std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Error opening file for output.");
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
            throw std::runtime_error("Error opening file for input.");
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
    } catch (const std::exception &e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
    }

    // Test for file opening failure
    try {
        std::ifstream inFile("non_existent_file.bin", std::ios::binary);
        if (!inFile) {
            throw std::runtime_error("Error opening non-existent file.");
        }
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) == "Error opening non-existent file.");
        std::cout << "File opening error test passed!\n";
    }

    // Test for deserialization failure (e.g., wrong file format)
    try {
        std::ofstream outFile("wrong_format.bin", std::ios::binary);
        outFile << "This is not serialized data";  // Writing incorrect data
        outFile.close();

        std::ifstream inFile("wrong_format.bin", std::ios::binary);
        if (!inFile) {
            throw std::runtime_error("Error opening file for input.");
        }

        int intResult;
        // Deserialize expecting binary data, this should fail
        Deserializer::deserialize(inFile, intResult);

        inFile.close();
    } catch (const std::exception &e) {
        std::cout << "Deserialization error test passed: " << e.what()
                  << std::endl;
    }

    // Test for string too large error
    try {
        std::ofstream outFile("large_string.bin", std::ios::binary);
        std::string largeString(1024 * 1024 + 1,
                                'A');  // String larger than 1MB
        Serializer::serialize(outFile,
                              largeString);  // Should succeed in serialization
        outFile.close();

        std::ifstream inFile("large_string.bin", std::ios::binary);
        std::string deserializedString;
        Deserializer::deserialize(
            inFile, deserializedString);  // Should fail in deserialization
        inFile.close();
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) ==
               "Deserialized string length is too large.");
        std::cout << "Large string error test passed!\n";
    }

    // Test for missing delimiter
    try {
        std::ofstream outFile("missing_delimiter.bin", std::ios::binary);
        std::string testString = "Test String";
        std::uint32_t length = testString.size();
        outFile.write(reinterpret_cast<const char *>(&length), sizeof(length));
        outFile.write(testString.c_str(), length);  // No delimiter
        outFile.close();

        std::ifstream inFile("missing_delimiter.bin", std::ios::binary);
        std::string deserializedString;
        Deserializer::deserialize(inFile, deserializedString);  // Should fail
        inFile.close();
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) ==
               "Delimiter '|' not found after string.");
        std::cout << "Missing delimiter error test passed!\n";
    }
    // Clean up temporary files that were created during testing.
    std::remove("test_output.bin");
    std::remove("wrong_format.bin");
    std::remove("large_string.bin");
    std::remove("missing_delimiter.bin");
}

int main() {
    tests();
    return 0;
}
