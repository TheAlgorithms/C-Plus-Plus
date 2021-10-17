/**
 * @file
 * \implementation of mapping function
 *
 * \details
 *  numbers = (1, 2, 3, 4)
 *  result = map(lambda x: x + x, numbers)
 *  print(list(result))
 *  This takes in a function and this function operates on the list provided
 *  in the end the final output of a map function is a list
 *  @author Akshat Sahijpal
 */

#include <iostream>
#include <vector>
#define print(x) std::cout << x << std::endl

/**
 * @tparam T Datatype can be any
 * @param fun The function tht performs the main operation on the list
 * @param v the list upon which the function performs operation
 * @return A list is returned
 */
template <typename T>
T map(int (*fun)(T),std::vector<T> v){
    T res;
    for (auto i : v){
        res += fun(i);
    }
    return res;
}
/**
 * \Input Function provided inside the map
 * @param T Datatype
 * @return
 */
int fun(int T){
    return T;
}
/**
 * \Main Function
 * \Creates a vector upon which the function fun performs
 */
int main(int argc, char const *argv[])
{
    std::vector<int> list = {1,1,1,2};
    print(map<int>(fun, list));
    return 0;
}