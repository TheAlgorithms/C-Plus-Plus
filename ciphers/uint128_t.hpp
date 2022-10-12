/**
 * @file
 *
 * @details Implementation of 128-bit unsigned integers.
 * @note The implementation can be flagged as not completed. This header is used
 * with enough operations as a part of bigger integer types 256-bit integer.
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */

#include <algorithm>  /// for `std::reverse` and other operations
#include <ostream>    /// for `std::cout` overload
#include <string>     /// for `std::string`
#include <utility>    /// for `std::pair` library

#ifdef _MSC_VER
#include <intrin.h>  /// for _BitScanForward64 and __BitScanReverse64 operation
#endif

#ifndef CIPHERS_UINT128_T_HPP_
#define CIPHERS_UINT128_T_HPP_
class uint128_t;

template <>
struct std::is_integral<uint128_t> : std::true_type {};
template <>
struct std::is_arithmetic<uint128_t> : std::true_type {};
template <>
struct std::is_unsigned<uint128_t> : std::true_type {};

/**
 * @brief Adding two string
 * @details Adds two long integer, only used for printing numbers
 * @param first First integer string
 * @param second Second integer string
 * @returns string denoting the addition of both the strings
 */
std::string add(const std::string &first, const std::string &second) {
    std::string third;
    int16_t sum = 0, carry = 0;
    for (int32_t i = static_cast<int32_t>(first.size()) - 1,
                 j = static_cast<int32_t>(second.size()) - 1;
         i >= 0 || j >= 0; --i, --j) {
        sum = ((i >= 0 ? first[i] - '0' : 0) + (j >= 0 ? second[j] - '0' : 0) +
               carry);
        carry = sum / 10;
        sum %= 10;
        third.push_back(sum + '0');
    }
    if (carry) {
        third.push_back('1');
    }
    std::reverse(third.begin(), third.end());
    return third;
}
/**
 * @class uint128_t
 * @brief class for 128-bit unsigned integer
 */
class uint128_t {
    uint64_t f{}, s{};  /// First and second half of 128 bit number

    /**
     * @brief Get integer from given string.
     * @details Create an integer from a given string
     * @param str integer string, can be hexadecimal (starting on 0x... or
     * number)
     * @returns void
     */
    void __get_integer_from_string(const std::string &str) {
        this->f = this->s = 0;
        if (str.size() > 1 && str[1] == 'x') {  // if hexadecimal
            for (auto i = 2; i < str.size(); ++i) {
                *this *= 16LL;
                if (str[i] >= '0' && str[i] <= '9') {
                    *this += (str[i] - '0');
                } else if (str[i] >= 'A' && str[i] <= 'F') {
                    *this += (str[i] - 'A' + 10);
                } else if (str[i] >= 'a' && str[i] <= 'f') {
                    *this += (str[i] - 'a' + 10);
                }
            }
        } else {  // if decimal
            for (auto &x : str) {
                *this *= 10LL;
                *this += (x - '0');
            }
        }
    }

 public:
    uint128_t() = default;

    /**
     * @brief Parameterized constructor
     * @tparam T integral type
     * @param low lower part 8-bit unisgned integer
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    explicit uint128_t(T low) : s(low) {}

    /**
     * @brief Parameterized constructor
     * @param str Integer string (hexadecimal starting with 0x.. or decimal)
     */
    explicit uint128_t(const std::string &str) {
        __get_integer_from_string(str);
    }

    /**
     * @brief Parameterized constructor
     * @param high higher part 64-bit unsigned integer
     * @param low lower part 64-bit unsigned integer
     */
    uint128_t(const uint64_t high, const uint64_t low) : f(high), s(low) {}

    /**
     * @brief Copy constructor
     * @param num 128-bit unsigned integer
     */
    uint128_t(const uint128_t &num) = default;

    /**
     * @brief Move constructor
     * @param num 128-bit unsigned integer
     */
    uint128_t(uint128_t &&num) noexcept : f(num.f), s(num.s) {}

    /**
     * @brief Destructor for uint128_t
     */
    ~uint128_t() = default;

