//This Programme returns the Nth fibonacci as a string.
//The method used is manual addition with carry and placing it in a string which is called string addition
//This makes it have no bounds or limits


#include <iostream>
#include <string>

using namespace std;

std::string add(std::string a, std::string b) 
{ 
    std::string temp = "";
    while ((int)a.length() < (int)b.length()) 
    {
        a = "0" + a;
    }
    while ((int)b.length() < (int)a.length()) {
        b = "0" + b;
    }
    int carry = 0;
    for (int i = a.length() - 1; i >= 0; i--) 
    {
        char val = (char)(((a[i] - 48) + (b[i] - 48)) + 48 + carry);
        if (val > 57) 
        {
            carry = 1;
            val -= 10;
        }
        else 
        {
            carry = 0;
        }
        temp = val + temp;
    }
    if (carry != 0) 
    {
        temp = "1" + temp;
    }
    while (temp[0] == '0' && temp.length() != 1) 
    {
        temp = temp.substr(1);
    }
    return temp;
}

void fib_Accurate(long long n) 
{
    std::string tmp = "";
    std::string fibMinus1 = "1";
    std::string fibMinus2 = "0";
    std::string comma = ", ";
        for (long long i = 0; i < n; i++) 
        {
            tmp = add(fibMinus1, fibMinus2);
            
            fibMinus2 = fibMinus1;
            fibMinus1 = tmp;
    	}
    std::cout <<  fibMinus2;
}


int main() 
{
    int n;
    cout << "Enter whatever number N you want to find the fibonacci of\n";
    cin >> n;
    cout << n << " th Fibonacci is \n";
	  fib_Accurate(n);
    
	return 0;
}
