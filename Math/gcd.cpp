/*
Computes gcd of two numbers in O(log(max(a,b))) time complexity
*/

int gcd(int a, int b)
{
	if(a==0)
		return b;
	return gcd(b%a, a);
}
/*
INBUILT FUNCTION FOR GCD USES SIMILAR IMPLEMENTATION.
SYNTAX: __gcd(a,b);
LIBRARY: <algorithm>
*/
