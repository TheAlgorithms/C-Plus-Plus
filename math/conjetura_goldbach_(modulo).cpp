#include <iostream>

using namespace std;

	bool EsPrimo (int n)
	{
		bool primo=true;
		int cont=2;
		
		while ( n>cont && primo ) 
		{
				if(n%cont==0)
					primo=false;
				
				else
					cont++;
		}
		
		return primo;
	}
	
	int main ()
	{	
	const int MAX=50;
			int n,a=0,b=0;
			int V1[MAX],V2[MAX];
		
	do {
		cout<< " Introduce valor de n : ";
		cin>>n;
		} while (n%2!=0 || n<2);
		
		cout<<endl;
		
	for (int i=2; i<n; i++)
		for (int j=2; j<n; j++)
			if(EsPrimo(i) && EsPrimo(j) && i+j==n)
			{
				V1[a]=i;
				V2[b]=j;
				
				a++;
				b++;
			}
			
	cout<< "Las posibles sumas serian: "<<endl;
	
	for (int i=0; i<a/2; i++)
		cout<<V1[i]<<"+"<<V2[i]<<"="<<n<<endl;
		
	system("pause");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
