/**
 * @author tjgurwara99
 * @file
 *
 * A basic implementation of Complex Number field as a class with operators
 * overloaded to accommodate (mathematical) field operations.
 */

#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <stdexcept>
#include <ctime>

/**
 * Class Complex to represent complex numbers as a field.
 */
class Complex {
    // The real value of the complex number
    double re;
    // The imaginary value of the complex number
    double im;

  public:
    /**
     * Complex Constructor which initialises the complex number which takes two
     * arguments.
     * @param x The real value of the complex number (optional).
     * @param y The imaginary value of the complex number (optional).
     */
    explicit Complex(double x = 0.f, double y = 0.f) : re(x), im(y) { ; }

    /**
     * Copy Constructor
     * @param other The other number to equate our number to.
     */
    Complex(const Complex &other) : re(other.real()), im(other.imag()) { ; }

    /**
     * Member function (getter) to access the class' re value.
     */
    double real() const { return this->re; }

    /**
     * Member function (getter) to access the class' im value.
     */
    double imag() const { return this->im; }

    /**
     * Member function to which gives the absolute value (modulus) of our
     * complex number
     * @return \f$ \sqrt{z \dot \bar{z}} \f$ where \f$ z \f$ is our complex
     * number.
     */
    double abs() const {
        return std::sqrt(this->re * this->re + this->im * this->im);
    }

    /**
     * Member function which gives the argument of our complex number.
     * @return Argument of our Complex number in radians.
     */
    double arg() const { return std::atan2(this->im, this->re); }

    /**
     * Operator overload to be able to add two complex numbers.
     * @param other The other number that is added to the current number.
     * @return result current number plus other number
     */
    Complex operator+(const Complex &other) {
        Complex result(this->re + other.re, this->im + other.im);
        return result;
    }

    /**
     * Operator overload to be able to subtract two complex numbers.
     * @param other The other number being subtracted from the current number.
     * @return result current number subtract other number
     */
    Complex operator-(const Complex &other) {
        Complex result(this->re - other.re, this->im - other.im);
        return result;
    }

    /**
     * Operator overload to be able to multiple two complex numbers.
     * @param other The other number to multiply the current number to.
     * @return result current number times other number.
     */
    Complex operator*(const Complex &other) {
        Complex result(this->re * other.re - this->im * other.im,
                       this->re * other.im + this->im * other.re);
        return result;
    }

    /**
     * Operator overload of the BITWISE NOT which gives us the conjugate of our
     * complex number. NOTE: This is overloading the BITWISE operator but its
     * not a BITWISE operation in this definition.
     * @return result The conjugate of our complex number.
     */
    Complex operator~() const {
        Complex result(this->re, -(this->im));
        return result;
    }

    /**
     * Operator overload to be able to divide two complex numbers. This function
     * would throw an exception if the other number is zero.
     * @param other The other number we divide our number by.
     * @return result Current number divided by other number.
     */
    Complex operator/(const Complex &other) {
        Complex result = *this * ~other;
        double denominator =
            other.real() * other.real() + other.imag() * other.imag();
        if (denominator != 0) {
            result = Complex(result.real() / denominator,
                             result.imag() / denominator);
            return result;
        } else {
            throw std::invalid_argument("Undefined Value");
        }
    }

    /**
     * Operator overload to be able to copy RHS instance of Complex to LHS
     * instance of Complex
     */
    const Complex &operator=(const Complex &other) {
        this->re = other.real();
        this->im = other.imag();
        return *this;
    }
};

/**
 * Logical Equal overload for our Complex class.
 * @param a Left hand side of our expression
 * @param b Right hand side of our expression
 * @return 'True' If real and imaginary parts of a and b are same
 * @return 'False' Otherwise.
 */
bool operator==(const Complex &a, const Complex &b) {
    return a.real() == b.real() && a.imag() == b.imag();
}

/**
 * Overloaded insersion operator to accommodate the printing of our complex
 * number in their standard form.
 * @param os The console stream
 * @param num The complex number.
 */
std::ostream &operator<<(std::ostream &os, const Complex &num) {
    os << "(" << num.real();
    if (num.imag() < 0) {
        os << " - " << -num.imag();
    } else {
        os << " + " << num.imag();
    }
    os << "i)";
    return os;
}

/**
 * Function to get random numbers to generate our complex numbers for test
 */
double get_rand() { return (std::rand() % 100 - 50) / 100.f; }

/**
 * Tests Function
 */
void tests() {
    std::srand(std::time(nullptr));
    double x1 = get_rand(), y1 = get_rand(), x2 = get_rand(), y2 = get_rand();
    Complex num1(x1, y1), num2(x2, y2);
    std::complex<double> cnum1(x1, y1), cnum2(x2, y2);
    Complex result;
    std::complex<double> expected;
    // Test for addition
    result = num1 + num2;
    expected = cnum1 + cnum2;
    assert(((void)"1 + 1i + 1 + 1i is equal to 2 + 2i but the addition doesn't "
                  "add up \n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "First test passes." << std::endl;
    // Test for subtraction
    result = num1 - num2;
    expected = cnum1 - cnum2;
    assert(((void)"1 + 1i - 1 - 1i is equal to 0 but the program says "
                  "otherwise. \n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Second test passes." << std::endl;
    // Test for multiplication
    result = num1 * num2;
    expected = cnum1 * cnum2;
    assert(((void)"(1 + 1i) * (1 + 1i) is equal to 2i but the program says "
                  "otherwise. \n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Third test passes." << std::endl;
    // Test for division
    result = num1 / num2;
    expected = cnum1 / cnum2;
    assert(((void)"(1 + 1i) / (1 + 1i) is equal to 1 but the program says "
                  "otherwise.\n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Fourth test passes." << std::endl;
    // Test for conjugates
    result = ~num1;
    expected = std::conj(cnum1);
    assert(((void)"(1 + 1i) has a conjugate which is equal to (1 - 1i) but the "
                  "program says otherwise.\n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Fifth test passes.\n";
    // Test for Argument of our complex number
    assert(((void)"(1 + 1i) has argument PI / 4 but the program differs from "
                  "the std::complex result.\n",
            (num1.arg() == std::arg(cnum1))));
    std::cout << "Sixth test passes.\n";
    // Test for absolute value of our complex number
    assert(((void)"(1 + 1i) has absolute value sqrt(2) but the program differs "
                  "from the std::complex result. \n",
            (num1.abs() == std::abs(cnum1))));
    std::cout << "Seventh test passes.\n";
}

/**
 * Main function
 */
int main() {
    tests();
    return 0;
}
