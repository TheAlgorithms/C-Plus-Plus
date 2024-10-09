/**
 * @file
 * @author [Shree Harish S](https://github.com/ShreeHarish)
 * @brief C++ implementation of the [RIPEMD-160 Hashing
 * Algorithm](https://homes.esat.kuleuven.be/~bosselae/ripemd160/pdf/AB-9601/AB-9601.pdf)
 *
 * @details
 * [RIPEMD-160](https://en.wikipedia.org/wiki/SHA-1) RIPEMD (RACE
 * Integrity Primitives Evaluation Message Digest) is a cryptographic hash
 * function designed to produce a 160-bit (20-byte) hash value from input data
 * of arbitrary size. It was developed as a part of the RIPEMD family of hash
 * functions in 1996 by a team of cryptographers including Ronald Rivest and
 * others. RIPEMD-160 is used in some cryptocurrencies and blockchain
 * technologies as part of their hashing mechanisms.
 *
 * Produces a fixed-size output of 160 bits (20 bytes), which is commonly
 * represented as a 40-character hexadecimal string.
 *
 * RIPEMD-160 uses a Merkle-Damgård construction, meaning it processes the input
 * data in blocks (512 bits) and produces a hash iteratively. It employs a total
 * of 80 processing steps, split into two parallel paths that converge at the
 * end.
 *
 */

#include <cassert>   /// For assert
#include <cstdint>   /// For data types such as int32_t, uint32_t, etc
#include <iomanip>   /// For functions like setw, setfill
#include <iostream>  /// For managing io
#include <sstream>   /// For bytes to hex string
#include <string>    /// For string data
#include <thread>    /// To parallelize for efficiency
#include <vector>    /// For dynamic arrays

/**
 * @namespace hashing
 * @brief Hashing algorithms
 */
namespace hashing {
/**
 * @class RIPEMD-160
 * @brief Implementation of relevant functions to perform RIPEMD160 hashing.
 * This class expects a string to hash.
 */
class RIPEMD160 {
 private:
    /**
     * @brief converts string data to vector of uint32_t (4 byte words)
     * @details converts the string to 4 byte words in little endian format
     * after adding padding and message length as specified in the algorithm
     * @param data data to be converted
     * @return vector of 4 byte words in little endian format
     */
    std::vector<uint32_t> string_to_word_data(std::string &data) {
        std::vector<uint32_t> word_data;

        // convert string data to 4 byte words in little endian format
        for (uint64_t i = 0; i < (data.size() / 4) * 4; i += 4) {
            word_data.push_back(static_cast<uint32_t>(data[i]) |
                                (static_cast<uint32_t>(data[i + 1]) << 8) |
                                (static_cast<uint32_t>(data[i + 2]) << 16) |
                                (static_cast<uint32_t>(data[i + 3]) << 24));
        }

        // add padding to data
        int extra = data.size() % 4;

        if (extra == 0) {
            word_data.push_back(0x00000080);
        }

        else if (extra == 1) {
            word_data.push_back(static_cast<uint32_t>(data[data.size() - 1]) |
                                0x00008000);
        }

        else if (extra == 2) {
            word_data.push_back(
                static_cast<uint32_t>(data[data.size() - 2]) |
                (static_cast<uint32_t>(data[data.size() - 1]) << 8) |
                0x00800000);
        }

        else if (extra == 3) {
            word_data.push_back(
                static_cast<uint32_t>(data[data.size() - 3]) |
                (static_cast<uint32_t>(data[data.size() - 2]) << 8) |
                (static_cast<uint32_t>(data[data.size() - 1]) << 16) |
                0x80000000);
        }

        while (word_data.size() % 16 != 14) {
            word_data.push_back(0x00000000);
        }

        // add message length
        word_data.push_back((static_cast<uint64_t>(data.size()) << 3) &
                            0xffffffff);
        word_data.push_back((static_cast<uint64_t>(data.size()) >> 29) &
                            0xffffffff);

        return word_data;
    }