    /**
     * @brief Leading zeroes in binary
     * @details Calculates leading zeros in 128-bit integer
     * @returns Integer denoting leading zeroes
     */
    inline uint32_t _lez() {
#ifndef _MSC_VER
        if (f) {
            return __builtin_clzll(f);
        }
        return 64 + __builtin_clzll(s);
#else
        unsigned long r = 0;
        _BitScanForward64(&r, f);
        if (r == 64) {
            unsigned long l = 0;
            _BitScanForward64(&l, s);
            return 64 + l;
        }
        return r;
#endif
    }

    /**
     * @brief Trailing zeroes in binary
     * @details Calculates leading zeros in 128-bit integer
     * @returns Integer denoting Trailing zeroes
     */
    inline uint32_t _trz() {
#ifndef _MSC_VER
        if (f) {
            return __builtin_ctzll(f);
        }
        return 64 + __builtin_ctzll(s);
#else
        unsigned long r = 0;
        _BitScanReverse64(&r, s);
        if (r == 64) {
            unsigned long l = 0;
            _BitScanReverse64(&l, f);
            return 64 + l;
        }
        return r;
#endif
    }

    /**
     * @brief casting operator to boolean value
     * @returns true if value of this is non-zero, else false
     */
    inline explicit operator bool() const { return (f || s); }

    /**
     * @brief casting operator to any integer valu
     * @tparam T any integer type
     * @returns integer value casted to mentioned type
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline explicit operator T() const {
        return static_cast<T>(s);
    }

    /**
     * @brief returns lower 64-bit integer part
     * @returns returns lower 64-bit integer part
     */
    inline uint64_t lower() const { return s; }

    /**
     * @brief returns upper 64-bit integer part
     * @returns returns upper 64-bit integer part
     */
    inline uint64_t upper() const { return f; }

    /**
     * @brief operator = for other types
     * @tparam T denoting any integer type
     * @param p an integer to assign it's value
     * @returns this pointer with it's value equal to `p`
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator=(const T &p) {
        this->s = p;
        return *this;
    }

    /**
     * @brief operator = for type string
     * @param p a string to assign it's value to equivalent integer
     * @returns this pointer with it's value equal to `p`
     */
    inline uint128_t &operator=(const std::string &p) {
        this->__get_integer_from_string(p);
        return *this;
    }

    /**
     * @brief operator = for uint128_t
     * @param p an 128-bit integer to assign it's value
     * @returns this pointer with it's value equal to `p`
     */
    inline uint128_t &operator=(const uint128_t &p) = default;

    /**
     * @brief Move assignment operator
     */
    inline uint128_t &operator=(uint128_t &&p) = default;

    /**
     * @brief operator + for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns addition of this and p, returning uint128_t integer
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator+(const T p) {
        return uint128_t(f + (p + s < s), p + s);
    }

    /**
     * @brief operator + for uint128_t and other integer types.
     * @param p 128-bit unsigned integer
     * @returns addition of this and p, returning uint128_t integer
     */
    inline uint128_t operator+(const uint128_t &p) {
        return uint128_t(f + (p.s + s < s) + p.f, p.s + s);
    }

    /**
     * @brief operator += for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns addition of this and p, returning this
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator+=(const T p) {
        bool app = p + s < s;
        this->f += app;
        this->s += p;
        return *this;
    }

    /**
     * @brief operator += for uint128_t
     * @param p 128-bit unsigned integer
     * @returns addition of this and p, returning this
     */
    uint128_t &operator+=(const uint128_t &p) {
        bool app = p.s + s < s;
        f = f + app + p.f;
        s = p.s + s;
        return *this;
    }

    /**
     * @brief pre-increment operator
     * @returns incremented value of this.
     */
    inline uint128_t &operator++() {
        *this += 1;
        return *this;
    }

    /**
     * @brief post-increment operator
     * @returns incremented value of this.
     */
    inline uint128_t operator++(int) {
        ++*this;
        return *this;
    }

    /**
     * @brief operator - for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns subtraction of this and p, returning uint128_t integer
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator-(const T &p) {
        bool app = p > s;
        return uint128_t(f - app, s - p);
    }

    /**
     * @brief operator - for uint128_t
     * @param p a type of integer variable
     * @returns subtraction of this and p, returning uint128_t integer
     */
    inline uint128_t operator-(const uint128_t &p) {
        bool app = p.s > s;
        return uint128_t(f - p.f - app, s - p.s);
    }

