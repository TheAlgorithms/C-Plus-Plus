/**
 * @file
 *
 * @details Implementation of 256-bit unsigned integers.
 * @note The implementation can be flagged as not completed. This header is used
 * with enough operations to demonstrate the usage of ECDH (Elliptic Curve
 * Diffie-Hellman) Key exchange.
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */
#include <string>   /// for `std::string`
#include <utility>  /// for `std::pair` library

#include "uint128_t.hpp"  /// for uint128_t integer

#ifndef CIPHERS_UINT256_T_HPP_
#define CIPHERS_UINT256_T_HPP_

class uint256_t;

template <>
struct std::is_integral<uint256_t> : std::true_type {};

template <>
struct std::is_arithmetic<uint256_t> : std::true_type {};

template <>
struct std::is_unsigned<uint256_t> : std::true_type {};

/**
 * @class uint256_t
 * @brief class for 256-bit unsigned integer
 */
class uint256_t {
    uint128_t f{}, s{};  /// First and second half of 256 bit number

    /**
     * @brief Get integer from given string.
     * @details Create an integer from a given string
     * @param str integer string, can be hexadecimal (starting on 0x... or
     * number)
     * @returns void
     */
    void __get_integer_from_string(const std::string &str) {
        this->f = this->s = uint128_t(0);
        if (str.size() > 1 && str[1] == 'x') {
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
        } else {
            for (auto &x : str) {
                *this *= 10LL;
                *this += (x - '0');
            }
        }
    }

 public:
    // Constructors
    uint256_t() = default;

    /**
     * @brief Parameterized constructor
     * @tparam T template for integer types
     * @param low Integer denoting lower 128-bits
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    explicit uint256_t(T low) : s(low), f(0) {}

    /**
     * @brief Parameterized constructor
     * @param str Integer string (hexadecimal starting with 0x.. or decimal)
     */
    explicit uint256_t(const std::string &str) {
        __get_integer_from_string(str);
    }

    /**
     * @brief Copy constructor
     * @param num 256-bit unsigned integer
     */
    uint256_t(const uint256_t &num) = default;

    /**
     * @brief Move constructor
     * @param num 256-bit unsigned integer
     */
    uint256_t(uint256_t &&num) noexcept
        : f(std::move(num.f)), s(std::move(num.s)) {}

    /**
     * @brief Parameterized constructor
     * @param high higher part 128-bit unsigned integer
     * @param low lower part 128-bit unsigned integer
     */
    uint256_t(uint128_t high, uint128_t low)
        : f(std::move(high)), s(std::move(low)) {}

    /**
     * @brief Parameterized constructor
     * @param high higher part 64-bit unsigned integer
     * @param low lower part 64-bit unsigned integer
     */
    uint256_t(const uint64_t high, const uint64_t low) : f(high), s(low) {}

    /**
     * @brief Destructor for uint256_t
     */
    ~uint256_t() = default;

    /**
     * @brief Leading zeroes in binary
     * @details Calculates leading zeros in 256-bit integer
     * @returns Integer denoting leading zeroes
     */
    inline uint32_t _lez() {
        if (f) {
            return f._lez();
        }
        return 128 + s._lez();
    }

    /**
     * @brief Trailing zeroes in binary
     * @details Calculates leading zeros in 256-bit integer
     * @returns Integer denoting Trailing zeroes
     */
    inline uint32_t _trz() {
        if (s) {
            return s._trz();
        }
        return 128 + f._trz();
    }

    /**
     * @brief casting operator to boolean value
     * @returns true if value of this is non-zero, else false
     */
    inline explicit operator bool() const { return f || s; }

    /**
     * @brief casting operator to any integer value
     * @tparam T any integer type
     * @returns integer value casted to mentioned type
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline explicit operator T() const {
        return static_cast<T>(s);
    }

    /**
     * @brief casting operator to uint128_t
     * @returns returns lower 128-bit integer part
     */
    inline explicit operator uint128_t() const { return s; }

    /**
     * @brief returns lower 128-bit integer part
     * @returns returns lower 128-bit integer part
     */
    inline uint128_t lower() const { return s; }

    /**
     * @brief returns upper 128-bit integer part
     * @returns returns upper 128-bit integer part
     */
    inline uint128_t upper() const { return f; }

    /**
     * @brief operator = for uint256_t
     * @param p an 256-bit integer to assign it's value
     * @returns this pointer with it's value equal to `p`
     */
    inline uint256_t &operator=(const uint256_t &p) = default;

