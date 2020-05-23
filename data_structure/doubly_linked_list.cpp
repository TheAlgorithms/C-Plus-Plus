/*
 * Copyright : 2020 , MIT
 * 
 * Last Modified Date : 23, May , 2020
 * Modified by : Amit Kumar (offamitkumar)
 */
#include <iostream>
#include<cstdio>
#include<cstdlib>
using std::cout;
using std::cin;

struct node {
 public:
     int val;
     node *prev;
     node *next;
     node():val{0}, prev{nullptr}, next{nullptr} {}
     explicit node(int v):val{v}, prev{nullptr}, next{nullptr} {}
}*start;

class double_linked_list {
 public:
  int link_list_size;
  double_linked_list() {
    start = nullptr;
    link_list_size = 0;
  }
  void insert(int x);
  void remove(int x);
  void search(int x);
  void show();
  void reverseShow();

  void insert_nth(int value , int location) {
      if (location > link_list_size) {
          cout << "Invalid Location" << '\n';
          return;
      }
      //  for insertion at end just call simple insertion function
      if (location == link_list_size) {
          insert(value);
          return;
      }
      bool insert_at_head = (location == 0);
      node *inserted_node = new node(value);
      node *temp_start = start;
      inserted_node->next = start;
      while ( location-- > 0 ) {
          start = start->next;
      }
      inserted_node->next = start;
      inserted_node->prev = start->prev;
      if (start->prev != nullptr) {
          start ->prev ->next = inserted_node;
      }
      start ->prev = inserted_node;
      if (insert_at_head) {
          start = inserted_node;
      } else {
          start = temp_start;
      }
  }
};

void double_linked_list::insert(int x) {
  node *t = start;
  if (start != nullptr) {
    while (t->next != nullptr) {
      t = t->next;
    }
    node *n = new node;
    t->next = n;
    n->prev = t;
    n->val = x;
    n->next = nullptr;
  } else {
    node *n = new node;
    n->val = x;
    n->prev = nullptr;
    n->next = nullptr;
    start = n;
  }
}

void double_linked_list::remove(int x) {
  node *t = start;
  while (t != nullptr && t->val != x) {
    t = t-> next;
  }
  if (t == nullptr) {
    return;
  }
  if (t->prev == nullptr) {
    if (t->next == nullptr) {
      start = nullptr;
    } else {
      start = t->next;
      start->prev = nullptr;
    }
  } else if (t->next == nullptr) {
    t->prev->next = nullptr;
  } else {
    t->prev->next = t->next;
    t->next->prev = t->prev;
  }
}

void double_linked_list::search(int x) {
  node *t = start;
  int found = 0;
  while (t != nullptr) {
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

void double_linked_list::show() {
  node *t = start;
  while (t != nullptr) {
    std::cout << t->val << "\t";
    t = t->next;
  }
}

void double_linked_list::reverseShow() {
  node *t = start;
  while (t != nullptr && t->next != nullptr) {
    t = t->next;
  }
  while (t != nullptr) {
    std::cout << t->val << "\t";
    t = t->prev;
  }
}

int main() {
  int choice, x;
  double_linked_list ob;
  do {
    std::cout << "\n1. Insert";
    std::cout << "\n2. Delete";
    std::cout << "\n3. Search";
    std::cout << "\n4. Forward print";
    std::cout << "\n5. Reverse print";
    std::cout << "\n6. Insert at Nth location:";
    std::cout << "\n\nEnter you choice : ";
    std::cin >> choice;
    switch (choice) {
      case 1:
        std::cout << "\nEnter the element to be inserted : ";
        std::cin >> x;
        ob.link_list_size++;
        ob.insert(x);
        break;
      case 6:
            cout << "\nEnter the element to be inserted : ";
            cin >> x;
            int loc;
            cout << "\nEnter the location : ";
            cin >> loc;
            ob.insert_nth(x , loc);
            ob.link_list_size++;
            break;
      case 2:
        std::cout << "\nEnter the element to be removed : ";
        std::cin >> x;
        ob.remove(x);
        ob.link_list_size--;
        break;
      case 3:
        std::cout << "\nEnter the element to be searched : ";
        std::cin >> x;
        ob.search(x);
        break;
      case 4:
        ob.show();
        break;
      case 5:
        ob.reverseShow();
        break;
    }
  } while (choice != 0);
  return 0;
}