    /**
     * @brief operator - using twos complement
     * @returns 2's complement of this.
     */
    inline uint128_t operator-() { return ~*this + uint128_t(1); }

    /**
     * @brief operator -- (pre-decrement)
     * @returns decremented value of this
     */
    inline uint128_t &operator--() {
        *this -= 1;
        return *this;
    }

    /**
     * @brief operator -- (post-decrement)
     * @returns decremented value of this
     */
    inline uint128_t operator--(int p) {
        --*this;
        return *this;
    }

    /**
     * @brief operator -= for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns subtraction of this and p, returning this
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint128_t &operator-=(const T &p) {
        bool app = p > s;
        f -= app;
        s -= p;
        return *this;
    }

    /**
     * @brief operator -= for uint128_t
     * @param p 128-bit unsigned integer
     * @returns subtraction of this and p, returning this
     */
    uint128_t &operator-=(const uint128_t &p) {
        bool app = p.s > s;
        f = f - p.f - app;
        s = s - p.s;
        return *this;
    }

    /**
     * @brief operator * for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns multiplication of this and p, returning uint128_t integer
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator*(const T p) {
        return *this * uint128_t(p);
    }

    /**
     * @brief operator * for uint128_t and other integer types.
     * @param p 128-bit unsigned integer
     * @returns multiplication of this and p, returning uint128_t integer
     */
    uint128_t operator*(const uint128_t &p) {
        uint64_t f_first = s >> 32, f_second = s & 0xFFFFFFFF,
                 s_first = p.s >> 32, s_second = p.s & 0xFFFFFFFF;
        uint64_t fi = f_first * s_first, se = f_first * s_second,
                 th = s_first * f_second, fo = s_second * f_second;
        uint64_t tmp = ((se & 0xFFFFFFFF) << 32), tmp2 = (th & 0xFFFFFFFF)
                                                         << 32;
        int cc = (tmp + tmp2 < tmp);
        tmp += tmp2;
        cc += (tmp + fo < tmp);
        uint64_t carry = fi + (se >> 32) + (th >> 32);
        return uint128_t(this->f * p.s + this->s * p.f + carry + cc, tmp + fo);
    }

    /**
     * @brief operator *= for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns multiplication of this and p, returning this
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator*=(const T p) {
        *this *= uint128_t(p);
        return *this;
    }

    /**
     * @brief operator *= for uint128_t and other integer types.
     * @param p 128-bit unsigned integer
     * @returns multiplication of this and p, returning this
     */
    uint128_t &operator*=(const uint128_t &p) {
        uint64_t f_first = s >> 32, f_second = s & 0xFFFFFFFF,
                 s_first = p.s >> 32, s_second = p.s & 0xFFFFFFFF;
        uint64_t fi = f_first * s_first, se = f_first * s_second,
                 th = s_first * f_second, fo = s_second * f_second;
        uint64_t tmp = (se << 32), tmp2 = (th << 32);
        int cc = (tmp + tmp2 < tmp);
        tmp += tmp2;
        cc += (tmp + fo < tmp);
        uint64_t carry = fi + (se >> 32) + (th >> 32);
        f = this->f * p.s + this->s * p.f + carry + cc;
        s = tmp + fo;
        return *this;
    }

    /**
     * @brief divide function for uint128_t and other integer types.
     * @details divide this value and
     * @param p 128-bit unsigned integer
     * @returns pair denoting quotient and remainder.
     */
    std::pair<uint128_t, uint128_t> divide(const uint128_t &p) {
        if (*this < p) {  // if this is less than divisor
            return {uint128_t(0), *this};
        } else if (*this == p) {  // if this is equal to divisor
            return {uint128_t(1), uint128_t(0)};
        }
        uint128_t tmp = p, tmp2 = *this;
        uint16_t left = tmp._lez() - _lez();
        tmp <<= left;
        uint128_t quotient(0);
        uint128_t zero(0);
        while (tmp2 >= p) {
            uint16_t shf = tmp2._lez() - tmp._lez();
            if (shf) {
                tmp >>= shf;
                quotient <<= shf;
                left -= shf;
            }
            if (tmp2 < tmp) {
                tmp >>= 1;
                quotient <<= 1;
                --left;
            }
            tmp2 -= tmp;
            ++quotient;
        }
        return {quotient << left, tmp2};
    }

