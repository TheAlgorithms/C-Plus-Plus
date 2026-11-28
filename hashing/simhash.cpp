/**
 * @file
 * @brief Implementation of [SimHash](https://en.wikipedia.org/wiki/SimHash)
 * (Charikar's Locality-Sensitive Hashing for cosine similarity).
 * @details
 * Computes a fixed-width binary fingerprint from weighted or unweighted string
 * tokens so that similar inputs produce hashes with small Hamming distance.
 * Reference: Moses S. Charikar (2002), "Similarity estimation techniques from
 * rounding algorithms", STOC '02.
 */

#include <array>      /// for std::array
#include <cassert>    /// for assert
#include <cctype>     /// for std::isalnum, std::tolower
#include <cmath>      /// for std::abs
#include <cstddef>    /// for std::size_t
#include <cstdint>    /// for std::uint64_t
#include <iostream>   /// for std::cout
#include <stdexcept>  /// for std::invalid_argument
#include <string>     /// for std::string
#include <utility>    /// for std::pair
#include <vector>     /// for std::vector

/**
 * @namespace hashing
 * @brief Hashing algorithms
 */
namespace hashing {

/**
 * @namespace simhash
 * @brief Functions for Charikar's 64-bit SimHash algorithm
 */
namespace simhash {

/**
 * @brief Extract lowercase alphanumeric tokens from an input string.
 * @param text input text to tokenize
 * @return vector of extracted tokens
 */
std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string current;
    for (unsigned char ch : text) {
        if (std::isalnum(ch) != 0) {
            current.push_back(static_cast<char>(std::tolower(ch)));
        } else if (!current.empty()) {
            tokens.push_back(current);
            current.clear();
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
    }
    return tokens;
}

/**
 * @brief Compute a deterministic 64-bit FNV-1a hash for a token.
 * @param token input string token
 * @return 64-bit unsigned integer digest
 */
std::uint64_t fnv1a_64(const std::string& token) {
    // Use FNV-1a instead of std::hash so fingerprints are deterministic across
    // compilers and standard library implementations.
    constexpr std::uint64_t offset_basis = 14695981039346656037ULL;
    constexpr std::uint64_t fnv_prime = 1099511628211ULL;
    std::uint64_t hash = offset_basis;
    for (unsigned char byte : token) {
        hash ^= static_cast<std::uint64_t>(byte);
        hash *= fnv_prime;
    }
    return hash;
}

/**
 * @brief Compute the 64-bit SimHash fingerprint of weighted features.
 * @param features pairs of (token, weight)
 * @return 64-bit SimHash fingerprint
 * @throws std::invalid_argument if features is empty
 */
std::uint64_t compute_simhash(
    const std::vector<std::pair<std::string, double>>& features) {
    if (features.empty()) {
        throw std::invalid_argument("features must not be empty");
    }

    std::array<double, 64> bit_weights{};
    for (const auto& [token, weight] : features) {
        const std::uint64_t digest = fnv1a_64(token);
        for (std::size_t bit = 0; bit < 64; ++bit) {
            if (((digest >> bit) & 1ULL) != 0ULL) {
                bit_weights[bit] += weight;
            } else {
                bit_weights[bit] -= weight;
            }
        }
    }

    std::uint64_t fingerprint = 0;
    for (std::size_t bit = 0; bit < 64; ++bit) {
        if (bit_weights[bit] >= 0.0) {
            fingerprint |= (1ULL << bit);
        }
    }
    return fingerprint;
}

/**
 * @brief Compute the 64-bit SimHash fingerprint of unweighted tokens.
 * @param tokens vector of string tokens
 * @return 64-bit SimHash fingerprint
 */
std::uint64_t compute_simhash(const std::vector<std::string>& tokens) {
    std::vector<std::pair<std::string, double>> weighted;
    weighted.reserve(tokens.size());
    for (const auto& token : tokens) {
        weighted.emplace_back(token, 1.0);
    }
    return compute_simhash(weighted);
}

/**
 * @brief Compute the Hamming distance between two 64-bit fingerprints.
 * @param hash_a first 64-bit hash
 * @param hash_b second 64-bit hash
 * @return number of differing bit positions in [0, 64]
 */
std::size_t hamming_distance(std::uint64_t hash_a, std::uint64_t hash_b) {
    std::uint64_t diff = hash_a ^ hash_b;
    std::size_t count = 0;
    while (diff != 0ULL) {
        diff &= (diff - 1ULL);
        ++count;
    }
    return count;
}

/**
 * @brief Compute normalized SimHash similarity in [0.0, 1.0].
 * @param hash_a first 64-bit hash
 * @param hash_b second 64-bit hash
 * @return similarity score where 1.0 means identical fingerprints
 */
double similarity(std::uint64_t hash_a, std::uint64_t hash_b) {
    return 1.0 - static_cast<double>(hamming_distance(hash_a, hash_b)) / 64.0;
}

}  // namespace simhash
}  // namespace hashing

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    const auto tokens_1 =
        hashing::simhash::tokenize("the quick brown fox jumps over the lazy dog");
    const auto tokens_2 =
        hashing::simhash::tokenize("the quick brown fox leaps over the lazy dog");
    const auto tokens_3 =
        hashing::simhash::tokenize("quantum chromodynamics and lattice gauge theory");

    assert(tokens_1.size() == 9);
    assert(hashing::simhash::tokenize("").empty());

    const std::uint64_t h1 = hashing::simhash::compute_simhash(tokens_1);
    const std::uint64_t h2 = hashing::simhash::compute_simhash(tokens_2);
    const std::uint64_t h3 = hashing::simhash::compute_simhash(tokens_3);

    assert(hashing::simhash::hamming_distance(h1, h1) == 0);
    assert(hashing::simhash::hamming_distance(h1, h2) <
           hashing::simhash::hamming_distance(h1, h3));
    assert(std::abs(hashing::simhash::similarity(h1, h1) - 1.0) < 1e-12);
    assert(hashing::simhash::similarity(0ULL, ~0ULL) == 0.0);

    const std::vector<std::pair<std::string, double>> weighted_features = {
        {"apple", 3.0}, {"banana", 1.0}};
    const std::uint64_t weighted_hash =
        hashing::simhash::compute_simhash(weighted_features);
    assert(weighted_hash ==
           hashing::simhash::compute_simhash(weighted_features));

    bool threw_on_empty = false;
    try {
        (void)hashing::simhash::compute_simhash(std::vector<std::string>{});
    } catch (const std::invalid_argument&) {
        threw_on_empty = true;
    }
    assert(threw_on_empty);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
