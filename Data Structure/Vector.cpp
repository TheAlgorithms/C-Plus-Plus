#include <cmath>
#include <string>
#include <iostream>

class Vector{
private:
	double x;
	double y;
	double z;

public:
	Vector() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector(double x_, double y_) {
		x = x_;
		y = y_;
		z = 0;
	}

	Vector(double x_, double y_, double z_) {
		x = x_;
		y = y_;
		z = z_;
	}

	void set(double x_, double y_){
		x = x_;
		y = y_;
	}

	void set(double x_, double y_, double z_){
		x = x_;
		y = y_;
		z = z_;
	}

	void add(Vector a) {
		x += a.x;
		y += a.y;
		z += a.z;
	}
	
	void sub(Vector a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	void mult(double a) {
		x *= a;
		y *= a;
		z *= a;
	}

	void div(double a) {
		x /= a;
		y /= a;
		z /= a;
	}

	//only 2D
	void fromRadians(double angle) {
		x = cos(angle);
		y = sin(angle);
		z = 0;
	}

	double getMag() {
		return sqrt(x * x + y * y + z * z);
	}

	void setMag(double m) {
		normalize();
		mult(m);
	}

	void normalize() {
		double mag = getMag();
		if (mag > 0) {
			div(mag);
		}
	}

	std::string stringify(){
		return ("(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")");
	}
};

int main(){

	Vector v(0,10,0);

	v.normalize();

	std::cout << v.stringify() << std::endl;

	v.set(1, 1, 1);

	std::cout << v.getMag() << std::endl;

	v.setMag(5);

	std::cout << v.stringify() << std::endl;

	v.fromRadians(3.1415/4);

	std::cout << v.stringify() << std::endl;

	return 0;
}