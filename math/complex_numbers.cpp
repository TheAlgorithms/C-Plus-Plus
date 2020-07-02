/**
 * @author tjgurwara99
 * @file
 *
 * \brief An implementation of Complex Number as Objects
 * \details A basic implementation of Complex Number field as a class with
 * operators overloaded to accommodate (mathematical) field operations.
 */

#include <cassert>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>
#include <stdexcept>

/**
 * \brief Class Complex to represent complex numbers as a field.
 */
class Complex {
    // The real value of the complex number
    double re;
    // The imaginary value of the complex number
    double im;

 public:
    /**
     * \brief Complex Constructor which initialises our complex number.
     * \details
     * Complex Constructor which initialises the complex number which takes
     * three arguments.
     * @param x If the third parameter is 'true' then this x is the absolute
     * value of the complex number, if the third parameter is 'false' then this
     * x is the real value of the complex number (optional).
     * @param y If the third parameter is 'true' then this y is the argument of
     * the complex number, if the third parameter is 'false' then this y is the
     * imaginary value of the complex number (optional).
     * @param is_polar 'false' by default. If we want to initialise our complex
     * number using polar form then set this to true, otherwise set it to false
     * to use initialiser which initialises real and imaginary values using the
     * first two parameters (optional).
     */
    explicit Complex(double x = 0.f, double y = 0.f, bool is_polar = false) {
        if (!is_polar) {
            re = x;
            im = y;
            return;
        }

        re = x * std::cos(y);
        im = x * std::sin(y);
    }

    /**
     * \brief Copy Constructor
     * @param other The other number to equate our number to.
     */
    Complex(const Complex &other) : re(other.real()), im(other.imag()) {}

    /**
     * \brief Member function to get real value of our complex number.
     * Member function (getter) to access the class' re value.
     */
    double real() const { return this->re; }

    /**
     * \brief Member function to get imaginary value of our complex number.
     * Member function (getter) to access the class' im value.
     */
    double imag() const { return this->im; }

    /**
     * \brief Member function to give the modulus of our complex number.
     * Member function to which gives the absolute value (modulus) of our
     * complex number
     * @return \f$ \sqrt{z \bar{z}} \f$ where \f$ z \f$ is our complex
     * number.
     */
    double abs() const {
        return std::sqrt(this->re * this->re + this->im * this->im);
    }

    /**
     * \brief Member function to give the argument of our complex number.
     * @return Argument of our Complex number in radians.
     */
    double arg() const { return std::atan2(this->im, this->re); }

    /**
     * \brief Operator overload of '+' on Complex class.
     * Operator overload to be able to add two complex numbers.
     * @param other The other number that is added to the current number.
     * @return result current number plus other number
     */
    Complex operator+(const Complex &other) {
        Complex result(this->re + other.re, this->im + other.im);
        return result;
    }

    /**
     * \brief Operator overload of '-' on Complex class.
     * Operator overload to be able to subtract two complex numbers.
     * @param other The other number being subtracted from the current number.
     * @return result current number subtract other number
     */
    Complex operator-(const Complex &other) {
        Complex result(this->re - other.re, this->im - other.im);
        return result;
    }

    /**
     * \brief Operator overload of '*' on Complex class.
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
     * \brief Operator overload of '~' on Complex class.
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
     * \brief Operator overload of '/' on Complex class.
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
     * \brief Operator overload of '=' on Complex class.
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
 * \brief Operator overload of '==' on Complex class.
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
 * \brief Operator overload of '<<' of ostream for Complex class.
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
 * \brief Function to get random numbers to generate our complex numbers for
 * test
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
