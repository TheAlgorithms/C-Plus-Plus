/**
 * @file
 * @brief Library to perform arithmatic operations on arbitrarily large
 * numbers.
 * \author [Krishna Vedala](https://github.com/kvedala)
 */

#ifndef MATH_LARGE_NUMBER_H_
#define MATH_LARGE_NUMBER_H_
#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cstring>
#include <iostream>
#include <type_traits>
#include <vector>

/**
 * Store large unsigned numbers as a C++ vector
 * The class provides convenience functions to add a
 * digit to the number, perform multiplication of
 * large number with long unsigned integers.
 **/
class large_number {
 public:
    /**< initializer with value = 1 */
    large_number() { _digits.push_back(1); }

    // /**< initializer from an integer */
    // explicit large_number(uint64_t n) {
    //     uint64_t carry = n;
    //     do {
    //         add_digit(carry % 10);
    //         carry /= 10;
    //     } while (carry != 0);
    // }

    /**< initializer from an integer */
    explicit large_number(int n) {
        int carry = n;
        do {
            add_digit(carry % 10);
            carry /= 10;
        } while (carry != 0);
    }

    /**< initializer from another large_number */
    large_number(const large_number &a) : _digits(a._digits) {}

    /**< initializer from a vector */
    explicit large_number(std::vector<unsigned char> &vec) : _digits(vec) {}

    /**< initializer from a string */
    explicit large_number(char const *number_str) {
        for (size_t i = strlen(number_str); i > 0; i--) {
            char a = number_str[i - 1] - '0';
            if (a >= 0 && a <= 9)
                _digits.push_back(a);
        }
    }

    /**
     * Function to check implementation
     **/
    static bool test() {
        std::cout << "------ Checking `large_number` class implementations\t"
                  << std::endl;
        large_number a(40);
        // 1. test multiplication
        a *= 10;
        if (a != large_number(400)) {
            std::cerr << "\tFailed 1/6 (" << a << "!=400)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 1/6...";
        // 2. test compound addition with integer
        a += 120;
        if (a != large_number(520)) {
            std::cerr << "\tFailed 2/6 (" << a << "!=520)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 2/6...";
        // 3. test compound multiplication again
        a *= 10;
        if (a != large_number(5200)) {
            std::cerr << "\tFailed 3/6 (" << a << "!=5200)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 3/6...";
        // 4. test increment (prefix)
        ++a;
        if (a != large_number(5201)) {
            std::cerr << "\tFailed 4/6 (" << a << "!=5201)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 4/6...";
        // 5. test increment (postfix)
        a++;
        if (a != large_number(5202)) {
            std::cerr << "\tFailed 5/6 (" << a << "!=5202)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 5/6...";
        // 6. test addition with another large number
        a = a + large_number("7000000000000000000000000000000");
        if (a != large_number("7000000000000000000000000005202")) {
            std::cerr << "\tFailed 6/6 (" << a
                      << "!=7000000000000000000000000005202)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 6/6..." << std::endl;
        return true;
    }

    /**
     * add a digit at MSB to the large number
     **/
    void add_digit(unsigned int value) {
        if (value > 9) {
            std::cerr << "digit > 9!!\n";
            exit(EXIT_FAILURE);
        }

        _digits.push_back(value);
    }

    /**
     * Get number of digits in the number
     **/
    size_t num_digits() const { return _digits.size(); }

    /**
     * operator over load to access the
     * i^th digit conveniently and also
     * assign value to it
     **/
    inline unsigned char &operator[](size_t n) { return this->_digits[n]; }

    inline const unsigned char &operator[](size_t n) const {
        return this->_digits[n];
    }

    /**
     * operator overload to compare two numbers
     **/
    friend std::ostream &operator<<(std::ostream &out, const large_number &a) {
        for (size_t i = a.num_digits(); i > 0; i--)
            out << static_cast<int>(a[i - 1]);
        return out;
    }

    /**
     * operator overload to compare two numbers
     **/
    friend bool operator==(large_number const &a, large_number const &b) {
        size_t N = a.num_digits();
        if (N != b.num_digits())
            return false;
        for (size_t i = 0; i < N; i++)
            if (a[i] != b[i])
                return false;
        return true;
    }

    /**
     * operator overload to compare two numbers
     **/
    friend bool operator!=(large_number const &a, large_number const &b) {
        return !(a == b);
    }

    /**
     * operator overload to increment (prefix)
     **/
    large_number &operator++() {
        (*this) += 1;
        return *this;
    }

    /**
     * operator overload to increment (postfix)
     **/
    large_number &operator++(int) {
        static large_number tmp(_digits);
        ++(*this);
        return tmp;
    }

    /**
     * operator overload to add
     **/
    large_number &operator+=(large_number n) {
        // if adding with another large_number
        large_number *b = reinterpret_cast<large_number *>(&n);
        const size_t max_L = std::max(this->num_digits(), b->num_digits());
        unsigned int carry = 0;
        size_t i;
        for (i = 0; i < max_L || carry != 0; i++) {
            if (i < b->num_digits())
                carry += (*b)[i];
            if (i < this->num_digits())
                carry += (*this)[i];
            if (i < this->num_digits())
                (*this)[i] = carry % 10;
            else
                this->add_digit(carry % 10);
            carry /= 10;
        }
        return *this;
    }

    large_number &operator+=(int n) { return (*this) += large_number(n); }
    // large_number &operator+=(uint64_t n) { return (*this) += large_number(n);
    // }

    /**
     * operator overload to perform addition
     **/
    template <class T>
    friend large_number &operator+(const large_number &a, const T &b) {
        static large_number c = a;
        c += b;
        return c;
    }

    /**
     * assignment operator
     **/
    large_number &operator=(const large_number &b) {
        this->_digits = b._digits;
        return *this;
    }

    /**
     * operator overload to increment
     **/
    template <class T>
    large_number &operator*=(const T n) {
        static_assert(std::is_integral<T>::value,
                      "Must be integer addition unsigned integer types.");
        this->multiply(n);
        return *this;
    }

    /**
     * returns i^th digit as an ASCII character
     **/
    char digit_char(size_t i) const {
        return _digits[num_digits() - i - 1] + '0';
    }

 private:
    /**
     * multiply large number with another integer and
     * store the result in the same large number
     **/
    template <class T>
    void multiply(const T n) {
        static_assert(std::is_integral<T>::value,
                      "Can only have integer types.");
        // assert(!(std::is_signed<T>::value)); //, "Implemented only for
        // unsigned integer types.");

        size_t i;
        uint64_t carry = 0, temp;
        for (i = 0; i < this->num_digits(); i++) {
            temp = static_cast<uint64_t>((*this)[i]) * n;
            temp += carry;
            if (temp < 10) {
                carry = 0;
            } else {
                carry = temp / 10;
                temp = temp % 10;
            }
            (*this)[i] = temp;
        }

        while (carry != 0) {
            this->add_digit(carry % 10);
            carry /= 10;
        }
    }

    std::vector<unsigned char>
        _digits; /**< where individual digits are stored */
};

#endif  // MATH_LARGE_NUMBER_H_
