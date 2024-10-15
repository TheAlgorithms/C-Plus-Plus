void sieveoferatosthenes(vector<ll>a,ll x){
	bool prime(x+1,true);

	for(ll i=2;i*i<=x;i++){
		if(prime[i]==true){
			for(ll j=i*i;j<=x;j+=i){
				prime[i]=false;
			}
		}
	}
	for(ll i=2;i<=x;i++){
		if(prime[i])a.push_back(i);
	}
} 
