/*  
* Approximation of the sin-function with the taylor series.
*/
#include<iostream>
#include<exception>
#include<math.h>

// Factioral of n 
long long fak(unsigned int n = 0)
{
    long long fak = 1L;
    if(n == 0)
        return 0L;
    else
    {
        for(int i = n; i > 0;i--)
            fak *=  i;
    }
    return fak;
}

// Approximation of the sin(x)
long long sin(long x)
{
    long long sum = 0L;
    for (long long i = 0L; i < 1000000000000000000;i++)
        sum += pow(-1, i) * (pow(x, 2 * i + 1) / fak(2 * i + 1)); 

    return sum;
}

int main()
{   
    std::cout << "Sin(" << M_PI <<  ") : " << sin(M_PI) << std::endl; 
    std::cout << "Sin(" << M_PI / 2 <<  ") : " << sin(M_PI / 2) << std::endl; 
    std::cout << "Sin(" << 0 <<  ") : " << sin(0) << std::endl;
    std::cout << "Sin(" << M_PI * 2 <<  ") : " << sin(M_PI * 2) << std::endl; 
    return 0;
}