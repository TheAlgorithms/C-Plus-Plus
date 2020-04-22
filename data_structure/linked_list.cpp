#include <iostream>

struct node {
        int val;
        node *next;
};

node *start;

void insert(int x) {
        node *t = start;
        node *n = new node;
        n->val = x;
        n->next = NULL;
        if (start != NULL) {
                while (t->next != NULL) {
                        t = t->next;
                }
                t->next = n;             
        } else {
                start = n;
        }
        
}

void remove(int x) {
        if (start == NULL) {
                std::cout << "\nLinked List is empty\n";
                return;
        } else if (start->val == x) {
                node *temp = start;
                start = start->next;
                delete temp;
                return;
        }

        node *temp = start, *parent = start;

        while (temp != NULL && temp->val != x) {
                parent = temp;
                temp = temp->next;
        }

        if (temp == NULL) {
                std::cout << std::endl << x << " not found in list\n";
                return;
        }

        parent->next = temp->next;
        delete temp;
}

void search(int x) {
        node *t = start;
        int found = 0;
        while (t != NULL) {
                if (t->val == x) {
                        std::cout << "\nFound";
                        found = 1;
                        break;
                }
                t = t->next;
        }
        if (found == 0) {
                std::cout << "\nNot Found";
        }
}

void show() {
        node *t = start;
        while (t != NULL) {
                std::cout << t->val << "\t";
                t = t->next;
        }
}

void reverse() {
        node *first = start;
        if (first != NULL) {
                node *second = first->next;
                while (second != NULL) {
                        node *tem = second->next;
                        second->next = first;
                        first = second;
                        second = tem;
                }
                start->next = NULL;
                start = first;
        } else {
                std::cout << "\nEmpty list";
        }
}

int main() {
        int choice, x;
        do {
                std::cout << "\n1. Insert";
                std::cout << "\n2. Delete";
                std::cout << "\n3. Search";
                std::cout << "\n4. Print";
                std::cout << "\n5. Reverse";
                std::cout << "\n0. Exit";
                std::cout << "\n\nEnter you choice : ";
                std::cin >> choice;
                switch (choice) {
                case 1:
                        std::cout << "\nEnter the element to be inserted : ";
                        std::cin >> x;
                        insert(x);
                        break;
                case 2:
                        std::cout << "\nEnter the element to be removed : ";
                        std::cin >> x;
                        remove(x);
                        break;
                 case 3:
                        std::cout << "\nEnter the element to be searched : ";
                        std::cin >> x;
                        search(x);
                        break;
                 case 4:
                        show();
                        std::cout << "\n";
                        break;
                 case 5:
                        std::cout << "The reversed list: \n";
                        reverse();
                        show();
                        std::cout << "\n";
                        break;
               }
        } while (choice != 0);

        return 0;
}