    /**
     * @brief implements f(j,x,y,z)
     * @param j round number j / 16
     * @param x value x
     * @param y value y
     * @param z value z
     * @return returns the function value
     */
    uint32_t f(int j, uint32_t x, uint32_t y, uint32_t z) {
        if (j == 0) {
            return x ^ y ^ z;
        }

        else if (j == 1) {
            return (x & y) | (~x & z);
        }

        else if (j == 2) {
            return (x | ~y) ^ z;
        }

        else if (j == 3) {
            return (x & z) | (y & ~z);
        }

        else {  /// if (j == 4)
            return x ^ (y | ~z);
        }
    }

    /**
     * @brief implements K value for a given j
     * @param j round number j / 16
     * @return appropriate K value
     */
    uint32_t K(int j) {
        if (j == 0) {
            return static_cast<uint32_t>(0x00000000);
        }

        else if (j == 1) {
            return static_cast<uint32_t>(0x5A827999);
        }

        else if (j == 2) {
            return static_cast<uint32_t>(0x6ED9EBA1);
        }

        else if (j == 3) {
            return static_cast<uint32_t>(0x8F1BBCDC);
        }

        else {  /// if (j == 4)
            return static_cast<uint32_t>(0xA953FD4E);
        }
    }

    /**
     * @brief implements K' value for a given j
     * @param j round number j / 16
     * @return appropriate K' value
     */
    uint32_t K_dash(int j) {
        if (j == 0) {
            return 0x50A28BE6;
        }

        else if (j == 1) {
            return 0x5C4DD124;
        }

        else if (j == 2) {
            return 0x6D703EF3;
        }

        else if (j == 3) {
            return 0x7A6D76E9;
        }

        else {  /// if (j == 4)
            return 0x00000000;
        }
    }

    /**
     * @brief implements r value for a given j
     * @param j round number j
     * @return appropriate r value
     */
    int r(int j) {
        static const int r_value[80] = {
            0, 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
            7, 4,  13, 1,  10, 6,  15, 3,  12, 0, 9,  5,  2,  14, 11, 8,
            3, 10, 14, 4,  9,  15, 8,  1,  2,  7, 0,  6,  13, 11, 5,  12,
            1, 9,  11, 10, 0,  8,  12, 4,  13, 3, 7,  15, 14, 5,  6,  2,
            4, 0,  5,  9,  7,  12, 2,  10, 14, 1, 3,  8,  11, 6,  15, 13};

        return r_value[j];
    }

    /**
     * @brief implements r' value for a given j
     * @param j round number j
     * @return appropriate r' value
     */
    int r_dash(int j) {
        static const int r_dash_value[80] = {
            5,  14, 7,  0, 9, 2,  11, 4,  13, 6,  15, 8,  1,  10, 3,  12,
            6,  11, 3,  7, 0, 13, 5,  10, 14, 15, 8,  12, 4,  9,  1,  2,
            15, 5,  1,  3, 7, 14, 6,  9,  11, 8,  12, 2,  10, 0,  4,  13,
            8,  6,  4,  1, 3, 11, 15, 0,  5,  12, 2,  13, 9,  7,  10, 14,
            12, 15, 10, 4, 1, 5,  8,  7,  6,  2,  13, 14, 0,  3,  9,  11};

        return r_dash_value[j];
    }

    /**
     * @brief implements s value for a given j
     * @param j round number j
     * @return appropriate s value
     */
    int s(int j) {
        static const int s_value[80] = {
            11, 14, 15, 12, 5,  8,  7,  9,  11, 13, 14, 15, 6,  7,  9,  8,
            7,  6,  8,  13, 11, 9,  7,  15, 7,  12, 15, 9,  11, 7,  13, 12,
            11, 13, 6,  7,  14, 9,  13, 15, 14, 8,  13, 6,  5,  12, 7,  5,
            11, 12, 14, 15, 14, 15, 9,  8,  9,  14, 5,  6,  8,  6,  5,  12,
            9,  15, 5,  11, 6,  8,  13, 12, 5,  12, 13, 14, 11, 8,  5,  6};

        return s_value[j];
    }

