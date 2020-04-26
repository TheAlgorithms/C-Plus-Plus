#include <iostream>
int binary_search(int a[], int l, int r, int key) {
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (key == a[m])
			return m;
		else if (key < a[m])
			r = m - 1;
		else
			l = m + 1;
	}
	return -1;
}
int main(int argc, char const *argv[]) {
	int n, key;
	std::cout << "Enter size of array: ";
	std::cin >> n;
	std::cout << "Enter array elements: ";
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	std::cout << "Enter search key: ";
	std::cin >> key;
	int res = binary_search(a, 0, n - 1, key);
	if (res != -1)
		std::cout << key << " found at index " << res << endl;
	else
		std::cout << key << " not found" << endl;
	return 0;
}
