#include <iostream>

int Highest_Common_Divisor(int num1, int num2)
{
    if (num2 == 0)
    {
        return num1;
    }
    else
    {
        return Highest_Common_Divisor(num2, num1 % num2);
    }
}
