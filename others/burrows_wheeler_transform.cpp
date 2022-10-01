/**
 * @file
 * @brief Performs burrows wheeler transformation
 * https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

/**
 * @brief Performs burrows wheeler transformation
 *
 * @param input
 * @return std::tuple<std::string, size_t> (encoded text, index pointing to the
 * original text in the table)
 */
std::tuple<std::string, size_t> burrows_wheeler_transform(
    const std::string &input) {
    std::vector<std::string> rotations;
    rotations.reserve(input.size());

    for (size_t i = 0; i < input.length(); i++) {
        rotations.push_back(input.substr(i) + input.substr(0, i));
    }
    std::sort(rotations.begin(), rotations.end());

    std::string output;
    size_t index = 0;
    for (size_t i = 0; i < rotations.size(); i++) {
        output += rotations[i].back();
        if (rotations[i] == input) {
            index = i;
        }
    }

    return std::make_tuple(output, index);
}

/**
 * @brief Performs the inverse of the burrows wheeler transformation,
 * reconstructing the original string
 *
 * @param input encoded text
 * @param index index pointing to the original text in the table
 * @return std::string original text
 */
std::string burrows_wheeler_inverse(std::string input, size_t index) {
    std::vector<std::pair<size_t, char>> table;
    table.reserve(input.size());

    for (size_t i = 0; i < input.length(); i++) {
        table.emplace_back(i, input[i]);
    }

    std::sort(
        table.begin(), table.end(),
        [](const std::pair<size_t, char> &a, const std::pair<size_t, char> &b) {
            return a.second < b.second;
        });

    std::string output;
    for (size_t i = 0; i < table.size(); i++) {
        output += table[index].second;
        index = table[index].first;
    }

    return output;
}

static void test() {
    std::string input = "CARROT";
    std::tuple<std::string, size_t> transformed =
        burrows_wheeler_transform(input);
    assert(std::get<0>(transformed) == "CTRRAO");
    assert(std::get<1>(transformed) == 1);
    assert(burrows_wheeler_inverse(std::get<0>(transformed),
                                   std::get<1>(transformed)) == input);

    std::string input2 = "THEALGORITHMS";
    transformed = burrows_wheeler_transform(input2);
    assert(std::get<0>(transformed) == "EHLTTRAHGOMSI");
    assert(std::get<1>(transformed) == 11);
    assert(burrows_wheeler_inverse(std::get<0>(transformed),
                                   std::get<1>(transformed)) == input2);
}

int main() {
    test();

    std::cout << "Original: CARROT" << std::endl;
    std::tuple<std::string, size_t> result =
        burrows_wheeler_transform("CARROT");
    std::cout << "Transformed: (" << std::get<0>(result) << ", "
              << std::get<1>(result) << ")" << std::endl;
    std::cout << "Should be: (CTRRAO, 1)" << std::endl;

    std::cout << "Original: THEALGORITHMS" << std::endl;
    result = burrows_wheeler_transform("THEALGORITHMS");
    std::cout << "Transformed: (" << std::get<0>(result) << ", "
              << std::get<1>(result) << ")" << std::endl;
    std::cout << "Should be: (EHLTTRAHGOMSI, 11)" << std::endl;

    std::cout << "Full transformation of CPLUSPLUS" << std::endl;
    result = burrows_wheeler_transform("CPLUSPLUS");
    std::string transformed =
        burrows_wheeler_inverse(std::get<0>(result), std::get<1>(result));
    std::cout << "Full transformation: " << transformed << std::endl;
}
