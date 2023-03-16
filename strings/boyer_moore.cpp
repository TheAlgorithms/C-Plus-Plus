/**
 * @file
 * @brief Boyer-moore's algorithm finding all occurrences of pattern in given
 * text.
 * @author [Stoycho Kyosev](https://github.com/stoychoX)
 */
#include <cassert> /// for assert
#include <cstring> /// for strlen
#include <limits>  /// for CHAR_MAX macro
#include<string>   /// for std::string
#include <vector>  /// for std::vector

#define APLHABET_SIZE CHAR_MAX

/// @brief A structure representing all the data we need to search the
/// preprocessed pattern in text.
struct pattern {
    std::string pat;

    std::vector<size_t> bad_char;
    std::vector<size_t> good_suffix;
};

/// @brief A function that preprocess the good suffix thable
/// @param str The string being preprocessed
/// @param arg The good suffix table
void init_good_suffix(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(str.size() + 1, 0);

    // border_pos[i] - the index of the longest proper suffix of str[i..] which
    // is also a proper prefix.
    std::vector<size_t> border_pos(str.size() + 1, 0);

    int current_char = str.length();

    size_t border_index = str.length() + 1;

    border_pos[current_char] = border_index;

    while (current_char > 0) {
        while (border_index <= str.length() &&
               str[current_char - 1] != str[border_index - 1]) {
            if (arg[border_index] == 0)
                arg[border_index] = border_index - current_char;

            border_index = border_pos[border_index];
        }

        current_char--;
        border_index--;
        border_pos[current_char] = border_index;
    }

    size_t largest_border_index = border_pos[0];

    for (size_t i = 0; i < str.size(); i++) {
        if (arg[i] == 0)
            arg[i] = largest_border_index;

        // If we go pass the largest border we find the next one as we iterate
        if (i == largest_border_index)
            largest_border_index = border_pos[largest_border_index];
    }
}

/// @brief A function that preprocess the bad char table
/// @param str The string being preprocessed
/// @param arg The bad char table
void init_bad_char(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(APLHABET_SIZE, str.length());

    for (size_t i = 0; i < str.length(); i++)
        arg[str[i]] = str.length() - i - 1;
}

/// @brief A function that initializes pattern
/// @param str Text used for initialization
/// @param arg Initialized structure
void init_pattern(const std::string& str, pattern& arg) {
    arg.pat = str;
    init_bad_char(str, arg.bad_char);
    init_good_suffix(str, arg.good_suffix);
}

/// @brief A function that implements Boyer-Moore's algorithm.
/// @param str Text we are seatching in.
/// @param arg pattern structure containing the preprocessed pattern
/// @return (vector of) indexes of the occurrences of pattern in text
std::vector<size_t> search(const std::string& str, const pattern& arg) {
    size_t index_position = arg.pat.size() - 1;
    std::vector<size_t> index_storage;

    while (index_position < str.length()) {
        int index_string = index_position;
        int index_pattern = arg.pat.size() - 1;

        while (index_pattern >= 0 &&
               str[index_string] == arg.pat[index_pattern]) {
            --index_pattern;
            --index_string;
        }

        if (index_pattern < 0) {
            index_storage.push_back(index_position - arg.pat.length() + 1);
            index_position += arg.good_suffix[0];
        } else {
            index_position += std::max(arg.bad_char[str[index_string]],
                                       arg.good_suffix[index_pattern + 1]);
        }
    }

    return index_storage;
}

/// @brief Check if pat is prefix of str
/// @param str pointer to some part of the input text
/// @param pat the searched pattern
/// @param len length of the searched pattern
/// @return true if pat is prefix of str. false otherwise.
bool is_prefix(const char* str, const char* pat, size_t len) {
    if (strlen(str) < len)
        return false;

    for (size_t i = 0; i < len; i++)
        if (str[i] != pat[i])
            return false;

    return true;
}

void and_test(const char* text) {
    pattern ands;
    init_pattern("and", ands);
    std::vector<size_t> indexes = search(text, ands);

    assert(indexes.size() == 2);
    assert(is_prefix(text + indexes[0], "and", 3));
    assert(is_prefix(text + indexes[1], "and", 3));
}

void pat_test(const char* text) {
    pattern pat;
    init_pattern("pat", pat);
    std::vector<size_t> indexes = search(text, pat);

    assert(indexes.size() == 6);

    for (const auto& idx : indexes) {
        assert(is_prefix(text + idx, "pat", 3));
    }
}

void tests() {
    const char* text =
        "When pat Mr. and Mrs. pat Dursley woke up on the dull, gray  \
                            Tuesday our story starts, \
                there was nothing about pat the cloudy sky outside to pat suggest that\
                        strange and \
                    mysterious things would pat soon be happening all pat over the \
                        country.";

    and_test(text);
    pat_test(text);
}

int main() { tests(); }
