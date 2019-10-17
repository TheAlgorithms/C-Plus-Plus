#include <bitset>
#include <iostream>
#include <string>
#include <assert.h>
 
uint32_t gray_encode(uint32_t b)
{
    return b ^ (b >> 1);
}
 
uint32_t gray_decode(uint32_t g)
{
    for (uint32_t bit = 1U << 31; bit > 1; bit >>= 1)
    {
        if (g & bit) g ^= bit >> 1;
    }
    return g;
}
 
std::string to_binary(int value) // utility function
{
    const std::bitset<32> bs(value);
    const std::string str(bs.to_string());
    const size_t pos(str.find('1'));
    return pos == std::string::npos ? "0" : str.substr(pos);
}
 
int main()
{
    std::cout << "Number\tBinary\tGray\tDecoded\n";
    for (uint32_t n = 0; n < 32; ++n)
    {
        uint32_t g = gray_encode(n);
        assert(gray_decode(g) == n);
 
        std::cout << n << "\t" << to_binary(n) << "\t" << to_binary(g) << "\t" << g << "\n";
    }
}