    /**
     * @brief operator / for uint128_t and other integer types.
     * @param p 128-bit unsigned integer
     * @returns unsigned 128-bit quotient.
     */
    inline uint128_t operator/(const uint128_t &p) { return divide(p).first; }

    /**
     * @brief operator / for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns unsigned 128-bit quotient.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator/(const T p) {
        uint128_t tmp = *this;
        tmp /= uint128_t(0, p);
        return tmp;
    }

    /**
     * @brief operator /= for uint128_t
     * @param p 128-bit unsigned integer
     * @returns this set as unsigned 128-bit quotient.
     */
    inline uint128_t &operator/=(const uint128_t &p) {
        *this = divide(p).first;
        return *this;
    }

    /**
     * @brief operator /= for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns this set as unsigned 128-bit quotient.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator/=(const T p) {
        *this /= uint128_t(0, p);
        return *this;
    }

    /**
     * @brief operator % for uint128_t
     * @param p 128-bit unsigned integer
     * @returns unsigned 128-bit remainder.
     */
    inline uint128_t operator%(const uint128_t &p) { return divide(p).second; }

    /**
     * @brief operator % for uint128_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns unsigned 128-bit remainder.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator%(const T &p) {
        return *this % uint128_t(p);
    }

    /**
     * @brief operator %= for uint128_t
     * @param p 128-bit unsigned integer
     * @returns this set as unsigned 128-bit remainder.
     */
    inline uint128_t &operator%=(const uint128_t &p) {
        *this = divide(p).second;
        return *this;
    }

    /**
     * @brief operator %= for uint128_t
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns this set as unsigned 128-bit remainder.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator%=(const T &p) {
        *this %= uint128_t(p);
        return *this;
    }

    /**
     * @brief operator < for uint128_t
     * @param other number to be compared with this
     * @returns true if this is less than other, else false
     */
    inline bool operator<(const uint128_t &other) {
        return f < other.f || (f == other.f && s < other.s);
    }

    /**
     * @brief operator <= for uint128_t
     * @param other number to be compared with this
     * @returns true if this is less than or equal to other, else false
     */
    inline bool operator<=(const uint128_t &other) {
        return f < other.f || (f == other.f && s <= other.s);
    }

    /**
     * @brief operator > for uint128_t
     * @param other number to be compared with this
     * @returns true if this is greater than other, else false
     */
    inline bool operator>(const uint128_t &other) {
        return f > other.f || (f == other.f && s > other.s);
    }

    /**
     * @brief operator >= for uint128_t
     * @param other number to be compared with this
     * @returns true if this is greater than or equal than other, else false
     */
    inline bool operator>=(const uint128_t &other) {
        return (f > other.f) || (f == other.f && s >= other.s);
    }

    /**
     * @brief operator == for uint128_t
     * @param other number to be compared with this
     * @returns true if this is equal than other, else false
     */
    inline bool operator==(const uint128_t &other) {
        return f == other.f && s == other.s;
    }

    /**
     * @brief operator != for uint128_t
     * @param other number to be compared with this
     * @returns true if this is not equal than other, else false
     */
    inline bool operator!=(const uint128_t &other) {
        return f != other.f || s != other.s;
    }

    /**
     * @brief operator ! for uint128_t
     * @returns true if this has zero value, else false
     */
    inline bool operator!() { return !f && !s; }

    /**
     * @brief operator && for uint128_t
     * @param b number to be compared with this
     * @returns true if both of the values are not zero, else false
     */
    inline bool operator&&(const uint128_t &b) {
        return (s || f) && (b.s || b.f);
    }

    /**
     * @brief operator || for uint128_t
     * @param b number to be compared with this
     * @returns true if one of the values are not zero, else false
     */
    inline bool operator||(const uint128_t &b) {
        return (s || f) || (b.s || b.f);
    }

