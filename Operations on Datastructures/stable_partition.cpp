// Credit to Sean Parent and his CppCon 2015 talk "Better Code: Data Structures"
// https://www.youtube.com/watch?v=sWgDk-o-6ZE&t=162s

#include <algorithm>
#include <iostream>
#include <vector>

template<typename Type, template<typename, typename=std::allocator<Type>> class Container>
std::ostream& operator<<(std::ostream& os, const Container<Type>& values)
{
    for (const auto& value: values)
        os << value << ' ';

    return os << '\n';
}

template<typename I, typename P>
decltype(auto) stable_partition(I f, I l, P& p)
{
    auto n = l - f;
    if (n == 0)
        return f;
    if (n == 1)
        return f + p(*f);

    auto m = f + n/2;

    return std::rotate(
        stable_partition(f, m, p),
        m,
        stable_partition(m, l, p));
}

int main()
{
    std::vector<int> numbers{-4, 3, -4, -6, 2, 9, 1, 0, -9, 4, 3, -8};
    std::cout << "Prior to stable partition: " << numbers;
    auto index = stable_partition(std::begin(numbers), std::end(numbers), [](auto value){return value > 0;});
    std::cout << "After stable partition:    " << numbers;

    return 0;
}
