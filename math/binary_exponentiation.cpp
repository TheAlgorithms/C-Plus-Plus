#include<iostream>
#include<cassert>

// the concept is to do exponentiation by converting the power to a sum of powers of 2.
// example: 3^13  we can convert 13 to 8+4+1. which can be represented by 1101. so to do 3^13 we can do instead
// 3^8 x 3^4 x 3^1. and so we get 3^13 and since every exponent is square of the old exponent eg: 3^8=(3^4)^2.

long long binary_exponentiation(ll a,ll b){
  long long res=1;   //
  while(b>0){
    if(b&1){
      res=res*a;
    }
    a=a*a;
    b>>=1;  //reducing the power by a power of 2. example 13->6->3->1->0;
  }
  return res;
}

static void tests(){
  assert(binary_exponentiation(2,2)==4);
  assert(binary_exponentiation(4,2)==16);
  assert(binary_exponentiation(2,10)==1024);
  std::cout<<"All tests successfully passed!\n";
}

int main(){
  int mode;
  std::cout<<"Please enter the mode you want to use \n (1) Self-Test Mode \n (2) Interactive Test Mode \n";
  std::cin>>mode;
  if(mode==1){
    long long a,b;
    std::cout<<"Enter the base:\n";
    std::cin>>a;
    std::cout<<"Enter the exponent:\n";
    std::cout<<b;
    std::cout<<"The exponent of "<<a<<"^"<<b<<"is:\n";
    std::cout<<binary_exponentiation(a,b);
  }
  else{
    tests();
  }
}