    /**
     * @brief operator () for uint128_t
     * @returns true if this value is non-zero, else false
     */
    inline bool operator()() { return s || f; }

    /**
     * @brief operator < for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is less than other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator<(const T other) {
        return *this < uint128_t(other);
    }

    /**
     * @brief operator <= for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is less than or equal to other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator<=(const T other) {
        return *this <= uint128_t(other);
    }

    /**
     * @brief operator > for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is greater than other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator>(const T other) {
        return *this > uint128_t(other);
    }

    /**
     * @brief operator >= for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is greater than or equal other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator>=(const T other) {
        return *this >= uint128_t(other);
    }

    /**
     * @brief operator == for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is equal to other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator==(const T other) {
        return *this == uint128_t(other);
    }

    /**
     * @brief operator != for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is not equal to other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator!=(const T other) {
        return *this != uint128_t(other);
    }

    /**
     * @brief operator && for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is both values are non-zero, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator&&(const T b) {
        return (f || s) && b;
    }

    /**
     * @brief operator || for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is either one of the values are non-zero, else
     * false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator||(const T b) {
        return (f || s) || b;
    }

    /**
     * @brief operator ~ for uint128_t
     * @returns 1's complement of this number
     */
    uint128_t operator~() { return uint128_t(~this->f, ~this->s); }

    /**
     * @brief operator << for uint128_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns value of this shifted by p to left
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint128_t operator<<(const T p) {
        if (!p) {
            return uint128_t(f, s);
        } else if (p >= 64 && p <= 128) {
            return uint128_t((this->s << (p - 64)), 0);
        } else if (p < 64 && p > 0) {
            return uint128_t((this->f << p) + ((this->s >> (64 - p))),
                             this->s << p);
        }
        return uint128_t(0);
    }

    /**
     * @brief operator <<= for uint128_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns this shifted by p to left
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint128_t &operator<<=(const T p) {
        if (p) {
            if (p >= 64 && p <= 128) {
                this->f = (this->s << (p - 64));
                this->s = 0;
            } else {
                f = ((this->f << p) + (this->s >> (64 - p)));
                s = (this->s << p);
            }
        }
        return *this;
    }

    /**
     * @brief operator >> for uint128_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns value of this shifted by p to right
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint128_t operator>>(const T p) {
        if (!p) {
            return uint128_t(this->f, this->s);
        } else if (p >= 64 && p <= 128) {
            return uint128_t(0, (this->f >> (p - 64)));
        } else if (p < 64 && p > 0) {
            return uint128_t((this->f >> p),
                             (this->s >> p) + (this->f << (64 - p)));
        }
        return uint128_t(0);
    }

    /**
     * @brief operator >>= for uint128_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns this shifted by p to right
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint128_t &operator>>=(const T p) {
        if (p) {
            if (p >= 64) {
                f = 0;
                s = (this->f >> (p - 64));
            } else {
                s = (this->s >> p) + (this->f << (64 - p));
                f = (this->f >> p);
            }
        }
        return *this;
    }

    /**
     * @brief operator & for uint128_t (bitwise operator)
     * @param p number to be operated
     * @returns value of this & p (& is bit-wise operator)
     */
    inline uint128_t operator&(const uint128_t &p) {
        return uint128_t(this->f & p.f, this->s & p.s);
    }

    /**
     * @brief operator & for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns value of this & p (& is bit-wise operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint128_t operator&(const T p) {
        uint128_t tmp = *this;
        return tmp & uint128_t(p);
    }

    /**
     * @brief operator &= for uint128_t (bitwise operator)
     * @param p number to be operated
     * @returns this = this & p (& is bit-wise operator)
     */
    uint128_t &operator&=(const uint128_t &p) {
        this->f &= p.f;
        this->s &= p.s;
        return *this;
    }

