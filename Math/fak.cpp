#include <iostream>

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

int main()
{
    for (int i = 0; i <= 20;i++)
        std::cout << i << "!" << " = " << fak(i) << std::endl;

    return 0;
}