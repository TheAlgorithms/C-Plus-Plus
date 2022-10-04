// dequeue implementation in C++
#include<iostream>

using namespace std;

// macro to define the size of the dequeue
#define SIZE 10

class dequeue {
  int a[20], f, r;
  public:

    // define the constructor
    dequeue::dequeue() {
      f = -1;
      r = -1;
    }

  // init using the constructor
  dequeue();

  // define methods to interface
  void insert_at_beg(int i) {
    if (r >= SIZE - 1) {
      cout << "\n insertion is not possible, overflow!!!!";
    } else {
      if (f == -1) {
        f++;
        r++;
      } else {
        r = r + 1;
      }
      a[r] = i;
      cout << "\nInserted item is" << a[r];
    }
  }
  void insert_at_end(int i) {
    if (r >= SIZE - 1) {
      cout << "\n insertion is not possible, overflow!!!!";
    } else {
      if (f == -1) {
        f++;
        r++;
      } else {
        r = r + 1;
      }
      a[r] = i;
      cout << "\nInserted item is" << a[r];
    }
  }
  void delete_fr_front() {
    if (f == -1) {
      cout << "deletion is not possible::dequeue is empty";
      return;
    } else {
      cout << "the deleted element is:" << a[f];
      if (f == r) {
        f = r = -1;
        return;
      } else
        f = f + 1;
    }
  }
  void delete_fr_rear() {
    if (f == -1) {
      cout << "deletion is not possible::dequeue is empty";
      return;
    } else {
      cout << "the deleted element is:" << a[r];
      if (f == r) {
        f = r = -1;
      } else
        r = r - 1;
    }
  }
  void show() {
    if (f == -1) {
      cout << "Dequeue is empty";
    } else {
      for (int i = f; i <= r; i++) {
        cout << a[i] << " ";
      }
    }
  }
};

signed main() {
  int c, i;

  // declare an instance of the class
  dequeue d;

  // make the program loop
  Do {
    cout << "\n 1.insert at beginning";
    cout << "\n 2.insert at end";
    cout << "\n 3.show";
    cout << "\n 4.deletion from front";
    cout << "\n 5.deletion from rear";
    cout << "\n 6.exit";
    cout << "\n enter your choice:";
    cin >> c;
    switch (c) {
    case 1:
      cout << "enter the element to be inserted";
      cin >> i;
      d.insert_at_beg(i);
      break;
    case 2:
      cout << "enter the element to be inserted";
      cin >> i;
      d.insert_at_end(i);
      break;
    case 3:
      d.show();
      break;
    case 4:
      d.delete_fr_front();
      break;
    case 5:
      d.delete_fr_rear();
      break;
    case 6:
      exit(1);
      break;
    default:
      cout << "invalid choice";
      break;
    }
  }
  while (c != 7);
  return 0;
}
