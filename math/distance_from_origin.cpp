#include<iostream>
#include<conio.h>
#include<math.h>

class point {
protected:
    int x, y;
public:
    void get() {
        std::cout << "Enter the value of the points: " << "\n";
        std::cout << "Point x: ";
        std::cin >> x;
        std::cout << "Point y: ";
        std::cin >> y;
    }
};

class Calculate:public point {
    double dis;
public:
    void display() {
        double disx = pow(x, 2);
        double disy = pow(y, 2);
        dis = sqrt(disx + disy);
        std::cout << "\n\nThe distance of the point from origin: " << dis;
    }
};

int main() {
    Calculate obj;
    obj.get();
    obj.display();

    return 0;
}
