int three_part_binary_search(int a[], int x, int low, int high){
	if (low < high){
		int m1 = (low + high) / 3 + 1;
		int m2 = 2 * (low + high) / 3 + 1;

		if (x == a[m1])
			return m1;
		else if (x == a[m2])
			return m2;
		else if (x < a[m1])
			return three_part_binary_search(a, x, low, m1 - 1);
		else if (x<a[m2])
			return three_part_binary_search(a, x, m1 + 1, m2 - 1);
		else if (x>a[m2])
			return three_part_binary_search(a, x, m2 + 1, high);
	}
	else
		return -1;
}