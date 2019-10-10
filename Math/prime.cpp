/*
APPROACH 1:
Complexity: O(N^0.5)
*/
bool primeCheck(long long N)
{
	if(N<=1)
		return false;
	for(long long i=2;i*i<=N;i++)
		if(N%i==0)
			return false;
	return true;
}

/*
APPROACH 2:
Complexity: O(1)
Precomputation: O(Nlog(logN))
*/
bool prime[1000001];
void Precomputation()
{
	prime[0]=prime[1]=1;
	for(int i=2;i*i<=1000000;i++)
		if(!prime[i])
			for(int j=i*i;j<=1000000;j+=i)
				prime[j]=1;
}

bool checkPrime(int N)
{
	return !prime[N];
}
