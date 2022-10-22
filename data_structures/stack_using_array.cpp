#include <iostream>
using namespace std;
struct Stack
{
    int size;
    int top;
    int * arr;
    
    Stack(int s)
    {
        size = s;
        top = -1;
        arr = new int[size];
    }
};

bool isEmpty(Stack * s)
{
    return (s->top == -1);
}

bool isFull(Stack * s)
{
    return (s->top == s->size - 1);
}

void push(Stack * s, int x) {
    if (isFull(s)) {
        cout << "\nOverflow";
    } else {
        s->arr[++s->top] = x;
    }
}

void pop(Stack * s) {
    if (isEmpty(s)) {
        cout << "\nUnderflow";
    } else {
        cout << "\n" << s->arr[s->top--] << " deleted";
    }
}

void show(Stack * s) {
    for (int i = 0; i <= s->top; i++) {
        cout << s->arr[i] << "\n";
    }
}

void topmost(Stack * s) { cout << "\nTopmost element: " << s->arr[s->top]; }
void bottom(Stack * s) { cout << "\nBottom element: " << s->arr[0]; } // If we need access to first element without using pop command 
int main() {
    int stack_size;
    cout << "\nEnter stack_size of stack : ";
    cin >> stack_size;
    Stack * st = new Stack(stack_size);
    int ch, x;
    do {
        cout << "\n0. Exit";
        cout << "\n1. Push";
        cout << "\n2. Pop";
        cout << "\n3. Print";
        cout << "\n4. Print topmost element:";
        cout << "\n5. Print Bottom element:";
        cout << "\nEnter Your Choice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "\nInsert : ";
            cin >> x;
            push(st,x);
        } else if (ch == 2) {
            pop(st);
        } else if (ch == 3) {
            show(st);
        } else if (ch == 4) {
            topmost(st);
        } else if(ch == 5) {
            bottom(st);
        }
    } while (ch != 0);

    delete[] st;

    return 0;
}
