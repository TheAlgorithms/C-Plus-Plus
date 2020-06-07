/**
 * Copyright 2020 @author David Leal
 * @file
 *
 * Basic calculator: sum, subtract, multiply, and divide.
 */

#include <iostream>
#include <cstdlib>

/**
 * Same as the number typed by the user, but it's saved
 * in the new node so it won't be re-writed.
 */

struct Node {
    float datatype;
};

/** 
 * Prototypes
 */

void requestData(Node*);
void pause();

/**
 * --------------
 * Main function
 * --------------
 */

int main() {
    Node* new_node = new Node();
    requestData(new_node);

    pause();
    return 0;
}

/**
 * Similar as system("pause"), but secure.
 */

void pause() {
    std::cout << "Press ENTER key to continue . . . ";

    std::cin.get();
    std::cin.get();
}

/**
 * Function to call the calculator.
 */

void requestData(Node* new_node) {
    int opt = 0; float number;
    int amount_to_sum = 0, amount_to_subtract = 0, amount_to_multiply = 0,
        amount_to_divide = 0;

    do {
        std::cout << "\tVirtual Calculator" << std::endl;
        std::cout << "1. Sum." << std::endl;
        std::cout << "2. Subtraction." << std::endl;
        std::cout << "3. Multiply." << std::endl;
        std::cout << "4. Divide." << std::endl;
        std::cout << "5. Exit." << std::endl;

        std::cout << "\nChoose an option: ";
        std::cin >> opt;

        switch (opt) {
        case 1:
            std::cout << "Type the amount of numbers to sum: ";
            std::cin >> amount_to_sum;

            std::cout << "\n";

            for (int i = 1; i <= amount_to_sum; i++) {
                std::cout << "Type a number: ";
                std::cin >> number;

                /**
                 * Set the first number as the main number.
                 * Save it in the new node so it's not re-writed.
                 */

                if (i == 1) {
                    new_node->datatype = number;

                /**
                 * If the current number is not the first one,
                 * sum the current one with the previous one.
                 */

                } else {
                    new_node->datatype += number;
                }
            }

            std::cout << "\nThe sum of the numbers is: "
                << new_node->datatype << std::endl;

            pause();
            break;

        case 2:
            std::cout << "Type the amount of numbers to subtract: ";
            std::cin >> amount_to_subtract;

            std::cout << "\n";

            for (int i = 1; i <= amount_to_subtract; i++) {
                std::cout << "Type a number: ";
                std::cin >> number;

                /**
                 * Set the first number as the main number.
                 * Save it in the new node so it's not re-writed.
                 */

                if (i == 1) {
                    new_node->datatype = number;

                /**
                 * If the current number is not the first one,
                 * subtract the current one with the previous one.
                 */

                } else {
                    new_node->datatype -= number;
                }
            }

            std::cout << "\nThe subtraction of the numbers is: "
                << new_node->datatype << std::endl;

            pause();
            break;

        case 3:
            std::cout << "Type the amount of numbers to multiply: ";
            std::cin >> amount_to_multiply;

            std::cout << "\n";

            for (int i = 1; i <= amount_to_multiply; i++) {
                std::cout << "Type a number: ";
                std::cin >> number;

                /**
                 * Set the first number as the main number.
                 * Save it in the new node so it's not re-writed.
                 */

                if (i == 1) {
                    new_node->datatype = number;

                /**
                 * If the current number is not the first one,
                 * multiply the current one with the previous one.
                 */

                } else {
                    new_node->datatype *= number;
                }
            }

            std::cout << "\nThe multiply result of the numbers is: "
                << new_node->datatype << std::endl;

            pause();
            break;

        case 4:
            std::cout << "Type the amount of numbers to divide: ";
            std::cin >> amount_to_divide;

            std::cout << "\n";

            for (int i = 1; i <= amount_to_divide; i++) {
                std::cout << "Type a number: ";
                std::cin >> number;

                /**
                 * Set the first number as the main number.
                 * Save it in the new node so it's not re-writed.
                 */

                if (i == 1) {
                    new_node->datatype = number;

                /**
                 * If the current number is not the first one,
                 * divide the previous number with the current one.
                 */

                } else {
                    new_node->datatype /= number;
                }
            }

            std::cout << "\nThe division of the numbers is: "
                << new_node->datatype << std::endl;

            pause();
            break;
        }

        /**
         * Check user's OS
         * Uses system("cls") if OS is Windows
         */

        #ifdef __linux__
        system("clear");

        /**
         * Uses system("clear") if OS is Linux
         */

        #elif _WIN32
        system("cls");
        #endif
    } while (opt != 5);
}
