/*
1. Computes (X^N)%M in O(logN) complexity
2. This method is known as Binary Exponentiation.
*/

long long M=1000000007
long long expo(long long X, long long N)
{
	if(N==0)
		return 1;
	if(N%2==0)
		return expo((X*X)%M, N/2);
	return (X*expo(X,N-1))%M;
}
