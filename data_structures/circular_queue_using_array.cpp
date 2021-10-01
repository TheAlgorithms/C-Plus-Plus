#include <iostream>
using namespace std;
#define num 100
// Can change the capacity of the array by replacing the value of variable num
int r = -1, f = -1, a[num], c;
void enqueue() {
    if ((r == c - 1 && f == 0) || f == r + 1) {
        cout << "\nQueue is full";
        return;
    }
    if (f == -1)
        f = 0;
    if (r == c - 1)
        r = 0;
    else
        r++;
    cout << "\nEnter integer:";
    cin >> a[r];
}
void dequeue() {
    if (f == -1) {
        cout << "\nQueue is empty";
        return;
    }
    cout << "\nItem deleted: " << a[f];
    if (f == r) {
        f = -1;
        r = -1;
    } else if (f == c - 1)
        f = 0;
    else
        f++;
}
void show() {
    int i;
    if (f == -1) {
        cout << "\nQueue is empty";
        return;
    }
    cout << "\nItems are: \n";
    for (i = f; i != r; i = (i + 1) % c) cout << a[i] << " ";
    cout << a[i];
}
int main() {
    int d;
    cout << "Enter capacity:";
    cin >> c;
    do {
        cout << "\nEnter a choice\n1-insert\n2-delete\n3-show\n4-exit\n";
        cin >> d;
        if (d == 1)
            enqueue();
        else if (d == 2)
            dequeue();
        else if (d == 3)
            show();
        else if (d == 4)
            exit(0);
        else
            cout << "\nEnter a valid choice.";
    } while (1);
    return 0;
}