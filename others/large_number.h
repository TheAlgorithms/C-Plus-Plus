/**
 * @author Krishna Vedala
 * @email krishna (dot) vedala (at) ieee (dot) org
 **/

#ifndef __LARGE_NUMBER__
#define __LARGE_NUMBER__
#include <type_traits>
#include <iostream>
#include <cassert>
#include <vector>

/**
 * Store large unsigned numbers as a C++ vector
 * The class provides convenience functions to add a
 * digit to the number, perform multiplication of
 * large number with long unsigned integers.
 **/
class large_number
{
public:
    large_number() /**< initializer */
    {
        _digits.push_back(1);
    }

    large_number(unsigned long n) /**< initializer */
    {
        unsigned long carry = n;
        do
        {
            add_digit(carry % 10);
            carry /= 10;
        } while (carry != 0);
    }

    large_number(const large_number &a) /**< initializer */
    {
        _digits = a._digits;
    }

    large_number(const std::vector<unsigned char> &vec) /**< initializer */
    {
        _digits = vec;
    }

    /**
     * Function to check implementation
     **/
    static bool test()
    {
        std::cout << "------ Checking `large_number` class implementations\t" << std::endl;
        large_number a(40);
        a *= 10;
        if (a != large_number(400))
        {
            std::cerr << "\tFailed 1/5 (" << a << "!=400)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 1/5...";
        a += 120;
        if (a != large_number(520))
        {
            std::cerr << "\tFailed 2/5 (" << a << "!=520)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 2/5...";
        a *= 10;
        if (a != large_number(5200))
        {
            std::cerr << "\tFailed 3/5 (" << a << "!=5200)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 3/5...";
        ++a;
        if (a != large_number(5201))
        {
            std::cerr << "\tFailed 4/5 (" << a << "!=5201)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 4/5...";
        a++;
        if (a != large_number(5202))
        {
            std::cerr << "\tFailed 5/5 (" << a << "!=5202)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 5/5..." << std::endl;
        return true;
    }

    /**
     * add a digit at MSB to the large number
     **/
    void add_digit(unsigned int value)
    {
        if (value > 9)
        {
            std::cerr << "digit > 9!!\n";
            exit(EXIT_FAILURE);
        }

        _digits.push_back(value);
    }

    /**
     * Get number of digits in the number
     **/
    const size_t num_digits() const
    {
        return _digits.size();
    }

    /**
     * operator over load to access the
     * i^th digit conveniently and also
     * assign value to it
     **/
    inline unsigned char &operator[](size_t n)
    {
        return this->_digits[n];
    }

    inline const unsigned char &operator[](size_t n) const
    {
        return this->_digits[n];
    }

    /**
     * operator overload to compare two numbers
     **/
    friend std::ostream &operator<<(std::ostream &out, const large_number &a)
    {
        for (size_t i = a.num_digits(); i > 0; i--)
            out << a[i - 1] + '0';
        return out;
    }

    /**
     * operator overload to compare two numbers
     **/
    friend bool operator==(const large_number &a, const large_number b)
    {
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
    friend bool operator!=(const large_number &a, const large_number b)
    {
        return !(a == b);
    }

    /**
     * operator overload to increment (prefix)
     **/
    large_number &operator++()
    {
        this->add((unsigned int)1);
        return *this;
    }

    /**
     * operator overload to increment (postfix)
     **/
    large_number &operator++(int)
    {
        large_number tmp(_digits);
        ++(*this);
        return tmp;
    }

    /**
     * operator overload to add
     **/
    template <class T>
    large_number &operator+=(T &n)
    {
        if (std::is_same<T, large_number>::value) // if adding with another large_number
        {
            large_number *b = &n;
            const size_t max_L = std::max(this->num_digits(), b->num_digits());
            unsigned int carry = 0, temp;
            for (size_t i = 0; i < max_L; i++)
            {
                temp += carry;
                if (i < b->num_digits())
                    temp += (*b)[i];
                if (i < this->num_digits())
                    temp += (*this)[i];
                if (temp < 10)
                    carry = 0;
                else
                {
                    carry = temp / 10;
                    temp = temp % 10;
                }
                if (i < this->num_digits())
                    (*this)[i] = temp;
                else
                    this->add_digit(temp);
            }
            while (carry != 0)
            {
                if (i < this->num_digits())
                    (*this)[i] = carry % 10;
                else
                    this->add_digit(carry % 10);
                carry /= 10;
            }

            return *this;
        }

        static_assert(std::is_integral<T>::value, "Must be integer addition unsigned integer types.");
        // typedef typename std::make_unsigned<T>::type T2;
        this->add(b);
        return *this;
    }

    // /**
    //  * operator overload to increment
    //  **/
    // friend large_number &operator+(large_number a, const large_number b)
    // {
    //     const size_t max_L = std::max(a.num_digits(), b.num_digits());

    //     return a;
    // }

    /**
     * operator overload to increment
     **/
    template <class T>
    large_number &operator*=(const T n)
    {
        static_assert(std::is_integral<T>::value, "Must be integer addition unsigned integer types.");
        this->multiply(n);
        return *this;
    }

    /**
     * returns i^th digit as an ASCII character
     **/
    const char digit_char(size_t i) const
    {
        return _digits[num_digits() - i - 1] + '0';
    }

private:
    /**
     * multiply large number with another integer and
     * store the result in the same large number
     **/
    template <class T>
    void multiply(const T n)
    {
        static_assert(std::is_integral<T>::value, "Can only have integer types.");
        // assert(!(std::is_signed<T>::value)); //, "Implemented only for unsigned integer types.");

        size_t i;
        unsigned long long carry = 0, temp;
        for (i = 0; i < this->num_digits(); i++)
        {
            temp = (*this)[i] * n;
            temp += carry;
            if (temp < 10)
                carry = 0;
            else
            {
                carry = temp / 10;
                temp = temp % 10;
            }
            (*this)[i] = temp;
        }

        while (carry != 0)
        {
            this->add_digit(carry % 10);
            carry /= 10;
        }
    };

    /**
     * add large number with another integer and
     * store the result in the same large number
     **/
    template <class T>
    void add(const T n)
    {
        static_assert(std::is_integral<T>::value, "Can only have integer types.");
        // static_assert(!(std::is_signed<T>::value), "Implemented only for unsigned integer types.");

        size_t i = 0;
        long long carry = n;

        while (carry != 0)
        {
            if (i < this->num_digits())
            {
                carry += (*this)[i];
                (*this)[i] = carry % 10;
                i++;
            }
            else
                this->add_digit(carry % 10);
            carry /= 10;
            if (carry == 0)
                return;
        }
    };

    std::vector<unsigned char> _digits; /**< where individual digits are stored */
};

#endif
