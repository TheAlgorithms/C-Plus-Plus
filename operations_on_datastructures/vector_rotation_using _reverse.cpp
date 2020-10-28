/**
 *@file
 *
 *@brief  Rotates an 1D array/vector of length n by k indices in linear time.
 *
 *@details To obtain the desired vector in linear time complexity.Lets take the length of the array
 *as n and indices to be rotated as k(assume k>=0 for now),initially we reverse the array then we imagine
 *our initial array divided into two sub-arrays sub_1 is from index '0' to index 'k-1' and sub_2 is from
 *index 'k' to  'n-1'.we now reverse these sub-arrays as well and we have our desired implementation.
 *This will be a right rotation by k.Here k>0 gives right rotation and k<0 gives left rotation.k=0 gives no change.
 *For left rotation k=k mod n (k is assumed negative for left rotation)is given to the rotation function
 *which results in left rotation, as a k index left rotation is equivalent to (k mod n)  index right rotation where k<0.
 * ### Example:
 *eg 1- say n=5,k=2
 *a[]={1,2,3,4}
 *a[]={4,3,2,1} is the revered array
 *sub_1[]={4,3};sub_2[]={2,1} are the sub-arrays
 *sub_1[]={3,4};sub_2[]={1,2} are the reversed sub-arrays
 *hence finally we merge sub_1 and sub_2 we get-
 *a[]={3,4,1,2}, which is our desired rotated sub-array

 *eg 2- say n=6,k=-2
 *we take k=k%n, hence k=4 making it equivalent to left rotation by 2 indices.
 *a[]={1,2,3,4,5,6}
 *a[]={6,5,4,3,2,1} reversed array
 *sub_1[]={6,5};sub_2[]={4,3,2,1}
 *sub_1[]={5,6};sub_2={1,2,3,4} reversed are sub-arrays
 *a[]={5,6,1,2,3,4} is the desired array
*/

#include <iostream> // to include io
#include<vector>    // to include vector
#include<algorithm> // to include reverse() function
#include <cassert>  // to include assert

/**
*@ namespace math
*@ brief math algorithms
*/
namespace math{

    /**
    *@brief calculates modulas
    *@param x is an integer
    *@param y is an integer
    *@returns an x mod y as an integer
    */

    int MOD(int x,int y)
    {
        return (x%y +y)%y;
    }
}// namespace math

/**
*@ namespace rotate
*@ brief vector rotation algorithms
*/
namespace rotate
{
    /**
    *@brief rotates an array of length n by k indices
    *@param n is an integer ,contains length of the vector
    *@param k is an integer ,contains number of indices to be shifted
    *@param a is a vector, contains integer elements
    *@returns a rotated vector
    */
    std::vector<int> to_right(std::vector<int> const v, int k)
    {
        std::vector<int> a=v;
        k=math::MOD(k,a.size());
        std::reverse(a.begin(), a.end());
        std::reverse(a.begin(),a.begin() + k);
        std::reverse(a.begin() + k, a.end());
        return a;
    }
}//namespace rotate

/**
*@brief test function;
*@details tests GCD and to_right function
*/
void test()
{

    // Tests the MOD function
    int mod=math::MOD(6,4);
    assert(mod==2);

    mod=math::MOD(-1,4);
    assert(mod==3);

    //Tests the to_rotate function
    std::vector<int> a;
    for(int i=1;i<=5;i++)
    {
        a.push_back(i);
    }
    std::vector<int> v=rotate::to_right(a,1);
    assert(v[0]==5&&v[4]==4);
    std::vector<int> b;
    for(int i=1;i<=5;i++)
    {
        b.push_back(i);
    }
    v=rotate::to_right(b,-1);
    assert(v[0]==2&&v[4]==1);


}

/**
 * @brief Main Function
 * @details Asks the user to enter the number of indices using std::cin
 * @returns 0 on exit
 */
int main()
 {
    test();
    int n=0;   //variable for size of the vector
    int k=0;   //indices to be rotated
    int temp=0;//temporary variable
    std::cout << "Enter size of array=\t";
    std::cin >> n;
    std::cout << "Enter Number of indices u want to rotate the array to right=\t";
    std::cin >> k;
    std::vector<int> a(n); // here vector is used ,BUT IT IS TREATED AS AN ARRAY
    std::cout << "Enter elements of array=\t";
    for (int i = 0; i < n; i++)
    {
        std::cin >> temp;
        a[i]=temp;
    }

    std::vector<int> res= rotate::to_right(a,k);
    std::cout << "Your rotated array is=\t";
    for (int i = 0; i < n; i++) {
        std::cout << res[i] << " ";
    }
    return 0;
}
