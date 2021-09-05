#include<iostream>
using namespace std;

int main() {

    char str[100], temp;
    int size = 0, i = 0;

    cout << "Enter a string:";
    cin.getline(str, 100);

    while (str[size] != '\0') {
        size++;
    }

    size = size - 1;
    while (i < size) {
        temp = str[i];
        str[i] = str[size];
        str[size] = temp;
        size--;
        i++;
    }
    cout << "After reverse string:" << str;

    return 0;
}