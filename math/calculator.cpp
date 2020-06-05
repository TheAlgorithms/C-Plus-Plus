/**
 * Copyright 2020 @author David Leal
 * @file
 *
 * Basic calculator: sum, subtract, multiply, and divide.
 */

#include <iostream>
#include <conio.h>
#include <cstdlib>

struct Node {
    float datatype;
};

// Prototype
void requestData();

Node* new_node = new Node();

int opt = 0;
float number;

int main() {
    requestData();

    _getch();
    return 0;
}

void requestData() {
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

                // Set the first number as the main number
                // Save it in the new node so it's not re-writed
                if (i == 1) {
                    new_node->datatype = number;
                }

                // If the current number is not the first one,
                // sum the current one with the previous one
                else {
                    new_node->datatype += number;
                }
            }

            std::cout << "\nThe sum of the numbers is: "
                << new_node->datatype << std::endl;

            system("pause");
            break;

        case 2:
            std::cout << "Type the amount of numbers to subtract: ";
            std::cin >> amount_to_subtract;

            std::cout << "\n";

            for (int i = 1; i <= amount_to_subtract; i++) {
                std::cout << "Type a number: ";
                std::cin >> number;

                // Set the first number as the main number
                // Save it in the new node so it's not re-writed
                if (i == 1) {
                    new_node->datatype = number;
                }

                // If the current number is not the first one,
                // subtract the current one with the previous one
                else {
                    new_node->datatype -= number;
                }
            }

            std::cout << "\nThe subtraction of the numbers is: "
                << new_node->datatype << std::endl;

            system("pause");
            break;

        case 3:
            std::cout << "Type the amount of numbers to multiply: ";
            std::cin >> amount_to_multiply;

            std::cout << "\n";

            for (int i = 1; i <= amount_to_multiply; i++) {
                std::cout << "Type a number: ";
                std::cin >> number;

                // Set the first number as the main number
                // Save it in the new node so it's not re-writed
                if (i == 1) {
                    new_node->datatype = number;
                }

                // If the current number is not the first one,
                // multiply the current one with the previous one
                else {
                    new_node->datatype *= number;
                }
            }

            std::cout << "\nThe multiply result of the numbers is: "
                << new_node->datatype << std::endl;

            system("pause");
            break;

        case 4:
            std::cout << "Type the amount of numbers to divide: ";
            std::cin >> amount_to_divide;

            std::cout << "\n";

            for (int i = 1; i <= amount_to_divide; i++) {
                std::cout << "Type a number: ";
                std::cin >> number;

                // Set the first number as the main number
                // Save it in the new node so it's not re-writed
                if (i == 1) {
                    new_node->datatype = number;
                }

                // If the current number is not the first one,
                // divide the previous number with the current one
                else {
                    new_node->datatype /= number;
                }
            }

            std::cout << "\nThe division of the numbers is: "
                << new_node->datatype << std::endl;

            system("pause");
            break;
        }

        system("cls");
    } while (opt != 5);
}
