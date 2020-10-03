#include <iostream>

//Using template so that we can use both ints, floats or a combination of both.
template<typename T>
T* cross(T* a, T* b) {
	static T product[3];
	// This part does the math.
	product[0] = (a[1] * b[2]) - (b[1] * a[2]);
	product[1] = -((a[0] * b[2]) - (b[0] * a[2]));
	product[2] = (a[0] * b[1]) - (b[0] * a[1]);
	
	// The address of the first element of the product array is returned.
	return product;
}

int main() {
	// The values of a and b can be change to any number.
	// The arrays should contain direction ratios of the vectors in the order i, j and k respectively.
	int a[3] = {1, 2, 3};
	int b[3] = {4, 5, 6};

	// The address of the first element of the arrays is pass and not the array as a argument.
	// The array ans, contains the direction ratios in the order i, j and k respectively.
	int* ans = cross(a, b);
	std::cout << ans[0] << " " << ans[1] << " " << ans[2] << std::endl;
	return 0;
}
