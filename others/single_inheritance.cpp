// A simple program to demonstrate single inheritance
#include<iostream>

using std::cout;
// Super -class A
class A{
    int a = 4;
    int b = 9;
 public:
    int mul() {
            int c = a*b;
            return c;
    }
};
// class B inherits the objects from class A
class B: private A {
 public:
    void display() {
                int res = mul();
                std::cout << "Product: " << res << endl;
	}
};
int main() {
        B b;  //creating objects of class B
        b.display();  // calling the method through the object
        return 0;
}