    /**
     * @brief implements s' value for a given j
     * @param j round number j
     * @return appropriate s' value
     */
    int s_dash(int j) {
        static const int s_dash_value[80] = {
            8,  9,  9,  11, 13, 15, 15, 5,  7,  7,  8,  11, 14, 14, 12, 6,
            9,  13, 15, 7,  12, 8,  9,  11, 7,  7,  12, 7,  6,  15, 13, 11,
            9,  7,  15, 11, 8,  6,  6,  14, 12, 13, 5,  14, 13, 13, 7,  5,
            15, 5,  8,  11, 14, 14, 6,  14, 6,  9,  12, 9,  12, 5,  15, 8,
            8,  5,  12, 9,  12, 5,  14, 6,  8,  13, 6,  5,  15, 13, 11, 11};

        return s_dash_value[j];
    }

    /**
     * @brief cyclic left shift of uint32_t
     * @param value value to be shifted
     * @param shift number of bits to be shifted
     * @return shifter value
     */
    inline uint32_t cyclic_left_shift(uint32_t value, int shift) {
        return (value << shift) | (value >> (32 - shift));
    }

    /**
     * @brief computes the 80 rounds for current block
     * @details hashing is performed on blocks of 512 bits and performed on two
     * parallel path. this function performs one of the parallel path.
     * @param A current value of A
     * @param B current value of B
     * @param C current value of C
     * @param D current value of D
     * @param E current value of E
     * @param T current value of T. This is a temporary memory for computation
     * @param current_block_data current 512 bits or 16 4-byte words that is
     * being processed
     * @return void
     */
    void compute_for_block(int32_t *A, int32_t *B, int32_t *C, int32_t *D,
                           int32_t *E, int32_t *T,
                           const std::vector<uint32_t> &current_block_data) {
        for (int j = 0; j < 80; j++) {
            *T = cyclic_left_shift(*A + f(j >> 4, *B, *C, *D) +
                                       current_block_data[r(j)] + K(j >> 4),
                                   s(j)) +
                 *E;

            *A = *E;
            *E = *D;
            *D = cyclic_left_shift(*C, 10);
            *C = *B;
            *B = *T;
        }
    }

    /**
     * @brief computes the 80 rounds for current block
     * @details hashing is performed on blocks of 512 bits and performed on two
     * parallel path. this function performs the other parallel path.
     * @param A current value of A_hash
     * @param B current value of B_hash
     * @param C current value of C_hash
     * @param D current value of D_hash
     * @param E current value of E_hash
     * @param T current value of T_hash. This is a temporary memory for
     * computation
     * @param current_block_data current 512 bits or 16 4-byte words that is
     * being processed
     * @return void
     */
    void compute_for_block_dash(
        int32_t *A, int32_t *B, int32_t *C, int32_t *D, int32_t *E, int32_t *T,
        const std::vector<uint32_t> &current_block_data) {
        for (int j = 0; j < 80; j++) {
            *T = cyclic_left_shift(*A + f(4 - (j >> 4), *B, *C, *D) +
                                       current_block_data[r_dash(j)] +
                                       K_dash(j >> 4),
                                   s_dash(j)) +
                 *E;

            *A = *E;
            *E = *D;
            *D = cyclic_left_shift(*C, 10);
            *C = *B;
            *B = *T;
        }
    }

    /**
     * @brief converts from bytes in little endian format to string
     * @param value value to be converted to string
     * @return converted string value
     */
    std::string uint32_t_to_string(uint32_t value) {
        std::stringstream stream;
        for (uint32_t i = 0; i < 4; ++i) {
            stream << std::setfill('0') << std::setw(2) << std::hex
                   << ((value >> (i * 8)) & 0xff);
        }

        return stream.str();
    }

