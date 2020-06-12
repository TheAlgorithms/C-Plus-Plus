#include <iostream>
template  <class X>
class node {
public:
    X val;
    node<X> *next;
};


template  <class X>
class linked_list
{
private:
    node<X> *start;
public:
    linked_list()
    {
        start=NULL;
    }
    void insert (X);
    void remove (X);
    void search (X);
    void show();
    void reverse();
};


template  <class X>
void linked_list<X>::insert(X x) {
        node <X>*t = start;
        node <X>*n = new node<X>;
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
template  <class X>
void linked_list<X>::remove(X x) {
        if (start == NULL) {
            std::cout << "\nLinked List is empty\n";
            return;
        } else if (start->val == x) {
            node <X>*temp = start;
            start = start->next;
            delete temp;
            return;
        }
        node<X> *temp = start, *parent = start;
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
template  <class X>
void linked_list<X>::search(X x) {
        node<X> *t = start;
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

template  <class X>
void linked_list<X>::show() {
        node <X>*t = start;
        while (t != NULL) {
                std::cout << t->val << "\t";
                t = t->next;
        }
}
template  <class X>
void linked_list<X>::reverse() {
    node <X>*first = start;
    if (first != NULL) {
            node<X> *second = first->next;
            while (second != NULL) {
                    node<X> *tem = second->next;
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
        linked_list<int> object;
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
                        object.insert(x);
                        break;
                case 2:
                        std::cout << "\nEnter the element to be removed : ";
                        std::cin >> x;
                        object.remove(x);
                        break;
                 case 3:
                        std::cout << "\nEnter the element to be searched : ";
                        std::cin >> x;
                        object.search(x);
                        break;
                 case 4:
                        object.show();
                        std::cout << "\n";
                        break;
                 case 5:
                        std::cout << "The reversed list: \n";
                        object.reverse();
                        object.show();
                        std::cout << "\n";
                        break;
               }
        } while (choice != 0);

        return 0;
}
