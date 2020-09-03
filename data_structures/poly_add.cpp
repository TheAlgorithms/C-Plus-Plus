/**
 * @file
 * @brief Implementation of [Addition of two polynomials]
 * (https://en.wikipedia.org/wiki/Polynomial#Addition)
 * @author [Ankita Roy Chowdhury](https://github.com/Ankita19ms0010)
 * @details
 * This code takes two polynomials as input
 * and prints their sum using linked list.
 * The polynomials must be in increasing or decreasing order of degree.
 *
 */
#include <iostream>  // for io operations

struct term {
    int coef;
    int pow;
    struct term *next;
};

/**
 * The function will create a polynomial
 * @returns pol which is the first term of the polynomial
 */
struct term *create_polynomial() {
    auto *pol = new term();  // First term in polynomial
    auto *next_pol = new term();
    int ch = 0;

    // Initiating first term
    std::cout << "Enter power: ";
    std::cin >> pol->pow;
    std::cout << "Enter Coefficient: ";
    std::cin >> pol->coef;

    std::cout << "Continue?\n1.Yes\n0.No\n";
    std::cin >> ch;
    pol->next = next_pol;

    // Creating subsequent polynomial terms
    while (ch != 0) {
        std::cout << "Enter power: ";
        std::cin >> next_pol->pow;
        std::cout << "Enter Coefficient: ";
        std::cin >> next_pol->coef;
        next_pol->next = new term();
        std::cout << "Continue?\n1.Yes\n0.No\n";
        std::cin >> ch;
        next_pol = next_pol->next;
    }

    return pol;
}

/**
 * The function will add 2 polynomials
 * @param poly1 first polynomial of the addition
 * @param poly2 second polynomial of the addition
 * @returns pol_sum which is the first term of the summed polynomial
 * and poly3 controls the remaining terms of the summed polynomial
 */
struct term *poly_add(struct term *poly1, struct term *poly2) {
    auto *pol_sum = new term();
    auto *poly3 = new term();

    // Comparing the powers of the first nodes of both the polynomials

    /* If the power of the first polynomial is greater than the power of the
       second one place the power and coefficient of the first node of the first
       polynomial in pol_sum and increase the pointer poly1
     */
    if (poly1->pow > poly2->pow) {
        pol_sum->pow = poly1->pow;
        pol_sum->coef = poly1->coef;
        poly1 = poly1->next;
    }
    /* If the power of the second polynomial is greater than the power of the
       first one place the power and coefficient of the first node of the second
       polynomial in pol_sum and increase the pointer poly2
     */
    else if (poly1->pow < poly2->pow) {
        pol_sum->pow = poly2->pow;
        pol_sum->coef = poly2->coef;
        poly2 = poly2->next;
    }
    /* If both of them have same power then sum the coefficients
       place both the summed coefficient and the power in pol_sum
       increase both the pointers poly1 and poly2
     */
    else {
        pol_sum->pow = poly1->pow;
        pol_sum->coef = poly1->coef + poly2->coef;
        poly1 = poly1->next;
        poly2 = poly2->next;
    }

    // Assign the address of poly3 in the address field of pol_sum
    pol_sum->next = poly3;

    // Comparing the rest of the nodes until one polynomial gets exhausted
    while (poly1->next && poly2->next) {
        /* If the power of the first polynomial is greater than the power of
           the second one place the power and coefficient of that node of the
           first polynomial in poly3 and increase the pointer poly1
         */
        if (poly1->pow > poly2->pow) {
            poly3->pow = poly1->pow;
            poly3->coef = poly1->coef;
            poly1 = poly1->next;
        }
        /* If the power of the second polynomial is greater than the power of
           the first one place the power and coefficient of that node of the
           second polynomial in poly3 and increase the pointer poly2
         */
        else if (poly1->pow < poly2->pow) {
            poly3->pow = poly2->pow;
            poly3->coef = poly2->coef;
            poly2 = poly2->next;
        }
        /* If both of them have same power then sum the coefficients
           place both the summed coefficient and the power in poly3
           increase both the pointers poly1 and poly2
         */
        else {
            poly3->pow = poly1->pow;
            poly3->coef = poly1->coef + poly2->coef;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        poly3->next = new term();  // Dynamically creating a new node
        poly3 = poly3->next;       // Increasing the pointer poly3
    }

    /* ptrr points to that node of the polynomial (which is not exhausted)
       at which the other one got exhausted
     */
    auto *ptrr = new term();
    if (poly1->next) {
        ptrr = poly1;
    } else if (poly2->next) {
        ptrr = poly2;
    }

    // Placing the remaining terms of the polynomial (which is not exhausted) in
    // poly3
    while (ptrr->next) {
        poly3->pow = ptrr->pow;
        poly3->coef = ptrr->coef;
        poly3->next = new term();
        poly3 = poly3->next;
        ptrr = ptrr->next;
    }
    return pol_sum;
}

/**
 * The function will display the polynomial
 * @param node first term of the polynomial to be displayed
 * @returns none
 */
void display_polynomial(struct term *node) {
    while (node->next) {
        std::cout << node->coef << " x^" << node->pow;
        node = node->next;
        if (node->next != nullptr) {
            std::cout << " + ";
        }
    }
}

/**
 * Main function
 */
int main() {
    struct term *poly1 = nullptr, *poly2 = nullptr, *poly3 = nullptr;
    std::cout << "Define first polynomial\n";
    poly1 = create_polynomial();  // Creating the first polynomial
    std::cout << "\n First Polynomial:\n";
    display_polynomial(poly1);

    std::cout << "\nDefine second polynomial\n";
    poly2 = create_polynomial();  // Creating the second polynomial
    std::cout << "\n Second Polynomial:\n";
    display_polynomial(poly2);

    poly3 = poly_add(poly1, poly2);  // Adding the two polynomials
    std::cout << "\nResultant polynomial:\n";
    display_polynomial(poly3);
    std::cout << "\n";

    delete poly1, poly2, poly3;  // Freeing memory space

    return 0;
}