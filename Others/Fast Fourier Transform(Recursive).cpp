const double PI = 4*atan(1);
const int N=2e5+5;
const int MOD=13313;
 
int FFT_N=0;
vector<base> omega;
 
void init_fft(int n)
{
	FFT_N = n;
	omega.resize(n);
	double angle = 2*PI/n;
	for(int i=0;i<n;i++)
	{
		omega[i]=base(cos(i*angle), sin(i*angle));
	}
}
 
void fft(vector<base> &a)
{
	int n=a.size();
	if(n==1)
		return;
	int half=n>>1;
	vector<base> even(half), odd(half);
	for(int i=0, j=0; i<n; i+=2, j++)
	{
		even[j]=a[i];
		odd[j]=a[i+1];
	}
	fft(even);
	fft(odd);
	int denominator=FFT_N/n;
	for(int i=0;i<half;i++)
	{
		base cur=odd[i] * omega[i*denominator];
		a[i]=even[i] + cur;
		a[i+half]=even[i] - cur;
	}
}
 
void multiply(vector<int> &a, vector<int> &b, vector<int> &res)
{
	vector<base> fa(a.begin(), a.end());
	vector<base> fb(b.begin(), b.end());
	int n=1;
	while(n<2*max(a.size(), b.size()))
		n<<=1;
	fa.resize(n);
	fb.resize(n);
	init_fft(n);
	fft(fa);
	fft(fb);
	for(int i=0;i<n;i++)
		fa[i] = conj(fa[i] *  fb[i]);
	fft(fa);
	res.resize(n);
	for(int i=0;i<n;i++)
	{
		res[i]=(long long)(fa[i].real()/n + 0.5);
		res[i]%=MOD;
	}
}
