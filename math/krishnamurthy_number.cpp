/*

	A Krishnamurthy number is a natural number which is equal to the sum of the factorial of its digits.

*/

#include <iostream>

//This function calculates the factorial of a number, a prerequisite for finding a Krishnamurthy number.
int factrl(int a){
	int fact=1;
	if (a!=0){
		for (int b=2; b<=a; b++){
			fact*=b;
		}
	}
	return fact;
}

//This function tells us whether its argument is a Krishnamurthy number or not.
bool Knum(int n){
	int x=n;
	int sum=0;
	while (x!=0){
		sum+=factrl(x%10);
		x/=10;
	}
	if (n==sum){
		return true;
	}
	else{
		return false;
	}
}

//some testcases
void test(){
	std::cout<<"1 is a Krishnamurthy number: "<<std::boolalpha<<Knum(1)<<std::endl;
	//should return true
	std::cout<<"2 is a Krishnamurthy number: "<<std::boolalpha<<Knum(2)<<std::endl;
	//should return true
	std::cout<<"121 is a Krishnamurthy number: "<<std::boolalpha<<Knum(121)<<std::endl;
	//should return false
	std::cout<<"145 is a Krishnamurthy number: "<<std::boolalpha<<Knum(145)<<std::endl;
	//should return true
}

//The main function tests our defined function against the testcases.
int main(){
	test();
	return 0;
}
