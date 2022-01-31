#include <iostream>

struct node {
    int value = 0;
    node* next = NULL;
};

double middle_element_sll(node *start) {
    int size = 0;
    node* slow = start;
    node* fast = start->next;
    bool moveSlow = false;
    while (fast != NULL) {
        size++;
        fast = fast->next;
        if (moveSlow) {
            slow = slow->next;
        }
        moveSlow = !moveSlow;
    }
    if (size % 2 != 0) {
        return (slow->value + slow->next->value) / 2.0;
    }
    return slow->value;
}

int main() {
    int size, input;
    node* start = new node, *temp = start;
    std::cout << "How many elements will be in this linked list? ";
    std::cin >> size;
    std::cout << "Write out a linked list." << std::endl;
    while (size > 0) {
        std::cin >> input;
        if (start->value == NULL) {
            start->value = input;
        } else {
            temp->next = new node;
            temp = temp->next;
            temp->value = input;
        }
        size--;
    }
    double answer = middle_element_sll(start);
    std::cout << "The middle of this linked list is: " << answer << std::endl;
    return 0;
}
