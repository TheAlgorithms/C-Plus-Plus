/**
 * Copyright 2020 @author tjgurwara99
 * @file
 *
 * A basic implementation of Complex Number field as a class with operators overloaded to accommodate (mathematical) field operations.
 */

#include <iostream>
#include <cmath>
#include <stdexcept>

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
     * Complex Constructor which initialises the complex number which takes two arguments.
     * @param x The real value of the complex number.
     * @param y The imaginary value of the complex number.
     */
    Complex(double x, double y) {
        this->re = x;
        this->im = y;
    }
    
    /**
     * Complex Constructor which initialises the complex number with no arguments.
     */
    Complex() {
        Complex(0.0,0.0);
    }

    /**
     * Member function (getter) to access the class' re value.
     */
    double real() const {
        return this->re;
    }

    /**
     * Member function (getter) to access the class' im value.
     */
    double imag() const {
        return this->im;
    }

    /**
     * Member function to which gives the absolute value (modulus) of our complex number
     * @return \f$ \sqrt{z \dot \bar{z} \f$ where \f$ z \f$ is our complex number.
     */
    double abs() const {
        return std::sqrt(this->re*this->re + this->im*this->im);
    }

    /**
     * Operator overload to be able to add two complex numbers.
     * @param other The other number that is added to the current number.
     * @return result current number plus other number
     */
    Complex operator+(const Complex& other) {
        Complex result(this->re + other.re, this->im + other.im);
        return result;
    }

    /**
     * Operator overload to be able to subtract two complex numbers.
     * @param other The other number being subtracted from the current number.
     * @return result current number subtract other number
     */
    Complex operator-(const Complex& other) {
        Complex result(this->re - other.re, this->im - other.im);
        return result;
    }

    /**
     * Operator overload to be able to multiple two complex numbers.
     * @param other The other number to multiply the current number to.
     * @return result current number times other number.
     */
    Complex operator*(const Complex& other) {
        Complex result(this->re * other.re - this->im * other.im,
                       this->re * other.im + this->im * other.re);
        return result;
    }

    /**
     * Operator overload of the BITWISE NOT which gives us the conjugate of our complex number.
     * NOTE: This is overloading the BITWISE operator but its not a BITWISE operation in this definition.
     * @return result The conjugate of our complex number.
     */
    Complex operator~() const {
        Complex result(this->re, -(this->im));
        return result;
    }

    /**
     * Operator overload to be able to divide two complex numbers. This function would throw an exception if the other number is zero.
     * @param other The other number we divide our number by.
     * @return result Current number divided by other number.
     */
    Complex operator/(const Complex& other) {
        Complex result = *this * ~other;
        double denominator = other.abs() * other.abs();
        if (denominator != 0) {
            result = Complex(result.real() / denominator, result.imag() / denominator);
            return result;
        }
        else {
            throw std::invalid_argument("Undefined Value");
        }
    }
};

/**
 * Logical Equal overload for our Complex class.
 * @param a Left hand side of our expression
 * @param b Right hand side of our expression
 * @return 'True' If real and imaginary parts of a and b are same
 * @return 'False' Otherwise.
 */
bool operator==(const Complex& a, const Complex& b) {
    double del_real = a.real() - b.real();
    double del_imag = a.imag() - b.imag();
    return ((del_real <= 1e-15 && del_real >= - 1e-15 ) && (del_imag <= 1e-15 && del_imag >= - 1e-15));
}

/**
 * Overloaded insersion operator to accommodate the printing of our complex number in their standard form.
 * @param os The console stream
 * @param num The complex number.
 */
std::ostream& operator<<(std::ostream& os, const Complex& num) {
    os << num.real();
    if (num.imag() < 0) {
        os << " - " << -num.imag();
    }
    else {
        os << " + " << num.imag();
    }
    os << "i";
    return os;
}

/**
 * Tests Function
 */
void tests() {
    Complex num1(1,1), num2(1,1);
    // Test for addition
    assert(((void)"1 + 1i + 1 + 1i is equal to 2 + 2i but the addition doesn't add up \n",
            (num1 + num2) == Complex(2,2)));
    std::cout << "First test passes." << std::endl;
    // Test for subtraction
    assert(((void)"1 + 1i - 1 - 1i is equal to 0 but the program says otherwise. \n",
            (num1 - num2) == Complex(0,0)));
    std::cout << "Second test passes." << std::endl;
    // Test for multiplication
    assert(((void)"(1 + 1i) * (1 + 1i) is equal to 2i but the program says otherwise. \n",
            (num1 * num2) == Complex(0,2)));
    std::cout << "Third test passes." << std::endl;
    // Test for division
    assert(((void)"(1 + 1i) / (1 + 1i) is equal to 1 but the program says otherwise.\n",
            (num1 / num2) == Complex(1,0)));
    std::cout << "Fourth test passes." << std::endl;
    // Test for conjugates
    assert(((void)"(1 + 1i) has a conjugate which is equal to (1 - 1i) but the program says otherwise.\n",
            ~num1 == Complex(1,-1)));
    std::cout << "Fifth test passes." << std::endl;

}
/**
 * Main function
 */
int main() {
    tests();
    return 0;
}
