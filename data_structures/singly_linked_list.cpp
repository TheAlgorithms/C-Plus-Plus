#include <iostream>

class singly_linked_list {

    struct node {
        int value;
        node* next;
    };

    node* head = NULL;

public:
    void insert(int value) {
        if(head == NULL) {
            node* temp_node = new node();
            temp_node->next = NULL;
            temp_node->value = value;
            head = temp_node;
        }
        else {
            node* temp_node = new node();
            temp_node->next = head;
            temp_node->value = value;
            head = temp_node;
        }
    }

    void remove() {
        if (head == NULL) {
            std::cout << "\nList is empty";
            return;;
        }

        node* temp_node = head;
        head = head->next;
        std::cout << "\nRemoved "<< temp_node->value <<" from the list"<< std::endl;
        delete temp_node;
    }

    void find(int value) {
        if (head == NULL) {
            std::cout << "\nList is empty";
            return;;
        }

        node* current = head;
        while (current != NULL) {
            if(value == current->value) {
                std::cout << "\n"<<value<<" found in the list"<< std::endl;
                return;
            }
            current = current->next;
        }

        std::cout << "\n" << value << " not found in the list" << std::endl;
    }

    void display() {
        if(head == NULL) {
            std::cout << "\nList is empty";
            return;;
        }

        node* current = head;
        std::cout << "\nList Content : ";
        while(current != NULL) {
            std::cout << current->value << " ";
            current = current->next;
        }
    }
};

int main(){
    int choice, value;
    singly_linked_list list;

    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Remove";
        std::cout << "\n3. Search";
        std::cout << "\n4. Display";
        std::cout << "\n0. Exit";
        std::cout << "\n\nEnter you choice : ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "\nEnter the element to be inserted : ";
            std::cin >> value;
            list.insert(value);
            break;
        case 2:
            list.remove();
            break;
        case 3:
            std::cout << "\nEnter the element to be searched : ";
            std::cin >> value;
            list.find(value);
            break;
        case 4:
            list.display();
            break;
        }
    } while (choice != 0);
}