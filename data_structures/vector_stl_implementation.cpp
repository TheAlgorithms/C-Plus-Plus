#include <bits/stdc++.h>
using namespace std;
template <typename T> class vectorClass {
    T* arr;
    int capacity;
    int current;
 
public:
    vectorClass()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }
      ~ vectorClass()
    {
          delete [] arr;
    }
    void push(T data)
    {
        if (current == capacity) {
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = data;
        current++;
    }
    void push(T data, int index)
    {
        if (index == capacity)
            push(data);
        else
            arr[index] = data;
    }
    T get(int index)
    {
        if (index < current)
            return arr[index];
    }
    void pop() { current--; }
  
    int size() { return current; }

    int getcapacity() { return capacity; }

    void print()
    {
        for (int i = 0; i < current; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};
 

signed main()
{
    vectorClass<int> v;
    vectorClass<char> v1;
    v.push(10);
    v.push(20);
    v.push(30);
    v.push(40);
    v.push(50);
    v1.push(71);
    v1.push(72);
    v1.push(73);
    v1.push(74);
 
    cout << "Vector size : " << v.size() << endl;
    cout << "Vector capacity : " << v.getcapacity() << endl;
 
    cout << "Vector elements : ";
    v.print();
 
    v.push(100, 1);
 
    cout << "\nAfter updating 1st index" << endl;
 
    cout << "Vector elements of type int : " << endl;
    v.print();

    cout << "Vector elements of type char : " << endl;
    v1.print();
    cout << "Element at 1st index of type int: " << v.get(1)
         << endl;
    cout << "Element at 1st index of type char: "
         << v1.get(1) << endl;
 
    v.pop();
    v1.pop();
 
    cout << "\nAfter deleting last element" << endl;
 
    cout << "Vector size of type int: " << v.size() << endl;
    cout << "Vector size of type char: " << v1.size()
         << endl;
    cout << "Vector capacity of type int : "
         << v.getcapacity() << endl;
    cout << "Vector capacity of type char : "
         << v1.getcapacity() << endl;
 
    cout << "Vector elements of type int: ";
    v.print();
    cout << "Vector elements of type char: ";
    v1.print();
 
    return 0;
}
