/**
 *@file
 *
 *@brief  Rotates an 1D array/vector of length n by k indices in linear time .If k>0 then rotation is towards right and k<0 gives left rotation.
 *k=0 gives no change in our vector. This inplementation fullfills its purpose only by using right rotation.
 *
 *@details To obtain the desired vector in linear time complexity,lets place place every number
 *of the array at its desired correct position. But while doing this, we will lose the original elements.
 *Thus, we need to store the number being replaced in a 'temp' variable. Then, we can place the replaced
 *number(which is stored in temp) at its correct position and so on, n times, where n is the length of array.
 *We have chosen n to be the number of replacements since we have to shift all the elements of the array(which is n).
 *But, there could be a problem with this method, if n % k =0
 *where k = k%n (since a value of k larger than n or k<0 eventually leads to a k equivalent to k%n). In this case,
 *while picking up numbers to be placed at the correct position, we will eventually reach the number from which
 *we originally started. Thus, in such a case, when we
 *hit the original number's index again, we start the same process with the index following our starting point.
 *
 * ### Example:
 *eg 1- say n=5,k=2
 *gcd(2,5)=1 (gcd=1 means all shifts an be done in one cycle)
 *a[0]->a[2] ; a[2]->a[4] ; a[4]->a[1] ;a[1]->a[3] ; a[3]->a[0] ;
 *eg 2- say n=6,k=2
 *gcd(2,6)=2 (gcd=2 means we need to have 2 cycles)
 *a[0]->a[2] ;a[2]->a[4] ;a[4]->a[0] ;
 *a[1]->a[3] ;a[3]->a[5] ;a[5]->a[1] ;
 *Note that-
 *the number of sub sequences are equal to the GCD of and k. If n and k are co-prime
 *complete process can be completed in one go as the subsequent indices are unique.
 *But if gcd>1 then the subsequent indices will repeat after n/gcd number of iterations,
 *hence we need to set our starting index in this case gcd number of times
 *
 *For a k<0, k=k%n is used which results in left rotation.
*/

#include <iostream> // to include io
#include<vector>    // to include vector
#include <cassert>  // to include assert

/**
*@ namespace math
*@ brief math algorithms
*/
namespace math{

    /**
    *@brief calculates Greatest Common Divisor
    *@param a is an integer
    *@param b is an integer
    *@returns an GCD as an integer
    */
    int GCD(int a,int b)
    {
        if(a==0)
        {
            return b;
        }
        return GCD(b%a,a);
    }
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
    std::vector<int> to_right(std::vector<int> a, int n, int k)
    {
        if(k==0)
        {
            k=n; // rotating an array same number of times as its length makes no changes to the array
        }
        k=math::MOD(k,n);
        int gcd= math::GCD(k,n); // rotating k times and n+k times are the same
        int l=0;
        for (int i = 0; i < gcd; i++)
        {
            l=(i+k)%n; //here we set the starting element of the subsequence
            int temp=a[i]; //storing initial element of the sub sequence into temporary variable
            for (int j = 0; j<n/gcd; j++)
            {
                //we put the current element to its approptiate place ,fill the emptied place with element in temp
                //element in temp store the diaplaced
                //eg n=5, k=2 ,current element = a[2], so we put temp element into a[2],orignal a[2] element into a[4]
                //and orignal element of a[4] into temp
                temp+=a[l];
                a[l]=temp-a[l];
                temp=temp-a[l];
                l=(l+k)%n;
           }
         }
        return a;
    }
 }//namespace rotate

/**
*@brief test function;
*@details tests GCD and to_right function
*/
void test()
{
    ///Tests the GCD function
    int gcd=0;
    gcd=math::GCD(3,5);
    assert(gcd==1);

    gcd=math::GCD(5,10);
    assert(gcd==5);
    
    /// Tests the MOD function
    int mod=math::MOD(6,4);
    assert(mod==2);

    mod=math::MOD(-1,4);
    assert(mod==3);
    
    ///Tests the to_right function
    std::vector<int> a;
    for(int i=1;i<=5;i++)
    {
        a.push_back(i);
    }
    std::vector<int> v;
    v=rotate::to_right(a,5,1);
    assert(v[0]==5&&v[4]==4);
    v=rotate::to_right(a,5,-1);
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

    std::vector<int> res= rotate::to_right(a,n,k);
    std::cout << "Your rotated array is=\t";
    for (int i = 0; i < n; i++) {
        std::cout << res[i] << " ";
    }
    return 0;
}
