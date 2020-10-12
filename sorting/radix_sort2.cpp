/**
 * @file
 * @brief Algorith of [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
 * @author [Suyash Jaiswal](https://github.com/Suyashjaiswal)
 * @details
 * Sort the vector of integers using radix sort i.e. sorting digi by digit using count sort as subroutine.
 * Running time of radix is O(d*(n+b)) where b is the base for representing numbers and d in the max digits in input inegers and n is number of integers.
 * consider example for n = 5, array elements = 432,234,143,332,123
    sorting digit by digit
    sorting according to
    1) 1st digit place
    => 432,332,143,123,234

    2) 2nd digit place
    => 123,432,332,234,143

    3) 3rd digit place
    => 123,143,234,332,432

    using count sort at each step, which is stable.
    stable => already sorted according to previous digits.
    
*/

// header files
#include <iostream>
#include <vector>
/**
 * @namespace sort
 * @brief Functions for sorting a vector of integers.
 */
namespace sort
{
/**
 * @namespace radix_sort
 * @brief Functions for sorting a vector of integers using radix sort algorithm.
 */
    namespace radix_sort
    {
/**
 * @brief Class to create a vector and sort it.
 */
    class radix{
    public:
    int n;
    std::vector<int> ar;
/**
 * @brief Constructor that initializes the vector on creation.
 * @param a vector to be sorted.
 */
    radix(std::vector<int>& a){
        ar = a;
        n = ar.size();
    }
    int get_max(){                                                      // returns the max element.
        int mx;for(int i = mx = 0;i < n;i++)mx = std::max(mx,ar[i]);
        return mx;
    }
    void show(){
        for(int i = 0;i < n;i++)std::cout<<ar[i]<<" ";std::cout<<"\n";
    }
    void radix_sort();
    void step_ith(int dig);
};
void radix :: step_ith(int cur_digit){                              // sorting according to current digit.
    int position[10] = {0};
    for(int i = 0;i < n;i++){
        position[(ar[i]/cur_digit)%10]++;                           // counting frequency of 0-9 at cur_digit.
    }
    int cur = 0;
    for(int i = 0;i < 10;i++){                                      
        int a = position[i];
        position[i] = cur;                                          // assingning starting position of 0-9.
        cur += a;
    }
    int temp[n];
    for(int i = 0;i < n;i++){
        temp[position[(ar[i]/cur_digit)%10]] = ar[i];               // storing ar[i] in ar[i]'s cur_digit expected position of this step.
        position[(ar[i]/cur_digit)%10]++;                           // incrementing ar[i]'s cur_digit position by 1, as current place used by ar[i].
    }
    for(int i = 0;i < n;i++){
        ar[i] = temp[i];
    }
}
void radix :: radix_sort(){
    int max_ele = get_max();
    for(int i = 1;max_ele/i > 0;i *= 10){                       // loop breaks when i > max_ele because no further digits left to makes changes in array.
        step_ith(i);
    }
}
}   // namespace radix_sort
}   // namespace sort

void test1(){
    std::vector<int> ar = {432,234,143,332,123};
    sort::radix_sort::radix obj(ar);
    obj.radix_sort();
    obj.show();
}
void test2(){
    std::vector<int> ar = {213,3214,123,111,112,142,133,132,32,12,113};
    sort::radix_sort::radix obj(ar);
    obj.radix_sort();
    obj.show();
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test1();
    test2();
    return 0;
}