    /**
     * @brief operator = for other types
     * @tparam T denoting any integer type
     * @param p an integer to assign it's value
     * @returns this pointer with it's value equal to `p`
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator=(const T &p) {
        this->s = p;
        return *this;
    }

    /**
     * @brief operator = for type string
     * @param p a string to assign it's value to equivalent integer
     * @returns this pointer with it's value equal to `p`
     */
    inline uint256_t &operator=(const std::string &p) {
        __get_integer_from_string(p);
        return *this;
    }

    /**
     * @brief Move assignment operator
     */
    inline uint256_t &operator=(uint256_t &&p) = default;

    /**
     * @brief operator + for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns addition of this and p, returning uint256_t integer
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator+(const T &p) {
        bool app = s + p < s;
        return uint256_t(f + app, s + p);
    }

    /**
     * @brief operator + for uint256_t and other integer types.
     * @param p 256-bit unsigned integer
     * @returns addition of this and p, returning uint256_t integer
     */
    inline uint256_t operator+(const uint256_t &p) {
        bool app = (s + p.s < s);
        return {f + app + p.f, s + p.s};
    }

    /**
     * @brief operator += for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns addition of this and p, returning this
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator+=(const T &p) {
        bool app = (p + s < s);
        this->f += app;
        this->s += p;
        return *this;
    }

    /**
     * @brief operator += for uint256_t
     * @param p 256-bit unsigned integer
     * @returns addition of this and p, returning this
     */
    inline uint256_t &operator+=(const uint256_t &p) {
        bool app = (s + p.s < s);
        f = f + app + p.f;
        s = s + p.s;
        return *this;
    }

    /**
     * @brief pre-increment operator
     * @returns incremented value of this.
     */
    inline uint256_t &operator++() {
        *this += 1;
        return *this;
    }

    /**
     * @brief post-increment operator
     * @returns incremented value of this.
     */
    inline uint256_t operator++(int) {
        ++*this;
        return *this;
    }

    /**
     * @brief operator - for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns subtraction of this and p, returning uint256_t integer
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator-(const T &p) {
        bool app = (p > s);
        return uint256_t(f - app, s - p);
    }

    /**
     * @brief operator - for uint256_t
     * @param p a type of integer variable
     * @returns subtraction of this and p, returning uint256_t integer
     */
    inline uint256_t operator-(const uint256_t &p) {
        bool app = s < p.s;
        return {f - p.f - app, s - p.s};
    }

    /**
     * @brief operator - using twos complement
     * @returns 2's complement of this.
     */
    inline uint256_t operator-() { return ~*this + uint256_t(1); }

    /**
     * @brief operator -- (pre-decrement)
     * @returns decremented value of this
     */
    inline uint256_t &operator--() {
        *this -= 1;
        return *this;
    }

    /**
     * @brief operator -- (post-decrement)
     * @returns decremented value of this
     */
    inline uint256_t operator--(int p) {
        --*this;
        return *this;
    }

    /**
     * @brief operator -= for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns subtraction of this and p, returning this
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator-=(const T p) {
        bool app = (p > s);
        f = f - app;
        s = s - p;
        return *this;
    }

    /**
     * @brief operator -= for uint256_t
     * @param p 256-bit unsigned integer
     * @returns subtraction of this and p, returning this
     */
    inline uint256_t &operator-=(const uint256_t &p) {
        bool app = s < p.s;
        f = f - app - p.f;
        s = s - p.s;
        return *this;
    }

    /**
     * @brief operator * for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns multiplication of this and p, returning uint256_t integer
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator*(const T &p) {
        return *this * uint256_t(p);
    }

    /**
     * @brief operator * for uint256_t and other integer types.
     * @param p 256-bit unsigned integer
     * @returns multiplication of this and p, returning uint256_t integer
     */
    uint256_t operator*(const uint256_t &p) {
        uint128_t f_first(s.upper()), f_second(s.lower()), s_first(p.s.upper()),
            s_second(p.s.lower());
        uint128_t fi = f_first * s_first, se = f_first * s_second,
                  th = s_first * f_second, fo = s_second * f_second;
        uint128_t tmp = se << 64, tmp2 = th << 64;
        int cc = (tmp + tmp2 < tmp);
        tmp += tmp2;
        cc += (tmp + fo < tmp);
        return {f * p.s + s * p.f + fi + se.upper() + th.upper() + cc,
                tmp + fo};
    }