 public:
    /**
     * @brief the hashing function that performs the RIPEMD-160 hashing
     * @param data string data to be hashed
     * @return hex of hash in string format
     */
    std::string hash(std::string data) {
        // convert string to 4-byte words including padding
        std::vector<uint32_t> word_data = string_to_word_data(data);

        // holds the current 512 bits of data to be processed
        std::vector<uint32_t> current_block_data;

        // initial state
        int64_t h_0 = 0x67452301;
        int64_t h_1 = 0xefcdab89;
        int64_t h_2 = 0x98badcfe;
        int64_t h_3 = 0x10325476;
        int64_t h_4 = 0xc3d2e1f0;

        int32_t A = 0, B = 0, C = 0, D = 0, E = 0, T = 0;
        int32_t A_dash = 0, B_dash = 0, C_dash = 0, D_dash = 0, E_dash = 0,
                T_dash = 0;

        // for each 512 bits of data
        for (uint64_t i = 0; i < word_data.size(); i += 16) {
            current_block_data = std::vector<uint32_t>(
                word_data.begin() + i, word_data.begin() + i + 16);

            A = h_0;
            B = h_1;
            C = h_2;
            D = h_3;
            E = h_4;

            A_dash = h_0;
            B_dash = h_1;
            C_dash = h_2;
            D_dash = h_3;
            E_dash = h_4;

            // parallely process the 80 rounds
            std::thread compute_for_block_thread(&compute_for_block, this, &A,
                                                 &B, &C, &D, &E, &T,
                                                 std::ref(current_block_data));
            std::thread compute_for_block_dash_thread(
                &compute_for_block_dash, this, &A_dash, &B_dash, &C_dash,
                &D_dash, &E_dash, &T_dash, std::ref(current_block_data));

            compute_for_block_thread.join();
            compute_for_block_dash_thread.join();

            // update the current state after 80 rounds
            T = h_1 + C + D_dash;
            h_1 = h_2 + D + E_dash;
            h_2 = h_3 + E + A_dash;
            h_3 = h_4 + A + B_dash;
            h_4 = h_0 + B + C_dash;
            h_0 = T;
        }

        // convert the bytes in little endian format to hex in string format
        std::string hash = "";
        hash = hash + uint32_t_to_string(h_0);
        hash = hash + uint32_t_to_string(h_1);
        hash = hash + uint32_t_to_string(h_2);
        hash = hash + uint32_t_to_string(h_3);
        hash = hash + uint32_t_to_string(h_4);

        return hash;
    }
};
}  // namespace hashing

/**
 * @brief test example hashes
 */
static void check_me(std::string data, std::string expected_hash) {
    hashing::RIPEMD160 obj;

    std::cout << "Hashing the data " + data + "\n";
    std::cout << "Obtained hash : " + obj.hash(data) + "\n";
    std::cout << "Expected hash : " + expected_hash + "\n";
    assert(obj.hash(data).compare(expected_hash) == 0);
    std::cout
        << "**********************************************************\n\n";
}

static void test() {
    check_me("", "9c1185a5c5e9fc54612808977ee8f548b2258d31");
    check_me("a", "0bdc9d2d256b3ee9daae347be6f4dc835a467ffe");
    check_me("abc", "8eb208f7e05d987a9b044a8e98c6b087f15a0bfc");
    check_me("message digest", "5d0689ef49d2fae572b881b123a85ffa21595f36");
    check_me("abcdefghijklmnopqrstuvwxyz",
             "f71c27109c692c1b56bbdceb5b9d2865b3708dbc");
    check_me("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
             "12a053384a9c0c88e405a06c27dcf49ada62eb2b");
    check_me(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0"
        "123456789",
        "b0e20b6e3116640286ed3a87a5713079b21f5189");
    check_me(
        "12345678901234567890123456789012345678901234567890123"
        "456789012345678901234567890",
        "9b752e45573d4b39f4dbd3323cab82bf63326bfb");
}

/**
 * @brief main function
 * @return 0 on exit
 */
int main(int argc, char *argv[]) {
    test();

    return 0;
}