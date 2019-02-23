#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

class cmplx{
	double real;
	double img;
	public:
	cmplx(): real{0}, img{0}{
	}
	cmplx(double r, double i=0): real{r}, img{i}{
	}
	double rl(){
		return real; 
	}
	double im(){
		return img;
	}
	cmplx operator+(cmplx a);
	cmplx operator-(cmplx a);
	cmplx operator*(cmplx a);
	cmplx operator/(cmplx a);
	cmplx operator=(cmplx a);
};

cmplx cmplx::operator+(cmplx a){
	cmplx c(real+a.real,img+a.img);
	return c;
}

cmplx cmplx::operator-(cmplx a){
	cmplx c(real-a.real,img-a.img);
	return c;
}

cmplx cmplx::operator*(cmplx a){
	double re = real*(a.real) - img*(a.img);
	double ig = img*(a.real) + real*(a.img);
	cmplx c(re,ig);
	return c;
}

cmplx cmplx::operator/(cmplx a){
	double den = (a.real)*(a.real) + (a.img)*(a.img);
	double re = (real*(a.real) + img*(a.img))/den;
	double ig = (img*(a.real) - real*(a.img))/den;
	cmplx c(re,ig);
	return c;
}

cmplx cmplx::operator=(cmplx a){
	real = a.real;
	img = a.img;
	return *this;
}

/* Discrete Fourier Transform */
void dft(vector<cmplx> &v){
	int len = v.size();
	if(len == 1)
		return;
	cmplx root = 1;
	double theta = (2.0*M_PI/len);
	cmplx mf = cmplx(cos(2.0*M_PI/len), sin(2.0*M_PI/len));
	vector<cmplx> even;
	vector<cmplx> odd;
	for(int i=0; i<len; i+=2){
		even.push_back(v[i]);
		odd.push_back(v[i+1]);
	}
	dft(even);
	dft(odd);
	int half = len/2;
	for(int i=0; i<half; i++){
		v[i] = even[i] + root*odd[i];
		v[i+half] = even[i] - root*odd[i];
		root = root*mf;
	}
}

/* Inverse Discrete Fourier Transform */
/* This reverse the array(except first element) and then calculates its fft */
/* Then scale down the values by length and return */
void invdft(vector<cmplx> &v){
	reverse(v.begin()+1,v.end());
	dft(v);
	int len = v.size();
	for(int i=0; i<len; i++){
		v[i] = v[i]/len;
	}
}

int main(){
	vector<cmplx> v = {1,2,3,4};
	dft(v);
	for(int i=0; i<4; i++){
		cout << v[i].rl() << " " << v[i].im() << endl;
	}
	invdft(v);
	for(int i=0; i<4; i++){
		cout << v[i].rl() << " " << v[i].im() << endl;
	}
}