    /**
     * @brief operator *= for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns multiplication of this and p, returning this
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator*=(const T &p) {
        return (*this *= uint256_t(p));
    }

    /**
     * @brief operator *= for uint256_t and other integer types.
     * @param p 256-bit unsigned integer
     * @returns multiplication of this and p, returning this
     */
    uint256_t &operator*=(const uint256_t &p) {
        uint128_t f_first(s.upper()), f_second(s.lower()), s_first(p.s.upper()),
            s_second(p.s.lower());
        uint128_t fi = f_first * s_first, se = f_first * s_second,
                  th = s_first * f_second, fo = s_second * f_second;
        uint128_t tmp = se << 64, tmp2 = th << 64;
        int cc = (tmp + tmp2 < tmp);
        tmp += tmp2;
        cc += (tmp + fo < tmp);
        f = f * p.s + s * p.f + fi + se.upper() + th.upper() + cc;
        s = tmp + fo;
        return *this;
    }

    /**
     * @brief divide function for uint256_t and other integer types.
     * @details divide this value and
     * @param p 256-bit unsigned integer
     * @returns pair denoting quotient and remainder.
     */
    std::pair<uint256_t, uint256_t> divide(const uint256_t &p) {
        if (*this < p) {  // if this is less than divisor
            return {uint256_t(0), *this};
        } else if (*this == p) {  // if this is equal to divisor
            return {uint256_t(1), uint256_t(0)};
        }
        uint256_t tmp = p, tmp2 = *this;
        uint16_t left = tmp._lez() - _lez();
        tmp <<= left;
        uint256_t quotient(0);
        uint256_t zero(0);
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
     * @brief operator / for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns unsigned 256-bit quotient.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator/(const T &p) {
        uint256_t tmp = *this;
        tmp /= uint256_t(p);
        return tmp;
    }

    /**
     * @brief operator / for uint256_t and other integer types.
     * @param p 256-bit unsigned integer
     * @returns unsigned 256-bit quotient.
     */
    inline uint256_t operator/(const uint256_t &p) { return divide(p).first; }

    /**
     * @brief operator /= for uint256_t
     * @param p 256-bit unsigned integer
     * @returns this set as unsigned 256-bit quotient.
     */
    inline uint256_t &operator/=(const uint256_t &p) {
        *this = divide(p).first;
        return *this;
    }

    /**
     * @brief operator /= for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns this set as unsigned 256-bit quotient.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator/=(const T &p) {
        *this /= uint256_t(p);
        return *this;
    }

    /**
     * @brief operator % for uint256_t
     * @param p 256-bit unsigned integer
     * @returns unsigned 256-bit remainder.
     */
    inline uint256_t operator%(const uint256_t &p) { return divide(p).second; }

    /**
     * @brief operator % for uint256_t and other integer types.
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns unsigned 256-bit remainder.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator%(const T &p) {
        uint256_t tmp = *this;
        tmp %= uint256_t(p);
        return tmp;
    }

    /**
     * @brief operator %= for uint256_t
     * @param p 256-bit unsigned integer
     * @returns this set as unsigned 256-bit remainder.
     */
    inline uint256_t &operator%=(const uint256_t &p) {
        *this = divide(p).second;
        return *this;
    }

    /**
     * @brief operator %= for uint256_t
     * @tparam T denoting integral type
     * @param p a type of integer variable
     * @returns this set as unsigned 256-bit remainder.
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator%=(const T &p) {
        *this %= uint256_t(p);
        return *this;
    }

    /**
     * @brief operator < for uint256_t
     * @param other number to be compared with this
     * @returns true if this is less than other, else false
     */
    inline bool operator<(const uint256_t &other) {
        return f < other.f || (f == other.f && s < other.s);
    }

    /**
     * @brief operator <= for uint256_t
     * @param other number to be compared with this
     * @returns true if this is less than or equal to other, else false
     */
    inline bool operator<=(const uint256_t &other) {
        return f < other.f || (f == other.f && s <= other.s);
    }

    /**
     * @brief operator > for uint256_t
     * @param other number to be compared with this
     * @returns true if this is greater than other, else false
     */
    inline bool operator>(const uint256_t &other) {
        return f > other.f || (f == other.f && s > other.s);
    }

    /**
     * @brief operator >= for uint256_t
     * @param other number to be compared with this
     * @returns true if this is greater than or equal than other, else false
     */
    inline bool operator>=(const uint256_t &other) {
        return (f > other.f) || (f == other.f && s >= other.s);
    }

    /**
     * @brief operator == for uint256_t
     * @param other number to be compared with this
     * @returns true if this is equal than other, else false
     */
    inline bool operator==(const uint256_t &other) {
        return f == other.f && s == other.s;
    }

    /**
     * @brief operator != for uint256_t
     * @param other number to be compared with this
     * @returns true if this is not equal than other, else false
     */
    inline bool operator!=(const uint256_t &other) {
        return !((*this) == other);
    }

    /**
     * @brief operator ! for uint256_t
     * @returns true if this has zero value, else false
     */
    inline bool operator!() { return !f && !s; }

    /**
     * @brief operator && for uint256_t
     * @param b number to be compared with this
     * @returns true if both of the values are not zero, else false
     */
    inline bool operator&&(const uint256_t &b) {
        return (s || f) && (b.s || b.f);
    }

    /**
     * @brief operator || for uint256_t
     * @param b number to be compared with this
     * @returns true if one of the values are not zero, else false
     */
    inline bool operator||(const uint256_t &b) {
        return (s || f) || (b.s || b.f);
    }

    /**
     * @brief operator () for uint256_t
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
    bool operator<(const T &other) {
        return *this < uint256_t(other);
    }

    /**
     * @brief operator <= for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is less than or equal to other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    bool operator<=(const T &other) {
        return *this <= uint256_t(other);
    }

    /**
     * @brief operator > for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is greater than other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    bool operator>(const T &other) {
        return *this > uint256_t(other);
    }

    /**
     * @brief operator >= for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is greater than or equal other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    bool operator>=(const T &other) {
        return *this >= uint256_t(other);
    }

    /**
     * @brief operator == for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is equal to other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    bool operator==(const T &other) {
        return *this == uint256_t(other);
    }

    /**
     * @brief operator != for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is not equal to other, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    bool operator!=(const T &other) {
        return *this != uint256_t(other);
    }

    /**
     * @brief operator && for other types
     * @tparam T integral type
     * @param other number to be compared with this
     * @returns true if this is both values are non-zero, else false
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline bool operator&&(const T &b) {
        return (s || f) && (b);
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
    inline bool operator||(const T &b) {
        return (s || f) || (b);
    }

    /**
     * @brief operator ~ for uint256_t
     * @returns 1's complement of this number
     */
    inline uint256_t operator~() { return {~f, ~s}; }

    /**
     * @brief operator << for uint256_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns value of this shifted by p to left
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint256_t operator<<(const T &p) {
        if (!p) {
            return {this->f, this->s};
        } else if (p >= 128) {
            return uint256_t((this->s << (p - 128)), uint128_t(0));
        }
        return uint256_t((this->f << p) + (this->s >> (128 - p)),
                         (this->s << p));
    }

    /**
     * @brief operator <<= for uint256_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns this shifted by p to left
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint256_t &operator<<=(const T &p) {
        if (p) {
            if (p >= 128) {
                this->f = (this->s << (p - 128));
                this->s = uint128_t(0);
            } else {
                f = ((this->s >> (128 - p)) + (this->f << p));
                s = (this->s << p);
            }
        }
        return *this;
    }

    /**
     * @brief operator >> for uint256_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns value of this shifted by p to right
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint256_t operator>>(const T &p) {
        if (!p) {
            return {this->f, this->s};
        } else if (p >= 128) {
            return uint256_t(uint128_t(0), (this->f >> (p - 128)));
        }
        return uint256_t((this->f >> p),
                         (this->s >> p) + (this->f << (128 - p)));
    }

    /**
     * @brief operator >>= for uint256_t
     * @tparam T integral type
     * @param p number denoting number of shifts
     * @returns this shifted by p to right
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    uint256_t &operator>>=(const T &p) {
        if (p) {
            if (p >= 128) {
                f = uint128_t(0);
                s = (this->f >> (p - 128));
            } else {
                s = (this->s >> p) + (this->f << (128 - p));
                f = (this->f >> p);
            }
        }
        return *this;
    }

    /**
     * @brief operator & for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns value of this & p (& is bit-wise operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator&(const T &p) {
        return *this & uint256_t(p);
    }

    /**
     * @brief operator & for uint256_t (bitwise operator)
     * @param p number to be operated
     * @returns value of this & p (& is bit-wise operator)
     */
    inline uint256_t operator&(const uint256_t &p) {
        return {f & p.f, s & p.s};
    }

    /**
     * @brief operator &= for uint256_t (bitwise operator)
     * @param p number to be operated
     * @returns this = this & p (& is bit-wise operator)
     */
    inline uint256_t &operator&=(const uint256_t &p) {
        f &= p.f;
        s &= p.s;
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
    inline uint256_t &operator&=(const T p) {
        s &= p.s;
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
    inline uint256_t operator|(const T &p) {
        return *this | uint256_t(p);
    }

    /**
     * @brief operator | for uint256_t (bitwise operator)
     * @param p number to be operated
     * @returns value of this | p (| is bit-wise OR operator)
     */
    inline uint256_t operator|(const uint256_t &p) {
        return {this->f | p.f, this->s | p.s};
    }

    /**
     * @brief operator |= for other types (bitwise operator)
     * @tparam T integral type
     * @param p number to be operated
     * @returns this = this | p (| is bit-wise OR operator)
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator|=(const T &p) {
        s |= p;
        return *this;
    }

    /**
     * @brief operator |= for uint256_t (bitwise operator)
     * @param p number to be operated
     * @returns this = this | p (| is bit-wise OR operator)
     */
    inline uint256_t &operator|=(const uint256_t &p) {
        f |= p.f;
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
    inline uint256_t operator^(const T &p) {
        return uint256_t(f, s ^ p);
    }

    /**
     * @brief operator ^ for uint256_t (bitwise operator)
     * @param p number to be operated
     * @returns value of this ^ p (^ is bit-wise XOR operator)
     */
    inline uint256_t operator^(const uint256_t &p) {
        return {this->f ^ p.f, this->s ^ p.s};
    }

    /**
     * @brief operator ^= for uint256_t (bitwise operator)
     * @param p number to be operated
     * @returns this = this ^ p (^ is bit-wise XOR operator)
     */
    inline uint256_t &operator^=(const uint256_t &p) {
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
    inline uint256_t &operator^=(const T &p) {
        s ^= p;
        return *this;
    }

    /**
     * @brief operator << for printing uint256_t integer
     * @details Prints the uint256_t integer in decimal form
     * @note Note that this operator is costly since it uses strings to print
     * the value
     * @param op ostream object
     * @param p 256-bit integer
     * @returns op, ostream object.
     */
    friend std::ostream &operator<<(std::ostream &op, uint256_t p) {
        if (!p.f) {
            op << p.s;
        } else {
            std::string out = "0", p_2 = "1";
            uint128_t L(1);
            for (uint64_t i = 0; i < 128; ++i) {
                if ((p.s & L)) {
                    out = add(out, p_2);
                }
                p_2 = add(p_2, p_2);
                L <<= 1;
            }
            L = uint128_t(1);
            for (int i = 0; i < 128; ++i) {
                if ((p.f & L)) {
                    out = add(out, p_2);
                }
                p_2 = add(p_2, p_2);
                L <<= 1;
            }
            op << out;
        }
        return op;
    }
};

// Artihmetic
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator+(const T p, const uint256_t &q) {
    return uint256_t(p) + q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator-(const T p, const uint256_t &q) {
    return (uint256_t(p) - q);
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator*(const T p, const uint256_t &q) {
    return uint256_t(p) * q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator/(const T p, const uint256_t &q) {
    return uint256_t(p) / q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator%(const T p, const uint256_t &q) {
    return uint256_t(p) % q;
}

// Bitwise operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator&(const T &p, const uint256_t &q) {
    return uint256_t(p) & q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator|(const T p, const uint256_t &q) {
    return uint256_t(p) | q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator^(const T p, const uint256_t &q) {
    return uint256_t(p) ^ q;
}

// Boolean operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator&&(const T p, const uint256_t &q) {
    return uint256_t(p) && q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator||(const T p, const uint256_t &q) {
    return uint256_t(p) || q;
}

// Comparison operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator==(const T p, const uint256_t &q) {
    return uint256_t(p) == q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator!=(const T p, const uint256_t &q) {
    return uint256_t(p) != q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<(const T p, const uint256_t &q) {
    return uint256_t(p) < q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<=(const T p, const uint256_t &q) {
    return uint256_t(p) <= q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>(const T p, const uint256_t &q) {
    return uint256_t(p) > q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>=(const T p, const uint256_t &q) {
    return uint256_t(p) >= q;
}

#endif  // CIPHERS_UINT256_T_HPP_