    /**
     * @brief operator &= for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns this = this & p (& is bit-wise operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint128_t &operator&=(const T p) {
        *this &= uint128_t(p);
        return *this;
    }

    /**
     * @brief operator | for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns value of this | p (| is bit-wise operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator|(const T p) {
        return uint128_t(p | s);
    }

    /**
     * @brief operator | for uint128_t (bitwise operator)
     * @param p number to be operated
     * @returns value of this | p (| is bit-wise OR operator)
     */
    inline uint128_t operator|(const uint128_t &p) {
        return uint128_t(this->f | p.f, this->s | p.s);
    }

    /**
     * @brief operator |= for uint128_t (bitwise operator)
     * @param p number to be operated
     * @returns this = this | p (| is bit-wise OR operator)
     */
    uint128_t &operator|=(const uint128_t &p) {
        f |= p.f;
        s |= p.s;
        return *this;
    }

    /**
     * @brief operator |= for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns this = this | p (| is bit-wise OR operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator|=(const T p) {
        s |= p.s;
        return *this;
    }

    /**
     * @brief operator ^ for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns value of this ^ p (^ is bit-wise XOR operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator^(const T p) {
        return uint128_t(this->f, this->s ^ p);
    }

    /**
     * @brief operator ^ for uint128_t (bitwise operator)
     * @param p number to be operated
     * @returns value of this ^ p (^ is bit-wise XOR operator)
     */
    inline uint128_t operator^(const uint128_t &p) {
        return uint128_t(this->f ^ p.f, this->s ^ p.s);
    }

    /**
     * @brief operator ^= for uint128_t (bitwise operator)
     * @param p number to be operated
     * @returns this = this ^ p (^ is bit-wise XOR operator)
     */
    uint128_t &operator^=(const uint128_t &p) {
        f ^= p.f;
        s ^= p.s;
        return *this;
    }

    /**
     * @brief operator ^= for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns this = this ^ p (^ is bit-wise XOR operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator^=(const T &p) {
        s ^= p;
        return *this;
    }

    /**
     * @brief operator << for printing uint128_t integer
     * @details Prints the uint128_t integer in decimal form
     * @note Note that this operator is costly since it uses strings to print
     * the value
     * @param op ostream object
     * @param p 128-bit integer
     * @returns op, ostream object.
     */
    friend std::ostream &operator<<(std::ostream &op, const uint128_t &p) {
        if (!p.f) {
            op << p.s;
        } else {
            std::string out = "0", p_2 = "1";
            for (int i = 0; i < 64; ++i) {
                if (p.s & (1LL << i)) {
                    out = add(out, p_2);
                }
                p_2 = add(p_2, p_2);
            }
            for (int i = 0; i < 64; ++i) {
                if (p.f & (1LL << i)) {
                    out = add(out, p_2);
                }
                p_2 = add(p_2, p_2);
            }
            op << out;
        }
        return op;
    }
};

// Arithmetic operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator+(const T &p, const uint128_t &q) {
    return uint128_t(p) + q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator-(const T p, const uint128_t &q) {
    return uint128_t(p) - q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator*(const T p, const uint128_t &q) {
    return uint128_t(p) * q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator/(const T p, const uint128_t &q) {
    return uint128_t(p) / q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator%(const T p, const uint128_t &q) {
    return uint128_t(p) % q;
}

// Bitwise operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator&(const T &p, const uint128_t &q) {
    return uint128_t(p) & q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator|(const T p, const uint128_t &q) {
    return uint128_t(p) | q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator^(const T p, const uint128_t &q) {
    return uint128_t(p) ^ q;
}

// Boolean operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator&&(const T p, const uint128_t &q) {
    return uint128_t(p) && q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator||(const T p, const uint128_t &q) {
    return uint128_t(p) || q;
}

// Comparison operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator==(const T p, const uint128_t &q) {
    return uint128_t(p) == q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator!=(const T p, const uint128_t &q) {
    return uint128_t(p) != q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<(const T p, const uint128_t &q) {
    return uint128_t(p) < q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<=(const T p, const uint128_t &q) {
    return uint128_t(p) <= q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>(const T p, const uint128_t &q) {
    return uint128_t(p) > q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>=(const T p, const uint128_t &q) {
    return uint128_t(p) >= q;
}

#endif  // CIPHERS_UINT128_T_HPP_
