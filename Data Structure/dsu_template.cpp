ll N;
ll A[mx];
ll Parent[mx];

ll initialise(){
	ll i;
	rep(i,0,N){
		Parent[i]=i;
	}
}

ll dsufun(ll a,ll b){
	if (A[a]>A[b])
	{
		return 1;
	}else if (A[a]<A[b])
	{
		return -1;
	}else{
		return 0;
	}
}

ll parent(ll ind){
	if (ind==Parent[ind])
	{
		return ind;
	}
	return Parent[ind] = parent(Parent[ind]);
}

bool join(ll a, ll b){
	ll x,y;
	x=parent(a);
	y=parent(b);
	if (x==y)
	{
		return false;
	}
	switch (dsufun(x,y))
	{
		case -1: Parent[x]=y;
				break;
		case 1: Parent[y]=x;
				break;
	}
	return true;
}
